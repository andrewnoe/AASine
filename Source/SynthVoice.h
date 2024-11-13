/*
  ==============================================================================

    SynthVoice.h
    Author:  Andrew Noe
    Holds all necessary functions for creating sound from a wave shape and
    passing it through a volume envelope and frequency filter.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice {

public:

    bool canPlaySound(juce::SynthesiserSound* sound) {

        return dynamic_cast<SynthSound*>(sound) != nullptr;

    }

    
    //Oscillator creation
    void getOscType(float* selection) {
        waveShape = *selection;
    }

    double setOscType() {
        if (waveShape == 0) {
            return osc1.sinewave(frequency);
        }
        else {
            return osc1.sinewave(frequency);
        }
    }

    //Envelope
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release) {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }

    double setEnvelope() {
        return env1.adsr(setOscType(), env1.trigger) ;
    }

    //Filter
    void getFilterParams(float* type, float* filterCutoff, float* filterRes) {
        filterType = *type;
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }

    double setFilter() {
        if (filterType == 0) {
            return filter1.lores(setEnvelope(), cutoff, resonance);
        }
        if (filterType == 1) {
            return filter1.hires(setEnvelope(), cutoff, resonance);
        }
        if (filterType == 2) {
            return filter1.bandpass(setEnvelope(), cutoff, resonance);
        }
        else {
            return filter1.lores(setEnvelope(), cutoff, resonance);
        }
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {

        env1.trigger = 1;
        //converts midi note to correct synth frequency
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

        level = velocity;

    }

    void stopNote(float velocity, bool allowTailOff) {

        env1.trigger = 0;
        allowTailOff = true;

        if (velocity == 0) {
            clearCurrentNote();
        }
        

    }

    void pitchWheelMoved(int newPitchWheelValue) {

    }

    void controllerMoved(int controllerNumber, int newControllerValue) {

    }

    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) {

        for (int sample = 0; sample < numSamples; sample++) {

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {

                outputBuffer.addSample(channel, startSample, setFilter() *0.3f);

            }

            startSample++;

        }

    }

private:
    double level;
    double frequency;
    int waveShape;

    int filterType;
    float cutoff;
    float resonance;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;

};

