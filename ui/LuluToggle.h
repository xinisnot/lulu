#pragma once
#include <JuceHeader.h>
#include "LuluComponentLookAndFeel.h"


class LuluToggle : public juce::Slider
{
public:
    LuluToggle()
    {
        setSliderStyle(juce::Slider::RotaryVerticalDrag);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    }
    
    void mouseDown(const juce::MouseEvent&) override
    {
        if(getValue() == 0.0)   setValue(1.0);
        else                    setValue(0.0);
    }
};
