/*
  ==============================================================================

    NesTriangleGenerator.h
    Created: 27 Jul 2019 5:19:01pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#define NUM_WAVETABLE_STEPS 16
#define WAVETABLE_MAX_INDEX 31

#include "SampleGenerator.h"

class NesTriangleGenerator : public SampleGenerator
{
public:
    NesTriangleGenerator (double sampleRate, double toneFrequency);
    float getNextSample() override;
    void setFrequency (double frequency) override;

private:
    // Number of samples per second this will output:
    double sampleRate;

    // The amount of the period that will be covered in one sample:
    double targetCyclesPerSample;

    // To avoid artifacts caused by abrupt frequency shifts, we
    // gradually change the apparent frequency over a number of samples:
    double smoothedCyclesPerSample;
    constexpr static const int SAMPLES_TO_UPDATE = 200;
    double smoothedCpsUpdate;

    double waveTable[NUM_WAVETABLE_STEPS * 2];

    // Current progress of this cycle:
    double x = 0.0;
};
