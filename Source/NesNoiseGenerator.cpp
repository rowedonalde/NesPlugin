/*
  ==============================================================================

    NesNoiseGenerator.cpp
    Created: 9 Jan 2020 10:17:50pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "NesNoiseGenerator.h"

NesNoiseGenerator::NesNoiseGenerator (double sampleRate)
{
    this->sampleRate = sampleRate;
}

float NesNoiseGenerator::getNextSample()
{
    // Advance through the lifecycle of this noise step:
    x = x + cyclesPerSample;

    // If we're at the end of this step, get the next one:
    if (x >= 1.0)
    {
        advanceRegister();
        x = fmod(x, 1.0);
    }

    return y;
}

void NesNoiseGenerator::advanceRegister()
{
    // From https://wiki.nesdev.com/w/index.php/APU_Noise:
    // Feedback is calculated as the exclusive-OR of bit 0 and one other bit:
    // bit 6 if Mode flag is set, otherwise bit 1:
    int compareBit = shiftRegisterShortMode ? FEEDBACK_COMPARE_BIT_SHORT_MODE : FEEDBACK_COMPARE_BIT_LONG_MODE;
    bool feedback = rngShiftRegister.test(0) != rngShiftRegister.test(compareBit);
    

    // The shift register is shifted right by one bit:
    rngShiftRegister >>= 1;

    // Bit 14 is set to the feedback calculated earlier:
    rngShiftRegister.set (FEEDBACK_SET_BIT, feedback);

    // The mixer receives the current envelope volume except when
    // bit 0 of the shift register is set:
    y = (rngShiftRegister.test(0) ? -1.0 : 1.0) * gain;
}

void NesNoiseGenerator::setFrequency(double frequency)
{
    // i.e., Hz subdivided into samples:
    cyclesPerSample = frequency / sampleRate;
}

void NesNoiseGenerator::setShiftRegisterShortMode(bool mode)
{
    shiftRegisterShortMode = mode;
}
