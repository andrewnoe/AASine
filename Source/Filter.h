/*
  ==============================================================================

    Filter.h
    Author:  Andrew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(AASineAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider filterCutoff;
    juce::Slider filterRes;

    juce::ComboBox filterMenu;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> resVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;

    AASineAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
