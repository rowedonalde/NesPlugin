/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
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

//    Slider gainSlider;
//    Label gainLabel;

    //Slider frequencySlider;
    //Label frequencyLabel;
    Slider keyboardSplitSlider;
    Label keyboardSplitLabel;
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> keyboardSplitAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NesPluginAudioProcessorEditor)
};
