/*
  ==============================================================================

    NesPwmVoice.h
    Created: 10 Sep 2019 10:02:58pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesPwmGenerator.h"

struct NesPwmVoice : public SynthesiserVoice
{
public:
    NesPwmVoice();

    bool canPlaySound (SynthesiserSound* sound) override;

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int) override;

    void stopNote (float, bool allowTailOff) override;

    void pitchWheelMoved (int) override;

    void controllerMoved (int, int) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

private:
    double level = 0.0;
    bool makeSound = false;
    NesPwmGenerator nesPwmGenerator;
};
