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
    NesTriangleWaveSound();

    bool appliesToNote (int) override;
    bool appliesToChannel (int) override;
};
