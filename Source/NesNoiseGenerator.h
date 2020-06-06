/*
  ==============================================================================

    NesNoiseGenerator.h
    Created: 9 Jan 2020 10:17:50pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#define SHIFT_REGISTER_SIZE 15
#define SHIFT_REGISTER_SEED 1
#define FEEDBACK_COMPARE_BIT_LONG_MODE 1
#define FEEDBACK_COMPARE_BIT_SHORT_MODE 6
#define FEEDBACK_SET_BIT 14

#include <bitset>
#include "SampleGenerator.h"

class NesNoiseGenerator : public SampleGenerator
{
public:
    NesNoiseGenerator (double sampleRate);
    float getNextSample() override;
    void setFrequency (double frequency) override;
    void setShiftRegisterShortMode (bool mode);

private:
    void advanceRegister();

    // Number of samples per second this will output:
    double sampleRate;

    // The fraction of the period that will be covered in one sample.
    // Because this is a noise channel, we should not be concerned
    // with smoothing out changes as in the other oscillators.
    double cyclesPerSample;

    // Current progress of this cycle. In the case of this noise
    // generator, one cycle is one resampling--that is, the
    // equivalent of one sample in a pure white noise generator.
    double x = 0.0;

    // Current output value determined by the shift register and the gain.
    // This is calculated when the register is advanced one step forward:
    double y = 0.0;

    // Per https://wiki.nesdev.com/w/index.php/APU_Noise this is seeded at 1:
    std::bitset<SHIFT_REGISTER_SIZE> rngShiftRegister = std::bitset<SHIFT_REGISTER_SIZE> (SHIFT_REGISTER_SEED);

    // TODO: This should be dynamic;
    float gain = 0.25f;

    bool shiftRegisterShortMode = false;
};
