#include <JuceHeader.h>
#include "MainComponent.h"


MainComponent::MainComponent()
{
    setSize(700, 400);
    addAndMakeVisible(sliderTriggerDensity);
    addAndMakeVisible(sliderTriggerProbability);
    addAndMakeVisible(sliderFeedbackAmount);
    addAndMakeVisible(sliderFeedbackDamp);
    addAndMakeVisible(toggleRecordFreeze);
    addAndMakeVisible(sliderMixerDry);
    addAndMakeVisible(sliderMixerWet);
    addAndMakeVisible(sliderCloudAmpBlur);
    addAndMakeVisible(sliderCloudGrainSize1);
    addAndMakeVisible(sliderCloudGrainSize2);
    addAndMakeVisible(sliderCloudWindowTilt);
    addAndMakeVisible(sliderCloudWindowSkirt);
    addAndMakeVisible(sliderCloudStereoSpread);
    addAndMakeVisible(sliderCloudPitchBlur);
    addAndMakeVisible(sliderCloudReverseProb);
    addAndMakeVisible(sliderEnvelopeAttack);
    addAndMakeVisible(sliderEnvelopeRelease);
    addAndMakeVisible(scope);
    addAndMakeVisible(rangeSliderCloudPosition);
    addAndMakeVisible(rangeBarCloudGrainSize);
    addAndMakeVisible(sliderCloudPosition1);
    addAndMakeVisible(sliderCloudPosition2);
    addAndMakeVisible(labelTitle);
    
    sliderTriggerDensity.setBounds    (0,    0, 70,  70);
    sliderTriggerProbability.setBounds(70,   0, 70,  70);
    sliderCloudReverseProb.setBounds  (140,  0, 70,  70);
    sliderCloudGrainSize1.setBounds   (210,  0, 70,  70);
    sliderCloudGrainSize2.setBounds   (280,  0, 70,  70);
    sliderCloudPosition1.setBounds    (350,  0, 70,  70);
    sliderCloudPosition2.setBounds    (420,  0, 70,  70);
    sliderCloudStereoSpread.setBounds (490,  0, 70,  70);
    sliderCloudAmpBlur.setBounds      (560,  0, 70,  70);
    sliderCloudPitchBlur.setBounds    (630,  0, 70,  70);
    sliderEnvelopeAttack.setBounds    (0,   70, 70,  70);
    sliderEnvelopeRelease.setBounds   (70,  70, 70,  70);
    sliderCloudWindowTilt.setBounds   (140, 70, 70,  70);
    sliderCloudWindowSkirt.setBounds  (210, 70, 70,  70);
    sliderFeedbackAmount.setBounds    (280, 70, 70,  70);
    sliderFeedbackDamp.setBounds      (350, 70, 70,  70);
    toggleRecordFreeze.setBounds      (490, 70, 70,  70);
    sliderMixerDry.setBounds          (560, 70, 70,  70);
    sliderMixerWet.setBounds          (630, 70, 70,  70);
    rangeBarCloudGrainSize.setBounds  (0,  140, 700, 20);
    scope.setBounds                   (0,  160, 700, 240);
    rangeSliderCloudPosition.setBounds(0,  160, 700, 240);
    labelTitle.setBounds              (0,  387, 700, 13);

    labelTitle.setFont(juce::Font (10.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    labelTitle.setJustificationType (juce::Justification::topRight);
    labelTitle.setEditable(false, false, false);
    labelTitle.setColour(juce::Label::backgroundColourId, juce::Colour (0x00000000));
    labelTitle.setColour(juce::Label::textColourId, juce::Colour(0xff606060));
    
    sliderTriggerDensity.setTitle    ("density");
    sliderTriggerProbability.setTitle("prob");
    sliderFeedbackAmount.setTitle    ("feedback");
    sliderFeedbackDamp.setTitle      ("damp");
    toggleRecordFreeze.setTitle      ("freeze");
    sliderMixerDry.setTitle          ("dry");
    sliderMixerWet.setTitle          ("wet");
    sliderCloudPosition1.setTitle    ("pos1");
    sliderCloudPosition2.setTitle    ("pos2");
    sliderCloudAmpBlur.setTitle      ("ampBlur");
    sliderCloudGrainSize1.setTitle   ("size1");
    sliderCloudGrainSize2.setTitle   ("size2");
    sliderCloudWindowTilt.setTitle   ("tilt");
    sliderCloudWindowSkirt.setTitle  ("skirt");
    sliderCloudStereoSpread.setTitle ("stereo");
    sliderCloudPitchBlur.setTitle    ("pitchBlur");
    sliderCloudReverseProb.setTitle  ("reverse");
    sliderEnvelopeAttack.setTitle    ("attack");
    sliderEnvelopeRelease.setTitle   ("release");
    
    sliderTriggerDensity.setName    ("trigger/density");
    sliderTriggerProbability.setName("trigger/probability");
    sliderFeedbackAmount.setName    ("feedback/amount");
    sliderFeedbackDamp.setName      ("feedback/damp");
    toggleRecordFreeze.setName      ("record/freeze");
    sliderMixerDry.setName          ("mixer/dry");
    sliderMixerWet.setName          ("mixer/wet");
    sliderCloudPosition1.setName    ("cloud/position1");
    sliderCloudPosition2.setName    ("cloud/position2");
    sliderCloudAmpBlur.setName      ("cloud/amp_blur");
    sliderCloudGrainSize1.setName   ("cloud/grain_size1");
    sliderCloudGrainSize2.setName   ("cloud/grain_size2");
    sliderCloudWindowTilt.setName   ("cloud/window_tilt");
    sliderCloudWindowSkirt.setName  ("cloud/window_skirt");
    sliderCloudStereoSpread.setName ("cloud/stereo_spread");
    sliderCloudPitchBlur.setName    ("cloud/pitch_blur");
    sliderCloudReverseProb.setName  ("cloud/reverse_prob");
    sliderEnvelopeAttack.setName    ("envelope/attack");
    sliderEnvelopeRelease.setName   ("envelope/release");
    
    sliderTriggerDensity.setTooltip    ("[trigger/denstity] Frequency of generating grain. (unit: Hz)");
    sliderTriggerProbability.setTooltip("[trigger/probability] Probability of generating grain.");
    sliderFeedbackAmount.setTooltip    ("[feedback/amount] Amount of grain feedback. (unit: dB)");
    sliderFeedbackDamp.setTooltip      ("[feedback/damp] Normalized Cutoff frequency of feedback.");
    toggleRecordFreeze.setTooltip      ("[record/freeze] Pause recording.");
    sliderMixerDry.setTooltip          ("[mixer/dry] Pre fx. (unit: dB)");
    sliderMixerWet.setTooltip          ("[mixer/wet] Post fx. (unit: dB)");
    rangeSliderCloudPosition.setTooltip("[cloud/position1][cloud/position2] Position of generating grain. (unit: msec)");
    sliderCloudPosition1.setTooltip    ("[cloud/position1] Position of generating grain. (unit: msec)");
    sliderCloudPosition2.setTooltip    ("[cloud/position2] Position of generating grain. (unit: msec)");
    sliderCloudAmpBlur.setTooltip      ("[cloud/amp_blur] Amount of grain amplitude blurring.");
    sliderCloudGrainSize1.setTooltip   ("[cloud/grain_size1] Grain size. (unit: msec)");
    sliderCloudGrainSize2.setTooltip   ("[cloud/grain_size2] Grain size. (unit: msec)");
    sliderCloudWindowTilt.setTooltip   ("[cloud/window_tilt] Shaping of grain window.");
    sliderCloudWindowSkirt.setTooltip  ("[cloud/window_skirt] Shaping of grain window.");
    sliderCloudStereoSpread.setTooltip ("[cloud/stereo_spread] Amount of stereo spread.");
    sliderCloudPitchBlur.setTooltip    ("[cloud/pitch_blur] Amount of grain pitch blurring. (unit: cent)");
    sliderCloudReverseProb.setTooltip  ("[cloud/reverse_prob] Probability of grain playing backwards.");
    sliderEnvelopeAttack.setTooltip    ("[envelope/attack] Attack time. (unit: msec)");
    sliderEnvelopeRelease.setTooltip   ("[envelope/release] Release time. (unit: msec)");
    rangeBarCloudGrainSize.setTooltip  ("[cloud/grain_size1][cloud/grain_size2] Grain size. (unit: msec)");
    
    sliderTriggerDensity.setLookAndFeel    (&luluDialLaf);
    sliderTriggerProbability.setLookAndFeel(&luluDialLaf);
    sliderFeedbackAmount.setLookAndFeel    (&luluDialLaf);
    sliderFeedbackDamp.setLookAndFeel      (&luluDialLaf);
    toggleRecordFreeze.setLookAndFeel      (&luluToggleLaf);
    sliderMixerDry.setLookAndFeel          (&luluDialLaf);
    sliderMixerWet.setLookAndFeel          (&luluDialLaf);
    sliderCloudAmpBlur.setLookAndFeel      (&luluDialLaf);
    sliderCloudGrainSize1.setLookAndFeel   (&luluDialLaf);
    sliderCloudGrainSize2.setLookAndFeel   (&luluDialLaf);
    sliderCloudWindowTilt.setLookAndFeel   (&luluDialLaf_fromCenter);
    sliderCloudWindowSkirt.setLookAndFeel  (&luluDialLaf_fromCenter);
    sliderCloudStereoSpread.setLookAndFeel (&luluDialLaf);
    sliderCloudPitchBlur.setLookAndFeel    (&luluDialLaf);
    sliderCloudReverseProb.setLookAndFeel  (&luluDialLaf);
    sliderEnvelopeAttack.setLookAndFeel    (&luluDialLaf);
    sliderEnvelopeRelease.setLookAndFeel   (&luluDialLaf);
    rangeSliderCloudPosition.setLookAndFeel(&luluRangeSliderLaf);
    sliderCloudPosition1.setLookAndFeel    (&luluDialLaf);
    sliderCloudPosition2.setLookAndFeel    (&luluDialLaf);
    rangeBarCloudGrainSize.setLookAndFeel  (&luluRangeBarLaf);

    sliderTriggerDensity.addListener    (this);
    sliderTriggerProbability.addListener(this);
    sliderFeedbackAmount.addListener    (this);
    sliderFeedbackDamp.addListener      (this);
    toggleRecordFreeze.addListener      (this);
    sliderMixerDry.addListener          (this);
    sliderMixerWet.addListener          (this);
    sliderCloudAmpBlur.addListener      (this);
    sliderCloudGrainSize1.addListener   (this);
    sliderCloudGrainSize2.addListener   (this);
    sliderCloudWindowTilt.addListener   (this);
    sliderCloudWindowSkirt.addListener  (this);
    sliderCloudStereoSpread.addListener (this);
    sliderCloudPitchBlur.addListener    (this);
    sliderCloudReverseProb.addListener  (this);
    sliderEnvelopeAttack.addListener    (this);
    sliderEnvelopeRelease.addListener   (this);
    rangeSliderCloudPosition.addListener(this);
    sliderCloudPosition1.addListener    (this);
    sliderCloudPosition2.addListener    (this);
    rangeBarCloudGrainSize.addListener  (this);
}

MainComponent::~MainComponent()
{
    sliderTriggerDensity.setLookAndFeel    (nullptr);
    sliderTriggerProbability.setLookAndFeel(nullptr);
    sliderFeedbackAmount.setLookAndFeel    (nullptr);
    sliderFeedbackDamp.setLookAndFeel      (nullptr);
    toggleRecordFreeze.setLookAndFeel      (nullptr);
    sliderMixerDry.setLookAndFeel          (nullptr);
    sliderMixerWet.setLookAndFeel          (nullptr);
    sliderCloudAmpBlur.setLookAndFeel      (nullptr);
    sliderCloudGrainSize1.setLookAndFeel   (nullptr);
    sliderCloudGrainSize2.setLookAndFeel   (nullptr);
    sliderCloudWindowTilt.setLookAndFeel   (nullptr);
    sliderCloudWindowSkirt.setLookAndFeel  (nullptr);
    sliderCloudStereoSpread.setLookAndFeel (nullptr);
    sliderCloudPitchBlur.setLookAndFeel    (nullptr);
    sliderCloudReverseProb.setLookAndFeel  (nullptr);
    sliderEnvelopeAttack.setLookAndFeel    (nullptr);
    sliderEnvelopeRelease.setLookAndFeel   (nullptr);
    rangeSliderCloudPosition.setLookAndFeel(nullptr);
    sliderCloudPosition1.setLookAndFeel    (nullptr);
    sliderCloudPosition2.setLookAndFeel    (nullptr);
    rangeBarCloudGrainSize.setLookAndFeel  (nullptr);
}


void MainComponent::setAudioProcessor(RNBO::JuceAudioProcessor *p)
{
    processor = p;
    RNBO::CoreObject& coreObject = processor->getRnboObject();

    for (unsigned long i = 0; i < coreObject.getNumParameters(); i++) {
        auto parameterName          = coreObject.getParameterId(i);
        RNBO::ParameterValue value  = coreObject.getParameterValue(i);
        juce::Slider *slider        = nullptr;
        
        if      (juce::String(parameterName) == sliderTriggerDensity.getName())     slider = &sliderTriggerDensity;
        else if (juce::String(parameterName) == sliderCloudGrainSize1.getName())    slider = &sliderCloudGrainSize1;
        else if (juce::String(parameterName) == sliderCloudGrainSize2.getName())    slider = &sliderCloudGrainSize2;
        else if (juce::String(parameterName) == sliderMixerDry.getName())           slider = &sliderMixerDry;
        else if (juce::String(parameterName) == sliderMixerWet.getName())           slider = &sliderMixerWet;
        else if (juce::String(parameterName) == sliderTriggerProbability.getName()) slider = &sliderTriggerProbability;
        else if (juce::String(parameterName) == sliderFeedbackAmount.getName())     slider = &sliderFeedbackAmount;
        else if (juce::String(parameterName) == sliderFeedbackDamp.getName())       slider = &sliderFeedbackDamp;
        else if (juce::String(parameterName) == sliderCloudAmpBlur.getName())       slider = &sliderCloudAmpBlur;
        else if (juce::String(parameterName) == sliderCloudWindowTilt.getName())    slider = &sliderCloudWindowTilt;
        else if (juce::String(parameterName) == sliderCloudWindowSkirt.getName())   slider = &sliderCloudWindowSkirt;
        else if (juce::String(parameterName) == sliderCloudStereoSpread.getName())  slider = &sliderCloudStereoSpread;
        else if (juce::String(parameterName) == sliderCloudPitchBlur.getName())     slider = &sliderCloudPitchBlur;
        else if (juce::String(parameterName) == sliderCloudReverseProb.getName())   slider = &sliderCloudReverseProb;
        else if (juce::String(parameterName) == toggleRecordFreeze.getName())       slider = &toggleRecordFreeze;
        else if (juce::String(parameterName) == sliderEnvelopeAttack.getName())     slider = &sliderEnvelopeAttack;
        else if (juce::String(parameterName) == sliderEnvelopeRelease.getName())    slider = &sliderEnvelopeRelease;
        else if (juce::String(parameterName) == sliderCloudPosition1.getName())     slider = &sliderCloudPosition1;
        else if (juce::String(parameterName) == sliderCloudPosition2.getName())     slider = &sliderCloudPosition2;

        if (slider) {
            RNBO::ParameterInfo parameterInfo;

            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            slider->setValue(value);

            if (juce::String(parameterName) == "cloud/position1" || juce::String(parameterName) == "cloud/position2")
            {
                rangeSliderCloudPosition.setRange(parameterInfo.min, parameterInfo.max);
                rangeSliderCloudPosition.setMinAndMaxValues(5000.0 - value, 5000.0 - value);
            }

            
            if (juce::String(parameterName) == "cloud/grain_size1" || juce::String(parameterName) == "cloud/grain_size2")
            {
                rangeBarCloudGrainSize.setRange(parameterInfo.min, parameterInfo.max);
                rangeBarCloudGrainSize.setMinAndMaxValues(5000.0 - value, 5000.0 - value);
            }
            

            if(slider->getName() == juce::String("trigger/density"))                slider->setSkewFactorFromMidPoint(150.0);
            else if(slider->getName() == juce::String("cloud/grain_size"))          slider->setSkewFactorFromMidPoint(200);
            else if(slider->getName() == juce::String("cloud/grain_size_blur"))     slider->setSkewFactorFromMidPoint(0.1);
        }
    }

    // oscilloscope
    scope.setSampleBufferPtr(scopeBuffer);
    scope.setIndexBufferPtr(indexBuffer);
    scope.setScopeLengthInSec(5.0f);
    scope.setAudioProcessor(processor);
}


void MainComponent::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
    if (processor == nullptr) return;
    
    RNBO::CoreObject& coreObject    = processor->getRnboObject();
    auto parameters                 = processor->getParameters();
    RNBO::ParameterIndex index      = coreObject.getParameterIndexForID(sliderThatWasMoved->getName().toRawUTF8());

    if (index != -1)
    {
        const auto param    = processor->getParameters()[index];
        auto newVal         = sliderThatWasMoved->getValue();

        if (param && param->getValue() != newVal) {
            auto normalizedValue = coreObject.convertToNormalizedParameterValue(index, newVal);
            param->beginChangeGesture();
            param->setValueNotifyingHost(normalizedValue);
            param->endChangeGesture();
        }

        if (sliderThatWasMoved->getName() == "cloud/position1" || sliderThatWasMoved->getName() == "cloud/position2") {
            double v1 = 5000.0 - sliderCloudPosition1.getValue();
            double v2 = 5000.0 - sliderCloudPosition2.getValue();

            if (v1 < v2)    rangeSliderCloudPosition.setMinAndMaxValues(v1, v2, juce::NotificationType::dontSendNotification);
            else            rangeSliderCloudPosition.setMinAndMaxValues(v2, v1, juce::NotificationType::dontSendNotification);
        }

        
        if (sliderThatWasMoved->getName() == "cloud/grain_size1" || sliderThatWasMoved->getName() == "cloud/grain_size2") {
            double v1 = 5000.0 - sliderCloudGrainSize1.getValue();
            double v2 = 5000.0 - sliderCloudGrainSize2.getValue();

            if (v1 < v2)    rangeBarCloudGrainSize.setMinAndMaxValues(v1, v2, juce::NotificationType::dontSendNotification);
            else            rangeBarCloudGrainSize.setMinAndMaxValues(v2, v1, juce::NotificationType::dontSendNotification);
        }
    }
    else if (sliderThatWasMoved == &rangeSliderCloudPosition)
    {
        sliderCloudPosition1.setValue(5000.0 - sliderThatWasMoved->getMinValue());
        sliderCloudPosition2.setValue(5000.0 - sliderThatWasMoved->getMaxValue());
    }
    else if (sliderThatWasMoved == &rangeBarCloudGrainSize)
    {
        sliderCloudGrainSize1.setValue(5000.0 - sliderThatWasMoved->getMinValue());
        sliderCloudGrainSize2.setValue(5000.0 - sliderThatWasMoved->getMaxValue());
    }
}


void MainComponent::updateSliderForParam(unsigned long index, double value)
{
    if (processor == nullptr) return;
    
    RNBO::CoreObject& coreObject    = processor->getRnboObject();
    auto slider                     = slidersByParameterIndex.getReference((int) index);
    
    if (slider && (slider->getThumbBeingDragged() == -1))
    {
        auto denormalizedValue = coreObject.convertFromNormalizedParameterValue(index, value);
        slider->setValue(denormalizedValue, NotificationType::dontSendNotification);

        if (slider->getName() == "cloud/position1" || slider->getName() == "cloud/position2")
        {
            double v1 = 5000.0 - sliderCloudPosition1.getValue();
            double v2 = 5000.0 - sliderCloudPosition2.getValue();

            if (v1 < v2)    rangeSliderCloudPosition.setMinAndMaxValues(v1, v2, juce::NotificationType::dontSendNotification);
            else            rangeSliderCloudPosition.setMinAndMaxValues(v2, v1, juce::NotificationType::dontSendNotification);
        }
        else if (slider->getName() == "cloud/grain_size1" || slider->getName() == "cloud/grain_size2")
        {
            double v1 = 5000.0 - sliderCloudGrainSize1.getValue();
            double v2 = 5000.0 - sliderCloudGrainSize2.getValue();

            if (v1 < v2)    rangeBarCloudGrainSize.setMinAndMaxValues(v1, v2, juce::NotificationType::dontSendNotification);
            else            rangeBarCloudGrainSize.setMinAndMaxValues(v2, v1, juce::NotificationType::dontSendNotification);
        }
    }
}

void MainComponent::setScopeBufferPtr(float* ptr)
{
    scopeBuffer = ptr;
}

void MainComponent::setIndexBufferPtr(float* ptr)
{
    indexBuffer = ptr;
}

void MainComponent::paint(juce::Graphics& g) { g.fillAll(juce::Colour (0xff2c3337)); }