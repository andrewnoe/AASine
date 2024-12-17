/*
  ==============================================================================

    NoiseOscillator.cpp
    Author:  Andrew
    Enables the slider for introducing white noise to the Synth Voice signal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoiseOscillator.h"

//==============================================================================
NoiseOscillator::NoiseOscillator(AASineAudioProcessor& p) : processor(p)
{
    setSize(200, 200);

    Blendslider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(1.0f);
    Blendslider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);

    blendVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend", Blendslider);

}

NoiseOscillator::~NoiseOscillator()
{
}

void NoiseOscillator::paint (juce::Graphics& g)
{   
    //background stuff
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("White Noise", titleArea, juce::Justification::centredTop);


    juce::Rectangle <float> area(62, 25, 75, 150);

    g.setColour(juce::Colours::beige);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void NoiseOscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int sliderWidth = 25;
    int sliderHeight = 175;

    //draw sliders by reducing area from rectangle above
    Blendslider.setBounds(area.removeFromTop(sliderHeight).withTrimmedTop(10));

}
