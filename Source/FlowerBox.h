/*
  ==============================================================================

    FlowerBox.h
    Created: 13 Oct 2016 6:12:43pm
    Author:  Matthew Herrero

  ==============================================================================
*/

#ifndef FLOWERBOX_H_INCLUDED
#define FLOWERBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <string>

//==============================================================================
/*
*/
class FlowerBox    : public Component,
                     public Timer
{
public:
    FlowerBox()
    {
        startTimerHz(60);
    }
    
    ~FlowerBox()
    {
        
    }
    
    void paint (Graphics& g) override
    {
        g.setColour (Colour (0xffe0ac7f));
        g.fillAll ();
        if(flower_visible) {
            g.setColour (Colour::fromString((StringRef)"FF" + std::to_string(current_color)));
            g.fillEllipse (flower_current.x-30, flower_current.y-30, 60, 60);
        }
    }
    
    void resized() override
    {
        
    }
    
    float percentToLeft() {
        return flower_current.x/getWidth();
    }
    
    float percentToBottom() {
        return (getHeight() - flower_current.y)/getHeight();
    }
    
    void mouseDown(const MouseEvent& event) override
    {
        flower_current = event.position;
        current_color = random.nextInt(1000000);
        flower_visible = true;
    }
    
    void timerCallback() override
    {
        repaint();
    }
    
private:
    bool flower_visible = false;
    int current_color;
    Point<float> flower_current = {0,0};
    Random random;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlowerBox)
};


#endif  // FLOWERBOX_H_INCLUDED
