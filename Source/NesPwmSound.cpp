/*
  ==============================================================================

    NesPwmSound.cpp
    Created: 10 Sep 2019 10:03:17pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesPwmSound.h"

NesPwmSound::NesPwmSound(int playNotesGTE)
{
    this->playNotesGTE = playNotesGTE;
}

bool NesPwmSound::appliesToNote(int midiNoteNumber)
{
    return midiNoteNumber >= playNotesGTE;
}

bool NesPwmSound::appliesToChannel(int)
{
    return true;
}

void NesPwmSound::setSplitKey(int midiNoteNumber)
{
    playNotesGTE = midiNoteNumber;
}
