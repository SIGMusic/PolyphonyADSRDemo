#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : audioSetupComp (audioDeviceManager, 0, 0, 0, 256,
                                                 true, // showMidiInputOptions must be true
                                                 true,
                                                 true,
                                                 false)
{
    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    audioDeviceManager.initialise (0, 2, nullptr, true, {}, nullptr);
    audioDeviceManager.addMidiInputDeviceCallback ({}, this);

    addAndMakeVisible(audioSetupComp);
    addAndMakeVisible(&synth_);

    attack_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attack_.setRange(0.0, 5.0);
    attack_.setValue(0.1);
    attack_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    decay_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decay_.setRange(0.0, 5.0);
    decay_.setValue(0.1);
    decay_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    sustain_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustain_.setRange(0.0, 1.0);
    sustain_.setValue(0.9);
    sustain_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    release_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    release_.setRange(0.0, 5.0);
    release_.setValue(0.1);
    release_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);

    addAndMakeVisible(attack_);
    addAndMakeVisible(decay_);
    addAndMakeVisible(sustain_);
    addAndMakeVisible(release_);

    attack_.addListener(this);
    decay_.addListener(this);
    sustain_.addListener(this);
    release_.addListener(this);

    // Make sure you set the size of the component after
    // you add any child components.
    setSize (kWindowWidth, 400 + kKeyboardHeight + kSliderHeight);
}

MainComponent::~MainComponent()
{
    audioDeviceManager.removeMidiInputDeviceCallback ({}, this);
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    synth_.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    synth_.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    synth_.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto local_bounds = getLocalBounds();
    synth_.setBounds(local_bounds.removeFromBottom(kKeyboardHeight));
    auto slider_bounds = local_bounds.removeFromBottom(kSliderHeight);
    for (auto* slider : {&attack_, &decay_, &sustain_, &release_})
    {
        slider->setBounds(slider_bounds.removeFromLeft(kSliderWidth));
    }
    audioSetupComp.setBounds(local_bounds);
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &attack_)
    {
        /*
        for (auto* voice : synth_.getVoices())
        {
            voice->setAttack(attack_.getValue());
        }
         */
    }
    else if (slider == &decay_)
    {
        */
        for (auto* voice : synth_.getVoices())
        {
            voice->setDecay(decay_.getValue());
        }
        */
    }
    else if (slider == &sustain_)
    {
        /*
        for (auto* voice : synth_.getVoices())
        {
            voice->setSustain(sustain_.getValue());
        }
         */
    }
    else if (slider == &release_)
    {
        /*
        for (auto* voice : synth_.getVoices())
        {
            voice->setRelease(release_.getValue());
        }
         */
    }
}
