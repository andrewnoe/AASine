/*
  ==============================================================================

    Oscillator.cpp
    Author:  Andrew Noe
    Gives the Synth Voice the ability to change its wave shape.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(AASineAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Oscillator::~Oscillator()
{

    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&oscMenu);


    waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);

    

}

void Oscillator::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Oscillator", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    */

}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));


}

void Oscillator::comboBoxChanged(juce::ComboBox* box) {

}
