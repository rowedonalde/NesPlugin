/*
  ==============================================================================

    NesTriangleWaveVoice.h
    Created: 1 Sep 2019 10:41:52pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesTriangleGenerator.h"

struct NesTriangleWaveVoice : public SynthesiserVoice
{
public:
    NesTriangleWaveVoice();

    bool canPlaySound (SynthesiserSound* sound) override;

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int) override;

    void stopNote (float, bool allowTailOff) override;

    void pitchWheelMoved (int) override;

    void controllerMoved (int, int) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    void setOctavesUp (int octavesUp);

private:
    double level = 0.0;
    bool makeSound = false;
    double pitchMultiplier;
    NesTriangleGenerator nesTriangleGenerator;
};
