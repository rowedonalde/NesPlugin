/*
  ==============================================================================

    NesTriangleWaveSound.h
    Created: 1 Sep 2019 10:56:47pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct NesTriangleWaveSound : public SynthesiserSound
{
public:
    NesTriangleWaveSound(int playNotesLessThan);

    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int) override;

    void setSplitKey(int midiNoteNumber);

private:
    int playNotesLessThan;
};
