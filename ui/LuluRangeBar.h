#pragma once

#include <JuceHeader.h>


class LuluRangeBar  : public juce::Slider
{
public:
    LuluRangeBar()
    {
        setSliderStyle(juce::Slider::TwoValueHorizontal);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    }

    ~LuluRangeBar() override
    {
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LuluRangeBar)
};


class LuluRangeBarLaf : public juce::LookAndFeel_V4
{
public:
    LuluRangeBarLaf() {};

    
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos,
                           float minSliderPos,
                           float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        float y0 = (float) height * 0.5f;
        juce::Point<float> minPoint (minSliderPos, y0);
        juce::Point<float> maxPoint (maxSliderPos, y0);
        
        // guide
        juce::Path guide;
        guide.startNewSubPath(juce::Point<float>(0, y0));
        guide.lineTo(juce::Point<float>(width, y0));
        g.setColour (juce::Colour(0xff74787a).withAlpha(0.1f));
        g.strokePath(guide, juce::PathStrokeType(1.0f));
        
        // range
        juce::Path range;
        range.startNewSubPath(minPoint);
        range.lineTo(maxPoint);
        g.setColour (juce::Colour(0xffd9dadb).withAlpha(0.2f));
        g.strokePath(range, juce::PathStrokeType(1.0f));

        // pointer
        juce::Rectangle<float> minPointArea (minPoint.translated(-3, 3), minPoint.translated(3, -3));
        juce::Rectangle<float> maxPointArea (maxPoint.translated(-3, 3), maxPoint.translated(3, -3));
        g.setColour (juce::Colour(0xffd9dadb));
        g.fillEllipse(minPointArea);
        g.fillEllipse(maxPointArea);
    }

    juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider) override
    {
        juce::Slider::SliderLayout layout;
        layout.sliderBounds = slider.getLocalBounds();
        return layout;
    }
};
