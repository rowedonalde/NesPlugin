/*
  ==============================================================================

    SampleGenerator.h
    Created: 27 Jul 2019 6:01:11pm
    Author:  Donald Rowe

  ==============================================================================
*/

#pragma once

class SampleGenerator
{
public:
    virtual float getNextSample() = 0;
    virtual void setFrequency (double frequency) = 0;
};
