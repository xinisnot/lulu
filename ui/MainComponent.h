#pragma once

#include <JuceHeader.h>
#include "LuluDial.h"
#include "LuluToggle.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"

class MainComponent  : public juce::Component, public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void setAudioProcessor(RNBO::JuceAudioProcessor *p);
    void updateSliderForParam(unsigned long index, double value);

private:
    LuluDial            sliderDrywet;
    LuluDial            sliderTriggerDensity;
    LuluDial            sliderTriggerProbability;
    LuluDial            sliderFeedbackAmount;
    LuluDial            sliderFeedbackDamp;
    LuluDial            sliderCloudPosition;
    LuluDial            sliderCloudPositionBlur;
    LuluDial            sliderCloudAmpBlur;
    LuluDial            sliderCloudGrainSize;
    LuluDial            sliderCloudGrainSizeBlur;
    LuluDial            sliderCloudWindowTilt;
    LuluDial            sliderCloudWindowSkirt;
    LuluDial            sliderCloudStereoSpread;
    LuluDial            sliderCloudPitchBlur;
    LuluDial            sliderCloudReverseProb;
    LuluToggle          toggleRecordFreeze;
    juce::Label         labelTitle              { "label", "lulu by @xinisnot" };
    LuluDialLaf         luluDialLaf             { false };
    LuluDialLaf         luluDialLaf_fromCenter  { true };
    LuluToggleLaf       luluToggleLaf;
    juce::TooltipWindow tooltipWindow;

    RNBO::JuceAudioProcessor* processor = nullptr;
    HashMap<int, juce::Slider*> slidersByParameterIndex; // used to map parameter index to slider we want to control
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
