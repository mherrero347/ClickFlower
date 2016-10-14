/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FlowerBox.h"
#include "SmoothSine.h"

//==============================================================================

class MainContentComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible(f_box);
        setSize (900, 700);
        
        // specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        samplingRate = sampleRate;
        block_size = samplesPerBlockExpected;
        flower_sine.init(samplingRate);
        flower_sine.buildUserInterface(&flower_sine_control);
        flower_sine_control.setParamValue("/sine/freq", 0);
        flower_sine_control.setParamValue("/sine/gain", 0);
        flower_sine_control.setParamValue("/sine/gain", 1);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float gain_scalar = f_box.percentToLeft();
        float freq_scalar = f_box.percentToBottom();
        flower_sine_control.setParamValue("/sine/freq",max_freq*freq_scalar);
        flower_sine_control.setParamValue("/sine/gain",gain_scalar);
        float* buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        flower_sine.compute(block_size, NULL, &buffer);
    }
    
    void releaseResources() override
    {
        
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (Colour (0xff3a2513));
        
    }

    void resized() override
    {
        f_box.setBounds(getWidth()*.05, getHeight()*.05, getWidth()-(getWidth()*.1), getHeight()-(getHeight()*.1));
    }
    
private:
    //==============================================================================
    FlowerBox f_box;
    SmoothSine flower_sine;
    MapUI flower_sine_control;
    int max_freq = 2000;
    int samplingRate, block_size;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
