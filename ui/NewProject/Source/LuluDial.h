#pragma once
#include <JuceHeader.h>


class LuluDial : public juce::Slider
{
public:
    LuluDial(juce::String title, juce::String tooltipText)
    {
        setTitle(title);
        setSliderStyle(juce::Slider::RotaryVerticalDrag);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
        setTooltip(tooltipText);
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


//==============================================================================


class LuluDialLaf : public juce::LookAndFeel_V4
{
public:
    LuluDialLaf(juce::Colour accentColour) : accentColour_(accentColour) {};

    virtual void drawRotarySlider(juce::Graphics& g,
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
        
        juce::Point<float> thumbPoint(bounds.getCentreX() + insideArcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
                                      bounds.getCentreY() + insideArcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));
        
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
        g.setColour(getAccentColour());
        g.drawEllipse(juce::Rectangle<float>(5.0f, 5.0f).withCentre(thumbPoint), lineWeight);
        
        // draw slider name or value
        g.setFont(12.0f);
        g.setColour(juce::Colour(0xffffffff));
        
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
        
        l->setFont(l->getFont().withHeight(12.0f));
        l->onEditorHide = [&slider, l] {
            slider.setValue(l->getText().getDoubleValue());
            slider.setTextBoxStyle(juce::Slider::NoTextBox, false, slider.getTextBoxWidth(), slider.getTextBoxHeight());
        };
        
        return l;
    }

    juce::Colour getAccentColour()
    {
        return accentColour_;
    }

private:
    juce::Colour accentColour_;
};


//==============================================================================


class LuluDialLaf_DrawValue : public LuluDialLaf
{
public:
    LuluDialLaf_DrawValue(juce::Colour accentColour) : LuluDialLaf(accentColour) {};

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
        
        // draw thumb
        g.setColour(getAccentColour());
        g.drawLine(juce::Line<float>(thumbStart, thumbEnd), lineWeight);

        // draw value
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
                               bounds.getCentreY(),
                               arcRadius,
                               arcRadius,
                               0.0f,
                               rotaryStartAngle,
                               toAngle,
                               true);
        
        g.strokePath (valueArc, juce::PathStrokeType (lineWeight, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        // draw slider name or value
        g.setFont(12.0f);
        g.setColour(juce::Colour(0xffffffff));
        
        if(slider.isMouseOverOrDragging())
        {
            double value = std::trunc(slider.getValue() * 1000) / 1000;
            g.drawText(juce::String(value), 0, height/2 - 10, width, 20, juce::Justification::centred);
        }
        else
            g.drawText(slider.getTitle(), 0, height/2 - 10, width, 20, juce::Justification::centred);
    }
};


//==============================================================================


class LuluDialLaf_FilterType : public LuluDialLaf
{
public:
    LuluDialLaf_FilterType(juce::Colour accentColour) : LuluDialLaf(accentColour) {};
    
    virtual void drawRotarySlider(juce::Graphics& g,
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

        float thumbDiam = thumbStart.getDistanceFrom(thumbEnd);
        
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
        g.setColour(getAccentColour());
        g.drawEllipse(juce::Rectangle<float>(thumbDiam, thumbDiam).withCentre(thumbStart), lineWeight);
        
        // draw slider name or value
        g.setFont(12.0f);
        g.setColour(juce::Colour(0xffffffff));
        
        if(slider.isMouseOverOrDragging())
        {
            int value = (int) slider.getValue();
            juce::String type;
            
            switch(value)
            {
                case 0: type = "bypass";   break;
                case 1: type = "lowpass";  break;
                case 2: type = "highpass"; break;
                case 3: type = "bandpass"; break;
                default: break;
            }
            
            g.drawText(type, 0, height/2 - 10, width, 20, juce::Justification::centred);
        }
        else
            g.drawText(slider.getTitle(), 0, height/2 - 10, width, 20, juce::Justification::centred);
    }
};
