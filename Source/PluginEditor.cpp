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
//    gainSlider.setRange(0.0, 1.0, 1);
//    gainSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
//    gainLabel.setText ("Volume", dontSendNotification);

//    keyboardSplitSlider.setRange(0, 127);
//    keyboardSplitSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
//    keyboardSplitSlider.setNumDecimalPlacesToDisplay(0);
//    keyboardSplitLabel.setText("Split Key", dontSendNotification);

//    addAndMakeVisible(gainSlider);
//    addAndMakeVisible(gainLabel);
//    addAndMakeVisible(keyboardSplitSlider);
//    addAndMakeVisible(keyboardSplitLabel);

    keyboardSplitLabel.setText("Split Key", dontSendNotification);
    addAndMakeVisible(keyboardSplitLabel);

    addAndMakeVisible(keyboardSplitSlider);
    keyboardSplitSlider.setNumDecimalPlacesToDisplay(0);
    keyboardSplitAttachment.reset (new SliderAttachment (valueTreeState, "splitKey", keyboardSplitSlider));

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
}
