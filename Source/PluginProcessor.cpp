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
    : parameters(*this, nullptr, Identifier ("NesPlugin"),
                 {
                     std::make_unique<AudioParameterInt>("splitKey", "Split Key", 0, 127, 60)
                 })
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    splitKeyParameter = parameters.getRawParameterValue ("splitKey");

    previousSplitKey = *splitKeyParameter;
    triangleSound = new NesTriangleWaveSound(*splitKeyParameter);
    pwmSound = new NesPwmSound(*splitKeyParameter);
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
    // Set up synth:
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

    // Listen for changes in the slider-controlled parameters:
    int currentSplitKey = *splitKeyParameter;

    if (currentSplitKey != previousSplitKey)
    {
        triangleSound->setSplitKey(currentSplitKey);
        pwmSound->setSplitKey(currentSplitKey);
        previousSplitKey = currentSplitKey;
    }

    synth.renderNextBlock(buffer, midiMessages, audioSourceChannelInfo.startSample, buffer.getNumSamples());
}

//==============================================================================
bool NesPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NesPluginAudioProcessor::createEditor()
{
    return new NesPluginAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void NesPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Copy the state to the requested location in memory:
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void NesPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Copy the XML data into the parameter state iff the proper tag name exists:
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr && xmlState->hasTagName(parameters.state.getType()))
    {
        parameters.replaceState (ValueTree::fromXml (*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NesPluginAudioProcessor();
}
