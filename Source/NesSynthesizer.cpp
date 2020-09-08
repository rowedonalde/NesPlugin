/*
  ==============================================================================

    NesSynthesizer.cpp
    Created: 7 Sep 2020 9:57:21pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesNoiseVoice.h"
#include "NesTriangleWaveVoice.h"
#include "NesSynthesizer.h"

NesSynthesizer::NesSynthesizer()
{

}

void NesSynthesizer::setNoiseMode (bool noiseMode)
{
    for (int i = 0; i < this->getNumVoices(); i++)
    {
        SynthesiserVoice* voice = this->getVoice(i);
        if (dynamic_cast<NesNoiseVoice*> (voice) != nullptr)
        {
            ((NesNoiseVoice*) voice)->setNoiseMode (noiseMode);
        }
    }
}

void NesSynthesizer::setTriangleOctavesUp (int octavesUp)
{
    for (int i = 0; i < this->getNumVoices(); i++)
    {
        SynthesiserVoice* voice = this->getVoice(i);
        if (dynamic_cast<NesTriangleWaveVoice*> (voice) != nullptr)
        {
            ((NesTriangleWaveVoice*) voice)->setOctavesUp (octavesUp);
        }
    }
}
