/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesNoiseVoice.h"
#include "NesNoiseSound.h"
#include "NesTriangleWaveSound.h"
#include "NesTriangleWaveVoice.h"
#include "NesPwmSound.h"
#include "NesSynthesizer.h"
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

    NesNoiseSound* noiseSound;
    NesTriangleWaveSound* triangleSound;
    NesPwmSound* pwmSound;

    int previousSplitKey;
    int previousTriangleWaveOctavesUp;
    bool previousNoiseGeneratorActive;
    bool previousNoiseMode;
    double masterGain = 0.0;

    std::atomic<float>* splitKeyParameter = nullptr;
    std::atomic<float>* triangleWaveOctavesUpParameter = nullptr;

    // Thess represent bools where false is 0.0 and true is 1.0.
    // Should convert with a >0.5 comparison.
    std::atomic<float>* noiseGeneratorActiveParameter = nullptr;
    std::atomic<float>* noiseModeParameter = nullptr;

    NesSynthesizer synth;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NesPluginAudioProcessor)
};
