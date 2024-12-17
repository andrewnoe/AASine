/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AASineAudioProcessor::AASineAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
        #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
        #endif
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        #endif
            ),
tree(*this, nullptr, "PARAMETERS",
    {   std::make_unique<juce::AudioParameterFloat>("wavetype", "WaveType", juce::NormalisableRange<float>(0.0f, 2.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
        std::make_unique<juce::AudioParameterFloat>("decay", "Decay",juce::NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.8f),
        std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
        std::make_unique<juce::AudioParameterFloat>("filterType", "FilterType", juce::NormalisableRange<float>(0.0f, 2.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>("filterCutoff", "FilterCutoff", juce::NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
        std::make_unique<juce::AudioParameterFloat>("filterRes", "FilterRes", juce::NormalisableRange<float>(1.0f, 5.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>("blend","Blend", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f),
    })
#endif
{

    mySynth.clearVoices();

    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

}

AASineAudioProcessor::~AASineAudioProcessor()
{
}

//==============================================================================
const juce::String AASineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AASineAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AASineAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AASineAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AASineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AASineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int AASineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AASineAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String AASineAudioProcessor::getProgramName(int index)
{
    return {};
}

void AASineAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void AASineAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    updateFilter();


}

void AASineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AASineAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void AASineAudioProcessor::updateFilter()
{
    int menuChoice = *tree.getRawParameterValue("filterType");
    int freq = *tree.getRawParameterValue("filterCutoff");
    int res = *tree.getRawParameterValue("filterRes");

    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }

    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }

    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
}

void AASineAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    juce::ScopedNoDenormals noDenormals;

    for (int i = 0; i < mySynth.getNumVoices(); i++) {

        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {

            myVoice->getEnvelopeParams((float*)tree.getRawParameterValue("attack"),
                                       (float*)tree.getRawParameterValue("decay"), 
                                       (float*)tree.getRawParameterValue("sustain"), 
                                       (float*)tree.getRawParameterValue("release"));

            myVoice->getOscType((float*)tree.getRawParameterValue("wavetype"));

            myVoice->getFilterParams((float*)tree.getRawParameterValue("filterType"),
                                     (float*)tree.getRawParameterValue("filterCutoff"),
                                     (float*)tree.getRawParameterValue("filterRes"));
            myVoice->getExtraParams((float*)tree.getRawParameterValue("blend"));

        }

    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilter();
    juce::dsp::AudioBlock<float> block(buffer);
    stateVariableFilter.process(juce::dsp::ProcessContextReplacing<float>(block));

}

//==============================================================================
bool AASineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AASineAudioProcessor::createEditor()
{
    return new AASineAudioProcessorEditor(*this);
}

//==============================================================================
void AASineAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AASineAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AASineAudioProcessor();
}
