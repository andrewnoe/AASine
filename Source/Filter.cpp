/*
  ==============================================================================

    Filter.cpp
    Author:  Andrew
    Enables the functionality of a basic frequency filter with 3 shapes and 
    a resonance knob.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"


//==============================================================================
Filter::Filter(AASineAudioProcessor& p) : processor(p)
{
    setSize(200, 200);

    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterType", filterMenu);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 10000.0);
    filterCutoff.setValue(1000.0);
    filterCutoff.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCutoff);
    filterVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000);

    filterRes.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    filterVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterRes);

}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    juce::Rectangle<int> knobOne(54, 75, getWidth(), 20);
    juce::Rectangle<int> knobTwo(34, 75, getWidth(), 20);

    g.fillAll (juce::Colours::black); 
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);


    juce::Rectangle<float> area(25, 25, 150, 150);
    g.setColour(juce::Colours::beige);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);

    g.drawText("Freq", knobOne, juce::Justification::centredLeft);
    g.drawText("Res", knobTwo, juce::Justification::centred);
    
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);

}
