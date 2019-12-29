/*
  ==============================================================================

    NesPluginWidgets.cpp
    Created: 14 Oct 2019 4:31:37pm
    Author:  Donald Rowe

  ==============================================================================
*/

#include "NesPluginWidgets.h"

// MIDI note 0 is C-2 ("C negative 2"), at least in Logic Pro X:
const String MidiNoteSlider::NOTE_NAMES[NUM_NOTE_NAMES] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

String MidiNoteSlider::getTextFromValue(double value)
{
    int note = (int) value;
    String noteName = NOTE_NAMES[note % NUM_NOTE_NAMES];
    int octave = MIDI_START_OCTAVE + (note / NUM_NOTE_NAMES);
    return noteName + String(octave);
}
