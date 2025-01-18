#pragma once

#include <JuceHeader.h>


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


class LuluDialLaf : public juce::LookAndFeel_V4
{
public:
    LuluDialLaf(bool fromCenter) : fromCenter_(fromCenter) {};

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
        
        // draw thumb
        juce::Point<float> thumbStart(bounds.getCentreX() + arcRadius * 0.92f * std::cos(toAngle - juce::MathConstants<float>::halfPi),
                                      bounds.getCentreY() + arcRadius * 0.92f * std::sin(toAngle - juce::MathConstants<float>::halfPi));
        juce::Point<float> thumbEnd  (bounds.getCentreX() + arcRadius         * std::cos(toAngle - juce::MathConstants<float>::halfPi),
                                      bounds.getCentreY() + arcRadius         * std::sin(toAngle - juce::MathConstants<float>::halfPi));


        g.setColour(juce::Colour(0xff2c678a));
        g.drawLine(juce::Line<float>(thumbStart, thumbEnd), lineWeight);

        // draw value
        juce::Path valueArc;

        if(fromCenter_) {
            valueArc.addCentredArc(bounds.getCentreX(),
                        bounds.getCentreY(),
                        arcRadius,
                        arcRadius,
                        0.0f,
                        toAngle,
                        juce::MathConstants<float>::twoPi,
                        true);
        }
        else {
            valueArc.addCentredArc(bounds.getCentreX(),
                        bounds.getCentreY(),
                        arcRadius,
                        arcRadius,
                        0.0f,
                        rotaryStartAngle,
                        toAngle,
                        true);
        }

        g.strokePath (valueArc, juce::PathStrokeType (lineWeight, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
        // draw slider name or value
        g.setFont(10.0f);
        g.setColour(juce::Colour(0xffd0d0d0));
        
        if(slider.isMouseOverOrDragging())
        {
            double value = std::trunc(slider.getValue() * 1000) / 1000;
            g.drawText(juce::String(value), 0, height/2 - 10, width, 20, juce::Justification::centred);
        }
        else
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

private:
    bool fromCenter_;
};