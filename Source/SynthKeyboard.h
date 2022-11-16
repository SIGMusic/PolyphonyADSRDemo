/*
  ==============================================================================

    SynthKeyboard.h
    Created: 18 Sep 2022 2:53:48am
    Author:  Andrew Orals

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WavetableSynth.h"

#include <map>

using std::unordered_map;

//==============================================================================
/*
*/
class SynthKeyboard  : public juce::Component,
                       public juce::MidiKeyboardState::Listener,
                       public juce::AudioSource
{
public:
    SynthKeyboard()
    {
        midi_keyboard_state_.addListener(this);
        midi_keyboard_.reset(new juce::MidiKeyboardComponent(midi_keyboard_state_,
                            juce::KeyboardComponentBase::Orientation::horizontalKeyboard));
        addAndMakeVisible(midi_keyboard_.get());

        for (int voice_idx = 0; voice_idx < max_voices_; ++voice_idx)
        {
            auto* synth = new WavetableSynth();
            mixer_.addInputSource(synth, false);
            free_voices_[num_free_voices_++] = synth;
            voices_.add(synth);
        }
    }

    virtual ~SynthKeyboard() = default;

    //==========================================================================
    // External MIDI

    void processMIDIMessage(const juce::MidiMessage& message)
    {
        if (message.isNoteOn())
        {
            /* TODO
            handleNoteOn(nullptr,
                         message.getChannel(),
                         message.getNoteNumber(),
                         message.getVelocity());
                         */
        }
        else if (message.isNoteOff())
        {
            /* TODO
            handleNoteOff(nullptr,
                          message.getChannel(),
                          message.getNoteNumber(),
                          message.getVelocity());
                          */
        }
    }
 

    //==========================================================================
    // AudioSource
 
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        mixer_.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
 
    virtual void releaseResources() override
    {
        mixer_.releaseResources();
    }

    virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        mixer_.getNextAudioBlock(bufferToFill);
    }

    //==========================================================================
    // MidiKeyboardState::Listener

    static constexpr inline float midiToFreq(juce::uint8 midi_note)
    {
        return 440.0 * std::pow(2.0, (midi_note - 69) / 12.0);
    }

    virtual void handleNoteOn(juce::MidiKeyboardState *source,
                              int midiChannel,
                              int midiNoteNumber,
                              float velocity) override
    {
        // TODO
    }

    virtual void handleNoteOff(juce::MidiKeyboardState *source,
                               int midiChannel,
                               int midiNoteNumber,
                               float velocity) override
    {
        // TODO
    }

    //==========================================================================
    // Component

    void paint (juce::Graphics& g) override { /* Nothing */ }

    void resized() override
    {
        midi_keyboard_->setBounds(getLocalBounds());
    }

private:
    // TODO
    static const int max_voices_ = 8;
    juce::OwnedArray<WavetableSynth> voices_;
    juce::MixerAudioSource mixer_;

    int num_free_voices_ = 0;
    WavetableSynth* free_voices_[max_voices_];
    unordered_map<int, WavetableSynth*> voice_mapping_;

    juce::MidiKeyboardState midi_keyboard_state_;
    std::unique_ptr<juce::MidiKeyboardComponent> midi_keyboard_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthKeyboard)
};
