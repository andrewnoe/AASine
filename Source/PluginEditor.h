/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "NoiseOscillator.h"
#include "Envelope.h"
#include "Filter.h"

//==============================================================================
/**
*/
class AASineAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AASineAudioProcessorEditor(AASineAudioProcessor&);
    ~AASineAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AASineAudioProcessor& processor;

    Oscillator oscGui;
    NoiseOscillator noiseGui;
    Envelope envGui;
    Filter filterGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AASineAudioProcessorEditor)
};
