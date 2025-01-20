#pragma once

#include <JuceHeader.h>
#include "LuluDial.h"
#include "LuluToggle.h"
#include "LuluOscilloscope.h"
#include "LuluRangeSlider.h"
#include "LuluRangeBar.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"

class MainComponent  : public juce::Component, public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void setAudioProcessor(RNBO::JuceAudioProcessor *p);
    void updateSliderForParam(unsigned long index, double value);

private:
    LuluDial            sliderMixerDry;
    LuluDial            sliderMixerWet;
    LuluDial            sliderTriggerDensity;
    LuluDial            sliderTriggerProbability;
    LuluDial            sliderFeedbackAmount;
    LuluDial            sliderFeedbackDamp;
    LuluDial            sliderCloudAmpBlur;
    LuluDial            sliderCloudGrainSize1;
    LuluDial            sliderCloudGrainSize2;
    LuluDial            sliderCloudWindowTilt;
    LuluDial            sliderCloudWindowSkirt;
    LuluDial            sliderCloudStereoSpread;
    LuluDial            sliderCloudPitchBlur;
    LuluDial            sliderCloudReverseProb;
    LuluDial            sliderEnvelopeAttack;
    LuluDial            sliderEnvelopeRelease;
    LuluToggle          toggleRecordFreeze;
    LuluRangeSlider     rangeSliderCloudPosition;
    LuluDial            sliderCloudPosition1;
    LuluDial            sliderCloudPosition2;
    LuluRangeBar        rangeBarCloudGrainSize;
    
    std::unique_ptr<float[]> scopeBuffer;
    std::unique_ptr<float[]> indexBuffer;
    LuluOscilloscope    scope;

    LuluDialLaf         luluDialLaf             { false };
    LuluDialLaf         luluDialLaf_fromCenter  { true };
    LuluToggleLaf       luluToggleLaf;
    LuluRangeSliderLaf  luluRangeSliderLaf;
    LuluRangeBarLaf     luluRangeBarLaf;

    juce::Label         labelTitle { "label", "lulu by @xinisnot" };
    juce::TooltipWindow tooltipWindow;

    RNBO::JuceAudioProcessor* processor = nullptr;
    HashMap<int, juce::Slider*> slidersByParameterIndex; // used to map parameter index to slider we want to control
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
