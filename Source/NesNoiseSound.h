/*
  ==============================================================================

    NesNoiseSound.h
    Created: 9 Jan 2020 10:18:44pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#define MAX_NOISE_MIDI_NOTE 15

#include "../JuceLibraryCode/JuceHeader.h"

struct NesNoiseSound : public SynthesiserSound
{
public:
    NesNoiseSound();

    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int) override;
    void setActive (bool active);

private:
    bool isActive = true;
};
