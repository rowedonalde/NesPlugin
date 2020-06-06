/*
  ==============================================================================

    NesNoiseVoice.h
    Created: 9 Jan 2020 10:18:23pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#define NUM_NOISE_FREQUENCIES 16

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesNoiseGenerator.h"

struct NesNoiseVoice : public SynthesiserVoice
{
public:
    NesNoiseVoice();

    bool canPlaySound (SynthesiserSound *) override;

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int) override;

    void stopNote (float, bool allowTailOff) override;

    void pitchWheelMoved (int) override;

    void controllerMoved (int, int) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    void setNoiseMode (bool noiseMode);

private:
    bool makeSound = false;
    NesNoiseGenerator nesNoiseGenerator;
    static const double NOISE_FREQUENCIES[NUM_NOISE_FREQUENCIES];
};
