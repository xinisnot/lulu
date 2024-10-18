#pragma once

#include <JuceHeader.h>
#include "LuluComponentLookAndFeel.h"


class LuluDial : public juce::Slider
{
public:
    LuluDial()
    {
        setSliderStyle(juce::Slider::RotaryVerticalDrag);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    }
    
    void mouseDoubleClick(const juce::MouseEvent&) override
    {
        if(getTextBoxPosition() == juce::Slider::NoTextBox)
        {
            setTextBoxStyle(juce::Slider::TextBoxBelow, false, getTextBoxWidth(), getTextBoxHeight());
            showTextBox();
        }
    }
};
