/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "LuluDial.h"
#include "LuluRangeDial.h"
#include "LuluRangeSlider.h"
#include "LuluToggle.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RootComponent  : public juce::Component,
                       public juce::Slider::Listener
{
public:
    //==============================================================================
    RootComponent ();
    ~RootComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void setAudioProcessor(RNBO::JuceAudioProcessor *p);
    void updateSliderForParam(unsigned long index, double value);
    void setLuluDialValue(RNBO::CoreObject& coreObject, juce::Slider* slider, unsigned long index, double interval);
    void luluDialValueChanged(RNBO::CoreObject& coreObject, juce::Slider* sliderThatWasMoved, RNBO::ParameterIndex index);
    void luluRangeUiValueChanged(RNBO::CoreObject& coreObject, juce::Slider* sliderThatWasMoved, RNBO::ParameterIndex index_min, RNBO::ParameterIndex index_max);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    RNBO::JuceAudioProcessor *processor = nullptr;
    HashMap<int, Slider *> slidersByParameterIndex; // used to map parameter index to slider we want to control

    LuluDialLaf             luluDialLaf { findColour(juce::Slider::thumbColourId) };
    LuluDialLaf             luluDialLaf_feedback { juce::Colour(0xffc03652) };
    LuluDialLaf_DrawValue   luluDialLaf_drawValue { findColour(juce::Slider::thumbColourId) };
    LuluDialLaf_DrawValue   luluDialLaf_drawValue_feedback { juce::Colour(0xffc03652) };
    LuluDialLaf_FilterType  luluDialLaf_filterType { juce::Colour(0xffc03652) };
    LuluToggleLaf           luluToggleLaf { findColour(juce::Slider::thumbColourId) };
    LuluRangeDialLaf        luluRangeDialLaf;
    LuluRangeSliderLaf      luluRangeSliderLaf;
    TooltipWindow           tooltipWindow;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<LuluDial> juce__component;
    std::unique_ptr<LuluDial> juce__component2;
    std::unique_ptr<LuluDial> juce__component3;
    std::unique_ptr<LuluDial> juce__component4;
    std::unique_ptr<LuluDial> juce__component5;
    std::unique_ptr<LuluDial> juce__component6;
    std::unique_ptr<LuluDial> juce__component7;
    std::unique_ptr<LuluDial> juce__component8;
    std::unique_ptr<LuluDial> juce__component9;
    std::unique_ptr<LuluDial> juce__component10;
    std::unique_ptr<LuluDial> juce__component11;
    std::unique_ptr<LuluToggle> juce__component12;
    std::unique_ptr<LuluToggle> juce__component13;
    std::unique_ptr<LuluRangeDial> juce__component14;
    std::unique_ptr<LuluRangeDial> juce__component15;
    std::unique_ptr<LuluRangeSlider> juce__component17;
    std::unique_ptr<LuluRangeSlider> juce__component16;
    std::unique_ptr<juce::Label> juce__label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RootComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

