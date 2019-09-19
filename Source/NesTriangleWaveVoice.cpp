/*
  ==============================================================================

    NesTriangleWaveVoice.cpp
    Created: 1 Sep 2019 10:41:52pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesTriangleWaveSound.h"
#include "NesTriangleWaveVoice.h"

NesTriangleWaveVoice::NesTriangleWaveVoice()
    : nesTriangleGenerator(getSampleRate(), 440.0)
{

}

bool NesTriangleWaveVoice::canPlaySound(SynthesiserSound *sound)
{
    return dynamic_cast<NesTriangleWaveSound*> (sound) != nullptr;
}

void NesTriangleWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *, int)
{
    // We step the apparent tone up two octaves to give the
    // triangle voice more upper room in the keyboard split:
    // TODO make the octaves configurable in the UI
    nesTriangleGenerator.setFrequency (MidiMessage::getMidiNoteInHertz(midiNoteNumber) * 4);
    makeSound = true;
}

void NesTriangleWaveVoice::stopNote(float, bool allowTailOff)
{
    clearCurrentNote();
    makeSound = false;
}

void NesTriangleWaveVoice::pitchWheelMoved(int)
{

}

void NesTriangleWaveVoice::controllerMoved(int, int)
{

}

void NesTriangleWaveVoice::renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples)
{
    if (makeSound)
    {
        for (int i = 0; i < numSamples; i++)
        {
            // We want to copy the sample value to each channel:
            auto nextSampleValue = nesTriangleGenerator.getNextSample();

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample + i, nextSampleValue);
            }
        }
    }
}
