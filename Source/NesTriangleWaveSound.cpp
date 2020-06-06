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
    if (noiseChannelActive)
    {
        // The furthest left of the keyboard is used for the noise generator:
        return midiNoteNumber >= MIN_TRIANGLE_MIDI_NOTE && midiNoteNumber < playNotesLessThan;
    }

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

// Indicate whether the noise channel is active.
// If the noise channel is active, don't play the triangle wave
// on the furthest left keys since the noise channel is using them.
// Otherwise, use the whole left side of the keyboard for the triangle wave.
void NesTriangleWaveSound::setNoiseChannelActive(bool active)
{
    noiseChannelActive = active;
}
