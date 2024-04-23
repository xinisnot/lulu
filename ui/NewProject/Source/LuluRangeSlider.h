#pragma once
#include <JuceHeader.h>


class LuluRangeSlider : public juce::Slider
{
public:
    LuluRangeSlider(juce::String title, double doubleClickReturnValue, juce::String tooltipText) : doubleClickReturnValue_(doubleClickReturnValue)
    {
        setTitle(title);
        setSliderStyle(juce::Slider::TwoValueHorizontal);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        setTooltip(tooltipText);
    }
    
    void mouseDoubleClick(const juce::MouseEvent&) override
    {
        setMaxValue(doubleClickReturnValue_);
        setMinValue(doubleClickReturnValue_);
    }
    
private:
    double doubleClickReturnValue_;
};


//==============================================================================


class LuluRangeSliderLaf : public juce::LookAndFeel_V4
{
public:
    void drawLinearSlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPos,
                          float minSliderPos,
                          float maxSliderPos,
                          juce::Slider::SliderStyle,
                          juce::Slider& slider) override
    {
        auto trackWidth    = juce::jmin (2.0f, (float) height * 0.25f);
        auto outlineColour = slider.findColour(juce::Slider::rotarySliderOutlineColourId).withBrightness(0.27f);
        auto valueColour   = slider.findColour(juce::Slider::thumbColourId);

        juce::Point<float> startPoint ((float) x, (float) y + (float) height * 0.5f);
        juce::Point<float> endPoint   ((float) (width + x), startPoint.y);

        // draw background
        juce::Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (outlineColour);
        g.strokePath (backgroundTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

        // draw value and thumb
        juce::Path valueTrack;
        juce::Point<float> minPoint = { minSliderPos, (float) height * 0.5f };
        juce::Point<float> maxPoint = { maxSliderPos, (float) height * 0.5f };

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (maxPoint);
        g.setColour (valueColour);
        g.strokePath (valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });
        g.drawEllipse(juce::Rectangle<float>(5.0f, 5.0f).withCentre(maxPoint), trackWidth);
        g.drawEllipse(juce::Rectangle<float>(5.0f, 5.0f).withCentre(minPoint), trackWidth);
        
        // draw slider name or value
        g.setFont(12.0f);
        g.setColour(juce::Colour(0xffffffff));
        g.drawText(slider.getTitle(), 0, height/2 - 10, width, 20, juce::Justification::centred);
        
        if (slider.isMouseOverOrDragging())
        {
            double maxValue = std::trunc(slider.getMaxValue() * 1000) / 1000;
            double minValue = std::trunc(slider.getMinValue() * 1000) / 1000;

            g.drawText(juce::String(minValue), 0, 0, width, height, juce::Justification::centredLeft);
            g.drawText(juce::String(maxValue), 0, 0, width, height, juce::Justification::centredRight);
        }
    }
    
    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override
    {
        juce::Slider::SliderLayout layout;
        layout.textBoxBounds = juce::Rectangle<int>(0, 0);
        layout.sliderBounds  = slider.getLocalBounds();
        
        return layout;
    }
};
