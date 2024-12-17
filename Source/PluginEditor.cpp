/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AASineAudioProcessorEditor::AASineAudioProcessorEditor(AASineAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), oscGui(p), noiseGui(p), envGui(p), filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 200);

    //addAndMakeVisible(&oscGui);
    addAndMakeVisible(&noiseGui);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&filterGui);

}

AASineAudioProcessorEditor::~AASineAudioProcessorEditor()
{
}

//==============================================================================
void AASineAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void AASineAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}

