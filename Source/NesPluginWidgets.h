/*
  ==============================================================================

    NesPluginWidgets.h
    Created: 14 Oct 2019 4:31:37pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#define NUM_NOTE_NAMES 12
#define MIDI_START_OCTAVE -2

#include "../JuceLibraryCode/JuceHeader.h"

class MidiNoteSlider : public Slider
{
public:
    String getTextFromValue (double value) override;

private:
    static const String NOTE_NAMES[NUM_NOTE_NAMES];
};
