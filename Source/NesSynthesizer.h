/*
  ==============================================================================

    NesSynthesizer.h
    Created: 7 Sep 2020 9:57:21pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct NesSynthesizer : public Synthesiser
{
public:
    NesSynthesizer();

    void setNoiseMode (bool noiseMode);

    void setTriangleOctavesUp (int octavesUp);
};
