/*
  ==============================================================================

    Oscillator.h
    Author:  Andrew Noe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component

{
public:
    Oscillator(AASineAudioProcessor&);
    ~Oscillator();

    void paint (juce::Graphics&) override;
    void resized() override;


private:

    juce::ComboBox oscMenu;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    AASineAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
