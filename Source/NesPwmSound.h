/*
  ==============================================================================

    NesPwmSound.h
    Created: 10 Sep 2019 10:03:17pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct NesPwmSound : public SynthesiserSound
{
public:
    NesPwmSound(int playNotesGTE);

    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int) override;

    void setSplitKey(int midiNoteNumber);

private:
    int playNotesGTE;
};
