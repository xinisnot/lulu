#pragma once
#include <JuceHeader.h>


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


class LuluToggleLaf : public juce::LookAndFeel_V4
{
public:
    LuluToggleLaf() {};

    void drawRotarySlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        auto outlineColour      = slider.findColour(juce::Slider::rotarySliderOutlineColourId).withBrightness(0.27f);
        auto bounds             = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);
        auto radius             = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto lineWeight         = juce::jmin(2.0f, radius * 0.5f);
        auto toAngle            = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        auto arcRadius          = radius - lineWeight * 0.5f;
        auto insideArcRadius    = arcRadius - 5.0f;
        
        juce::Point<float> thumbStart(bounds.getCentreX() + insideArcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
                                      bounds.getCentreY() + insideArcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));
        juce::Point<float> thumbEnd  (bounds.getCentreX() +       arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
                                      bounds.getCentreY() +       arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

        // draw outline
        juce::Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    insideArcRadius,
                                    insideArcRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    rotaryEndAngle,
                                    true);

        g.setColour(outlineColour);
        g.strokePath(backgroundArc, juce::PathStrokeType(lineWeight, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
        // draw led
        if(((int)slider.getValue()) == 1)
        {
            juce::Path led;
            led.addCentredArc(bounds.getCentreX(),
                              bounds.getCentreY(),
                              arcRadius,
                              arcRadius,
                              0.0f,
                              0.0f,
                              juce::MathConstants<float>::twoPi,
                              true);
            
            g.setColour(juce::Colour(0xff2c678a));
            g.strokePath(led, juce::PathStrokeType(lineWeight, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
        
        // draw slider name or value
        g.setFont(10.0f);
        g.setColour(juce::Colour(0xffd0d0d0));
        g.drawText(slider.getTitle(), 0, height/2 - 10, width, 20, juce::Justification::centred);
    }


    juce::Label* createSliderTextBox(juce::Slider& slider) override
    {
        auto* l = juce::LookAndFeel_V4::createSliderTextBox(slider);
        
        l->setFont(l->getFont().withHeight(10.0f));
        l->onEditorHide = [&slider, l] {
            slider.setValue(l->getText().getDoubleValue());
            slider.setTextBoxStyle(juce::Slider::NoTextBox, false, slider.getTextBoxWidth(), slider.getTextBoxHeight());
        };
        
        return l;
    }
};
