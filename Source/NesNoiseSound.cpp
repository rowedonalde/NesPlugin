/*
  ==============================================================================

    NesNoiseSound.cpp
    Created: 9 Jan 2020 10:18:44pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesNoiseSound.h"

NesNoiseSound::NesNoiseSound()
{

}

bool NesNoiseSound::appliesToNote(int midiNoteNumber)
{
    return midiNoteNumber <= MAX_NOISE_MIDI_NOTE;
}

bool NesNoiseSound::appliesToChannel(int)
{
    return true;
}
