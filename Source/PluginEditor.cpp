/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NesPluginAudioProcessorEditor::NesPluginAudioProcessorEditor (NesPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Set up UI:
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    gainLabel.setText ("Volume", dontSendNotification);

    //frequencySlider.setRange(10, 2000);
    // Setting max to 55.9 kHz per triangle generator on NES:
    frequencySlider.setRange(1, 55900);
    frequencySlider.setSkewFactorFromMidPoint(1000.0);
    frequencySlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    frequencyLabel.setText("Frequency", dontSendNotification);

    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(frequencySlider);
    addAndMakeVisible(frequencyLabel);

    gainSlider.addListener(this);
    frequencySlider.addListener(this);

    // TODO set value via processor
    gainSlider.setValue(p.getMasterGain());
    frequencySlider.setValue(p.getTriangleFrequency());

    setSize (600, 100);
}

NesPluginAudioProcessorEditor::~NesPluginAudioProcessorEditor()
{
}

//==============================================================================
void NesPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void NesPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainLabel.setBounds(10, 10, 90, 20);
    gainSlider.setBounds(100, 10, getWidth() - 110, 20);

    frequencyLabel.setBounds(10, 40, 90, 20);
    frequencySlider.setBounds(100, 40, getWidth() - 110, 20);
}

void NesPluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    processor.setMasterGain(gainSlider.getValue());
    processor.setTriangleFrequency(frequencySlider.getValue());
}
