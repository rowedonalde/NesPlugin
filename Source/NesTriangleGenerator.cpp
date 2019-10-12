/*
  ==============================================================================

    NesTriangleGenerator.cpp
    Created: 27 Jul 2019 5:19:01pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "NesTriangleGenerator.h"

NesTriangleGenerator::NesTriangleGenerator(double sampleRate, double toneFrequency)
{
    this->sampleRate = sampleRate;

    setFrequency(toneFrequency);
    smoothedCyclesPerSample = targetCyclesPerSample;
    smoothedCpsUpdate = 0.0;

    // Generate increasing half of the wavetable:
    for (auto step = 0; step < NUM_WAVETABLE_STEPS; step++)
    {
        waveTable[step] = 2.0 / NUM_WAVETABLE_STEPS * step - 1.0;
    }

    // Mirror it to get the decreasing half of the wavetable:
    for (auto step = 0; step < NUM_WAVETABLE_STEPS; step++)
    {
        waveTable[NUM_WAVETABLE_STEPS + step] = waveTable[NUM_WAVETABLE_STEPS - step - 1];
    }
}

float NesTriangleGenerator::getNextSample()
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

    int waveStep = x * NUM_WAVETABLE_STEPS * 2;

    // If x==1.0, then waveStep will be 1.0*16*2==32, which is out of bounds in the array:
    return waveTable[std::min(waveStep, WAVETABLE_MAX_INDEX)];
}

void NesTriangleGenerator::setFrequency(double frequency)
{
    // i.e., Hz subdivided into samples:
    targetCyclesPerSample = frequency / sampleRate;

    // In our transition from the previous frequency to the new frequency,
    // this is how much we should shift per sample:
    smoothedCpsUpdate = fabs(targetCyclesPerSample - smoothedCyclesPerSample) / SAMPLES_TO_UPDATE;
}
