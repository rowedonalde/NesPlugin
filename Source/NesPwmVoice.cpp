/*
  ==============================================================================

    NesPwmVoice.cpp
    Created: 10 Sep 2019 10:02:58pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesPwmSound.h"
#include "NesPwmVoice.h"

NesPwmVoice::NesPwmVoice()
    : nesPwmGenerator(getSampleRate(), 440.0)
{

}

bool NesPwmVoice::canPlaySound(SynthesiserSound *sound)
{
    return dynamic_cast<NesPwmSound*> (sound) != nullptr;
}

void NesPwmVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *, int)
{
    nesPwmGenerator.setFrequency (MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    makeSound = true;
}

void NesPwmVoice::stopNote(float, bool allowTailOff)
{
    clearCurrentNote();
    makeSound = false;
}

void NesPwmVoice::pitchWheelMoved(int)
{

}

void NesPwmVoice::controllerMoved(int, int)
{

}

void NesPwmVoice::renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples)
{
    if (makeSound)
    {
        for (int i = 0; i < numSamples; i++)
        {
            // We want to copy the sample value to each channel:
            auto nextSampleValue = nesPwmGenerator.getNextSample();

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample + i, nextSampleValue);
            }
        }
    }
}
