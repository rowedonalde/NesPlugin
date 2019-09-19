/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "NesPwmGenerator.h"
#include "NesPwmVoice.h"
#include "NesPwmSound.h"
#include "NesTriangleGenerator.h"
#include "NesTriangleWaveVoice.h"
#include "NesTriangleWaveSound.h"
#include "SampleGenerator.h"

//==============================================================================
NesPluginAudioProcessor::NesPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    triangleSound = new NesTriangleWaveSound(splitKey);
    pwmSound = new NesPwmSound(splitKey);
}

NesPluginAudioProcessor::~NesPluginAudioProcessor()
{
}

//==============================================================================
const String NesPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NesPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NesPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NesPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NesPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NesPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NesPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NesPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String NesPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void NesPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NesPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //sampleGenerators = new SampleGenerator*[getTotalNumOutputChannels()];
    //for (int i = 0; i < getTotalNumOutputChannels(); i++)
    //{
    //    //sampleGenerators[i] = new SineGenerator(sampleRate, 10);
    //    sampleGenerators[i] = new NesTriangleGenerator(sampleRate, 10);
    //}

    // Set up synth:
    // Actually, I don't think we need a synth audio source here--
    // we just need a synth.
    //synthAudioSource.prepareToPlay(samplesPerBlock, sampleRate);

    for (auto i = 0; i < 1; i++)
    {
        synth.addVoice (new NesTriangleWaveVoice());

        synth.addVoice (new NesPwmVoice());
        synth.addVoice (new NesPwmVoice());
    }

    synth.addSound (triangleSound);
    synth.addSound (pwmSound);

    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void NesPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    // TODO: destroy synths here?
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NesPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NesPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto audioSourceChannelInfo = AudioSourceChannelInfo(buffer);
    synth.renderNextBlock(buffer, midiMessages, audioSourceChannelInfo.startSample, buffer.getNumSamples());
}

//==============================================================================
bool NesPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NesPluginAudioProcessor::createEditor()
{
    return new NesPluginAudioProcessorEditor (*this);
}

//==============================================================================
void NesPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NesPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

int NesPluginAudioProcessor::getSplitKey()
{
    return splitKey;
}

void NesPluginAudioProcessor::setSplitKey(int splitKey)
{
    this->splitKey = splitKey;

    triangleSound->setSplitKey(splitKey);
    pwmSound->setSplitKey(splitKey);
}

double NesPluginAudioProcessor::getMasterGain()
{
    return masterGain;
}

void NesPluginAudioProcessor::setMasterGain(double gain)
{
    masterGain = gain;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NesPluginAudioProcessor();
}
