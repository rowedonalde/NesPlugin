/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesTriangleWaveSound.h"
#include "NesTriangleWaveVoice.h"
#include "NesPwmSound.h"
#include "SampleGenerator.h"

//==============================================================================
/**
*/
class NesPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NesPluginAudioProcessor();
    ~NesPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioProcessorValueTreeState parameters;

    NesTriangleWaveSound* triangleSound;
    NesPwmSound* pwmSound;

    // Keep a handle on the triangle voice specifically so we
    // can shift the octave up and down:
    NesTriangleWaveVoice* triangleVoice;

    int previousSplitKey;
    int previousTriangleWaveOctavesUp;
    double masterGain = 0.0;

    float* splitKeyParameter = nullptr;
    float* triangleWaveOctavesUpParameter = nullptr;

    Synthesiser synth;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NesPluginAudioProcessor)
};
