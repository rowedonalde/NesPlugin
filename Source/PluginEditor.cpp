/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NesPluginAudioProcessorEditor::NesPluginAudioProcessorEditor (NesPluginAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Set up UI:
    keyboardSplitLabel.setText("Split Key", dontSendNotification);
    addAndMakeVisible(keyboardSplitLabel);

    addAndMakeVisible(keyboardSplitSlider);
    keyboardSplitSlider.setTextBoxIsEditable(false);
    keyboardSplitSlider.setNumDecimalPlacesToDisplay(0);
    keyboardSplitAttachment.reset (new SliderAttachment (valueTreeState, "splitKey", keyboardSplitSlider));

    triangleWaveOctavesUpLabel.setText("Triangle Wave Octave", dontSendNotification);
    addAndMakeVisible(triangleWaveOctavesUpLabel);

    addAndMakeVisible(triangleWaveOctavesUpSlider);
    triangleWaveOctavesUpSlider.setNumDecimalPlacesToDisplay(0);
    triangleWaveOctavesUpAttachment.reset (new SliderAttachment (valueTreeState, "triangleWaveOctavesUp", triangleWaveOctavesUpSlider));

    setSize (600, 100);
}

NesPluginAudioProcessorEditor::~NesPluginAudioProcessorEditor()
{
}

//==============================================================================
void NesPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void NesPluginAudioProcessorEditor::resized()
{
    keyboardSplitLabel.setBounds(10, 40, 90, 20);
    keyboardSplitSlider.setBounds(100, 40, getWidth() - 110, 20);

    triangleWaveOctavesUpLabel.setBounds(10, 70, 200, 20);
    triangleWaveOctavesUpSlider.setBounds(210, 70, getWidth() - 220, 20);
}
