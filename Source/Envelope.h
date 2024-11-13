/*
  ==============================================================================

    Envelope.h
    Author:  Andrew Noe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(AASineAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> attackVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> decayVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> releaseVal;

    AASineAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
