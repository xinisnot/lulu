#pragma once

#include <JuceHeader.h>


class LuluRangeSlider  : public juce::Slider
{
public:
    LuluRangeSlider()
    {
        setSliderStyle(juce::Slider::TwoValueHorizontal);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    }

    ~LuluRangeSlider() override
    {
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LuluRangeSlider)
};



class LuluRangeSliderLaf : public juce::LookAndFeel_V4
{
public:
    LuluRangeSliderLaf() {};

    
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos,
                           float minSliderPos,
                           float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        juce::Point<float> minPoint (minSliderPos, (float) height);
        juce::Point<float> maxPoint (maxSliderPos, (float) 0.0f);
        juce::Rectangle<float> range(minPoint, maxPoint);

        g.setColour (juce::Colour(0xff74787a).withAlpha(0.1f));
        g.fillRect (range);
        
        juce::Path center;
        float center_x = (minPoint.getX() + maxPoint.getX()) * 0.5f;

        center.startNewSubPath(minPoint.withX(center_x));
        center.lineTo(maxPoint.withX(center_x));

        g.setColour (juce::Colour(0xffd9dadb).withAlpha(0.05f));
        g.strokePath(center, juce::PathStrokeType(1.0f));

        juce::Rectangle<float> minPointArea (minPoint.translated(-5, 5), minPoint.translated(5, -5));
        juce::Rectangle<float> maxPointArea (maxPoint.translated(-5, 5), maxPoint.translated(5, -5));
        g.setColour (juce::Colour(0xffd9dadb));
        g.fillEllipse(minPointArea);
        g.fillEllipse(maxPointArea);
    }

    juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider)
    {
        juce::Slider::SliderLayout layout;
        layout.sliderBounds = slider.getLocalBounds();
        return layout;
    }
};