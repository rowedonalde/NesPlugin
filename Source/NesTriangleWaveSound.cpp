/*
  ==============================================================================

    NesTriangleWaveSound.cpp
    Created: 1 Sep 2019 10:56:47pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesTriangleWaveSound.h"

NesTriangleWaveSound::NesTriangleWaveSound()
{

}

bool NesTriangleWaveSound::appliesToNote(int)
{
    return true;
}

bool NesTriangleWaveSound::appliesToChannel(int)
{
    return true;
}
