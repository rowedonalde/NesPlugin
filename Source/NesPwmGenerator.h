/*
  ==============================================================================

    NesPwmGenerator.h
    Created: 10 Sep 2019 10:02:28pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "SampleGenerator.h"

class NesPwmGenerator : public SampleGenerator
{
public:
    NesPwmGenerator (double sampleRate, double toneFrequency);
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

    // Current progress of this cycle:
    double x = 0.0;
};
