/*
  ==============================================================================

    NesPwmGenerator.cpp
    Created: 10 Sep 2019 10:02:28pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesPwmGenerator.h"

NesPwmGenerator::NesPwmGenerator(double sampleRate, double toneFrequency)
{
    this->sampleRate = sampleRate;

    setFrequency(toneFrequency);
    smoothedCyclesPerSample = targetCyclesPerSample;
    smoothedCpsUpdate = 0.0;
}

float NesPwmGenerator::getNextSample()
{
    // Update to the next progress before we return:
    x = fmod(x + smoothedCyclesPerSample, 1.0);

    // Update the smoothed frequency if needed:
    if (smoothedCyclesPerSample < targetCyclesPerSample)
    {
        smoothedCyclesPerSample = std::min(
            targetCyclesPerSample, smoothedCyclesPerSample + smoothedCpsUpdate);
    }
    else if (smoothedCyclesPerSample > targetCyclesPerSample)
    {
        smoothedCyclesPerSample = std::max(
            targetCyclesPerSample, smoothedCyclesPerSample - smoothedCpsUpdate);
    }

    float y = 1.0;

    // TODO: put duty cycle logic here. For now just assume square wave.
    if (x >= 0.5)
    {
        y = -1 * y;
    }

    return y;
}

void NesPwmGenerator::setFrequency(double frequency)
{
    // i.e., Hz subdivided into samples:
    targetCyclesPerSample = frequency / sampleRate;

    // In our transition from our previous frequency to the new frequency,
    // this is how much we should shift per sample:
    // XXX Do I even need this for PWM?
    smoothedCpsUpdate = fabs(targetCyclesPerSample - smoothedCyclesPerSample) / SAMPLES_TO_UPDATE;
}
