/*
  ==============================================================================

    NesNoiseVoice.cpp
    Created: 9 Jan 2020 10:18:23pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesNoiseSound.h"
#include "NesNoiseVoice.h"

// From https://wiki.nesdev.com/w/index.php/APU_Noise
const double NesNoiseVoice::NOISE_FREQUENCIES[NUM_NOISE_FREQUENCIES] = {
    440.0,
    879.9,
    1761.6,
    2348.8,
    3523.2,
    4709.9,
    7046.3,
    8860.3,
    11186.1,
    13982.6,
    18643.5,
    27965.2,
    55930.4,
    111860.8,
    223721.6,
    447443.2
};

NesNoiseVoice::NesNoiseVoice()
    : nesNoiseGenerator(getSampleRate())
{

}

bool NesNoiseVoice::canPlaySound(SynthesiserSound *sound)
{
    return dynamic_cast<NesNoiseSound*> (sound) != nullptr;
}

void NesNoiseVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *, int)
{
    // TODO: Actually calculate frequency from table:
    nesNoiseGenerator.setFrequency(NOISE_FREQUENCIES[midiNoteNumber]);
    makeSound = true;
}

void NesNoiseVoice::stopNote(float, bool allowTailOff)
{
    clearCurrentNote();
    makeSound = false;
}

void NesNoiseVoice::pitchWheelMoved(int)
{

}

void NesNoiseVoice::controllerMoved(int, int)
{

}

void NesNoiseVoice::renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples)
{
    if (makeSound)
    {
        for (int i = 0; i < numSamples; i++)
        {
            auto nextSampleValue = nesNoiseGenerator.getNextSample();

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample + i, nextSampleValue);
            }
        }
    }
}
