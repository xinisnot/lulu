#pragma once
#include <JuceHeader.h>


class LuluRangeDial : public juce::Slider
{
public:
    LuluRangeDial(juce::String title, double doubleClickReturnValue, juce::String tooltipText) : doubleClickReturnValue_(doubleClickReturnValue)
    {
        setTitle(title);
        setSliderStyle(juce::Slider::TwoValueVertical);
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


class LuluRangeDialLaf : public juce::LookAndFeel_V4
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
        float rotaryStartAngle          = slider.getRotaryParameters().startAngleRadians;
        float rotaryEndAngle            = slider.getRotaryParameters().endAngleRadians;
        float sliderPosMinProportional  = juce::jmap(slider.getMinValue(), slider.getMinimum(), slider.getMaximum(), 0.0, 1.0);
        float sliderPosMaxProportional  = juce::jmap(slider.getMaxValue(), slider.getMinimum(), slider.getMaximum(), 0.0, 1.0);
        
        auto outlineColour      = slider.findColour(juce::Slider::rotarySliderOutlineColourId).withAlpha(0.8f);
        auto thumbColour        = slider.findColour(juce::Slider::thumbColourId);
        auto bounds             = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);
        auto radius             = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto lineWeight         = juce::jmin(2.0f, radius * 0.5f);
        auto toAngleMin         = rotaryStartAngle + sliderPosMinProportional * (rotaryEndAngle - rotaryStartAngle);
        auto toAngleMax         = rotaryStartAngle + sliderPosMaxProportional * (rotaryEndAngle - rotaryStartAngle);
        auto arcRadius          = radius - lineWeight * 0.5f;
        auto insideArcRadius    = arcRadius - 5.0f;
        
        juce::Point<float> thumbMinStart(bounds.getCentreX() + insideArcRadius * std::cos(toAngleMin - juce::MathConstants<float>::halfPi),
                                         bounds.getCentreY() + insideArcRadius * std::sin(toAngleMin - juce::MathConstants<float>::halfPi));
        juce::Point<float> thumbMinEnd  (bounds.getCentreX() +       arcRadius * std::cos(toAngleMin - juce::MathConstants<float>::halfPi),
                                         bounds.getCentreY() +       arcRadius * std::sin(toAngleMin - juce::MathConstants<float>::halfPi));
        juce::Point<float> thumbMaxStart(bounds.getCentreX() + insideArcRadius * std::cos(toAngleMax - juce::MathConstants<float>::halfPi),
                                         bounds.getCentreY() + insideArcRadius * std::sin(toAngleMax - juce::MathConstants<float>::halfPi));
        juce::Point<float> thumbMaxEnd  (bounds.getCentreX() +       arcRadius * std::cos(toAngleMax - juce::MathConstants<float>::halfPi),
                                         bounds.getCentreY() +       arcRadius * std::sin(toAngleMax - juce::MathConstants<float>::halfPi));

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
        
        // draw range and thumb
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                toAngleMin,
                                toAngleMax,
                                true);
         
        g.setColour(thumbColour);
        g.strokePath(valueArc, juce::PathStrokeType (lineWeight, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        g.drawLine(juce::Line<float>(thumbMinStart, thumbMinEnd), lineWeight);
        g.drawLine(juce::Line<float>(thumbMaxStart, thumbMaxEnd), lineWeight);
        
        // draw slider name or value
        g.setFont(12.0f);
        g.setColour(juce::Colour(0xffffffff));
        
        if(slider.isMouseOverOrDragging())
        {
            double maxValue = std::trunc(slider.getMaxValue() * 1000) / 1000;
            double minValue = std::trunc(slider.getMinValue() * 1000) / 1000;
            
            g.drawText(juce::String(maxValue), 0, height/2 - 20, width, 20, juce::Justification::centred);
            g.drawText(juce::String(minValue), 0, height/2,      width, 20, juce::Justification::centred);
        }
        else
            g.drawText(slider.getTitle(), 0, height/2 - 10, width, 20, juce::Justification::centred);
    }
    
    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override
    {
        juce::Slider::SliderLayout layout;
        layout.textBoxBounds = juce::Rectangle<int>(0, 0);
        layout.sliderBounds  = slider.getLocalBounds();
        
        return layout;
    }
};
