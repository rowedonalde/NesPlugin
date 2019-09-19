/*
  ==============================================================================

    NesTriangleWaveSound.cpp
    Created: 1 Sep 2019 10:56:47pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesTriangleWaveSound.h"

NesTriangleWaveSound::NesTriangleWaveSound(int playNotesLessThan)
{
    this->playNotesLessThan = playNotesLessThan;
}

bool NesTriangleWaveSound::appliesToNote(int midiNoteNumber)
{
    return midiNoteNumber < playNotesLessThan;
}

bool NesTriangleWaveSound::appliesToChannel(int)
{
    return true;
}

void NesTriangleWaveSound::setSplitKey(int midiNoteNumber)
{
    playNotesLessThan = midiNoteNumber;
}
