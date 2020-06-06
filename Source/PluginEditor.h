/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NesPluginWidgets.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NesPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    NesPluginAudioProcessorEditor (NesPluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~NesPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //void sliderValueChanged (Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NesPluginAudioProcessor& processor;

    AudioProcessorValueTreeState& valueTreeState;
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    MidiNoteSlider keyboardSplitSlider;
    Label keyboardSplitLabel;
    std::unique_ptr<SliderAttachment> keyboardSplitAttachment;

    Slider triangleWaveOctavesUpSlider;
    Label triangleWaveOctavesUpLabel;
    std::unique_ptr<SliderAttachment> triangleWaveOctavesUpAttachment;

    ToggleButton noiseModeToggleButton;
    std::unique_ptr<ButtonAttachment> noiseModeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NesPluginAudioProcessorEditor)
};
