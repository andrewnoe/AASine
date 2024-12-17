/*
  ==============================================================================

    NoiseOscillator.h
    Author:  Andrew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class NoiseOscillator  : public juce::Component
{
public:
    NoiseOscillator(AASineAudioProcessor&);
    ~NoiseOscillator();

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider Blendslider;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> blendVal;

    AASineAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseOscillator)
};
