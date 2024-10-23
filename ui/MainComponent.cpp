#include <JuceHeader.h>
#include "MainComponent.h"


MainComponent::MainComponent()
{
    setSize(320, 340);
    addAndMakeVisible(sliderTriggerDensity);
    addAndMakeVisible(sliderTriggerProbability);
    addAndMakeVisible(sliderFeedbackAmount);
    addAndMakeVisible(sliderFeedbackDamp);
    addAndMakeVisible(toggleRecordFreeze);
    addAndMakeVisible(sliderDrywet);
    addAndMakeVisible(sliderCloudPosition);
    addAndMakeVisible(sliderCloudPositionBlur);
    addAndMakeVisible(sliderCloudAmpBlur);
    addAndMakeVisible(sliderCloudGrainSize);
    addAndMakeVisible(sliderCloudGrainSizeBlur);
    addAndMakeVisible(sliderCloudWindowTilt);
    addAndMakeVisible(sliderCloudWindowSkirt);
    addAndMakeVisible(sliderCloudStereoSpread);
    addAndMakeVisible(sliderCloudPitchBlur);
    addAndMakeVisible(sliderCloudReverseProb);
    addAndMakeVisible(labelTitle);
    
    sliderTriggerDensity.setBounds    (0,   0,   80,  80);
    sliderTriggerProbability.setBounds(80,  0,   80,  80);
    sliderFeedbackAmount.setBounds    (160, 0,   80,  80);
    sliderFeedbackDamp.setBounds      (240, 0,   80,  80);
    sliderCloudPosition.setBounds     (0,   80,  80,  80);
    sliderCloudPositionBlur.setBounds (80,  80,  80,  80);
    sliderCloudGrainSize.setBounds    (160, 80,  80,  80);
    sliderCloudGrainSizeBlur.setBounds(240, 80,  80,  80);
    sliderCloudAmpBlur.setBounds      (0,   160, 80,  80);
    sliderCloudPitchBlur.setBounds    (80,  160, 80,  80);
    sliderCloudStereoSpread.setBounds (160, 160, 80,  80);
    sliderCloudReverseProb.setBounds  (240, 160, 80,  80);
    sliderCloudWindowTilt.setBounds   (0,   240, 80,  80);
    sliderCloudWindowSkirt.setBounds  (80,  240, 80,  80);
    toggleRecordFreeze.setBounds      (160, 240, 80,  80);
    sliderDrywet.setBounds            (240, 240, 80,  80);
    labelTitle.setBounds              (0,   320, 320, 15);

    labelTitle.setFont(juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    labelTitle.setJustificationType (juce::Justification::topRight);
    labelTitle.setEditable(false, false, false);
    labelTitle.setColour(juce::Label::backgroundColourId, juce::Colour (0x00000000));
    labelTitle.setColour(juce::Label::textColourId, juce::Colour(0xff606060));
    
    sliderTriggerDensity.setTitle    ("density");
    sliderTriggerProbability.setTitle("prob");
    sliderFeedbackAmount.setTitle    ("feedback");
    sliderFeedbackDamp.setTitle      ("damp");
    toggleRecordFreeze.setTitle      ("freeze");
    sliderDrywet.setTitle            ("drywet");
    sliderCloudPosition.setTitle     ("pos");
    sliderCloudPositionBlur.setTitle ("posBlur");
    sliderCloudAmpBlur.setTitle      ("ampBlur");
    sliderCloudGrainSize.setTitle    ("size");
    sliderCloudGrainSizeBlur.setTitle("sizeBlur");
    sliderCloudWindowTilt.setTitle   ("tilt");
    sliderCloudWindowSkirt.setTitle  ("skirt");
    sliderCloudStereoSpread.setTitle ("stereo");
    sliderCloudPitchBlur.setTitle    ("pitchBlur");
    sliderCloudReverseProb.setTitle  ("reverse");
    
    sliderTriggerDensity.setName    ("trigger/density");
    sliderTriggerProbability.setName("trigger/probability");
    sliderFeedbackAmount.setName    ("feedback/amount");
    sliderFeedbackDamp.setName      ("feedback/damp");
    toggleRecordFreeze.setName      ("record/freeze");
    sliderDrywet.setName            ("drywet");
    sliderCloudPosition.setName     ("cloud/position");
    sliderCloudPositionBlur.setName ("cloud/position_blur");
    sliderCloudAmpBlur.setName      ("cloud/amp_blur");
    sliderCloudGrainSize.setName    ("cloud/grain_size");
    sliderCloudGrainSizeBlur.setName("cloud/grain_size_blur");
    sliderCloudWindowTilt.setName   ("cloud/window_tilt");
    sliderCloudWindowSkirt.setName  ("cloud/window_skirt");
    sliderCloudStereoSpread.setName ("cloud/stereo_spread");
    sliderCloudPitchBlur.setName    ("cloud/pitch_blur");
    sliderCloudReverseProb.setName  ("cloud/reverse_prob");
    
    sliderTriggerDensity.setTooltip    ("[trigger/denstity] (unit: Hz)");
    sliderTriggerProbability.setTooltip("[trigger/probability]");
    sliderFeedbackAmount.setTooltip    ("[feedback/amount] (unit: dB)");
    sliderFeedbackDamp.setTooltip      ("[feedback/damp].");
    toggleRecordFreeze.setTooltip      ("[record/freeze]");
    sliderDrywet.setTooltip            ("[drywet]");
    sliderCloudPosition.setTooltip     ("[cloud/position]");
    sliderCloudPositionBlur.setTooltip ("[cloud/position_blur]");
    sliderCloudAmpBlur.setTooltip      ("[cloud/amp_blur]");
    sliderCloudGrainSize.setTooltip    ("[cloud/grain_size] (unit: msec)");
    sliderCloudGrainSizeBlur.setTooltip("[cloud/grain_size_blur]");
    sliderCloudWindowTilt.setTooltip   ("[cloud/window_tilt]");
    sliderCloudWindowSkirt.setTooltip  ("[cloud/window_skirt]");
    sliderCloudStereoSpread.setTooltip ("[cloud/stereo_spread]");
    sliderCloudPitchBlur.setTooltip    ("[cloud/pitch_blur] (unit: cent)");
    sliderCloudReverseProb.setTooltip  ("[cloud/reverse_prob]");
    
    sliderTriggerDensity.setLookAndFeel    (&luluDialLaf);
    sliderTriggerProbability.setLookAndFeel(&luluDialLaf);
    sliderFeedbackAmount.setLookAndFeel    (&luluDialLaf);
    sliderFeedbackDamp.setLookAndFeel      (&luluDialLaf);
    toggleRecordFreeze.setLookAndFeel      (&luluToggleLaf);
    sliderDrywet.setLookAndFeel            (&luluDialLaf);
    sliderCloudPosition.setLookAndFeel     (&luluDialLaf);
    sliderCloudPositionBlur.setLookAndFeel (&luluDialLaf);
    sliderCloudAmpBlur.setLookAndFeel      (&luluDialLaf);
    sliderCloudGrainSize.setLookAndFeel    (&luluDialLaf);
    sliderCloudGrainSizeBlur.setLookAndFeel(&luluDialLaf);
    sliderCloudWindowTilt.setLookAndFeel   (&luluDialLaf_fromCenter);
    sliderCloudWindowSkirt.setLookAndFeel  (&luluDialLaf_fromCenter);
    sliderCloudStereoSpread.setLookAndFeel (&luluDialLaf);
    sliderCloudPitchBlur.setLookAndFeel    (&luluDialLaf);
    sliderCloudReverseProb.setLookAndFeel  (&luluDialLaf);

    sliderTriggerDensity.addListener    (this);
    sliderTriggerProbability.addListener(this);
    sliderFeedbackAmount.addListener    (this);
    sliderFeedbackDamp.addListener      (this);
    toggleRecordFreeze.addListener      (this);
    sliderDrywet.addListener            (this);
    sliderCloudPosition.addListener     (this);
    sliderCloudPositionBlur.addListener (this);
    sliderCloudAmpBlur.addListener      (this);
    sliderCloudGrainSize.addListener    (this);
    sliderCloudGrainSizeBlur.addListener(this);
    sliderCloudWindowTilt.addListener   (this);
    sliderCloudWindowSkirt.addListener  (this);
    sliderCloudStereoSpread.addListener (this);
    sliderCloudPitchBlur.addListener    (this);
    sliderCloudReverseProb.addListener  (this);
}

MainComponent::~MainComponent()
{
    sliderTriggerDensity.setLookAndFeel    (nullptr);
    sliderTriggerProbability.setLookAndFeel(nullptr);
    sliderFeedbackAmount.setLookAndFeel    (nullptr);
    sliderFeedbackDamp.setLookAndFeel      (nullptr);
    toggleRecordFreeze.setLookAndFeel      (nullptr);
    sliderDrywet.setLookAndFeel            (nullptr);
    sliderCloudPosition.setLookAndFeel     (nullptr);
    sliderCloudPositionBlur.setLookAndFeel (nullptr);
    sliderCloudAmpBlur.setLookAndFeel      (nullptr);
    sliderCloudGrainSize.setLookAndFeel    (nullptr);
    sliderCloudGrainSizeBlur.setLookAndFeel(nullptr);
    sliderCloudWindowTilt.setLookAndFeel   (nullptr);
    sliderCloudWindowSkirt.setLookAndFeel  (nullptr);
    sliderCloudStereoSpread.setLookAndFeel (nullptr);
    sliderCloudPitchBlur.setLookAndFeel    (nullptr);
    sliderCloudReverseProb.setLookAndFeel  (nullptr);
}


void MainComponent::setAudioProcessor(RNBO::JuceAudioProcessor *p)
{
    processor = p;
    RNBO::CoreObject& coreObject = processor->getRnboObject();

    for (unsigned long i = 0; i < coreObject.getNumParameters(); i++) {
        auto parameterName          = coreObject.getParameterId(i);
        RNBO::ParameterValue value  = coreObject.getParameterValue(i);
        juce::Slider *slider        = nullptr;
        
        if (juce::String(parameterName) == sliderTriggerDensity.getName())          slider = &sliderTriggerDensity;
        else if (juce::String(parameterName) == sliderCloudPositionBlur.getName())  slider = &sliderCloudPositionBlur;
        else if (juce::String(parameterName) == sliderCloudPosition.getName())      slider = &sliderCloudPosition;
        else if (juce::String(parameterName) == sliderCloudGrainSize.getName())     slider = &sliderCloudGrainSize;
        else if (juce::String(parameterName) == sliderCloudGrainSizeBlur.getName()) slider = &sliderCloudGrainSizeBlur;
        else if (juce::String(parameterName) == sliderDrywet.getName())             slider = &sliderDrywet;
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

        if (slider) {
            RNBO::ParameterInfo parameterInfo;

            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            slider->setValue(value);

            if(slider->getName() == juce::String("trigger/density"))                slider->setSkewFactorFromMidPoint(100.0);
            else if(slider->getName() == juce::String("cloud/position"))            slider->setSkewFactorFromMidPoint(200);
            else if(slider->getName() == juce::String("cloud/position_blur"))       slider->setSkewFactorFromMidPoint(0.1);
            else if(slider->getName() == juce::String("cloud/grain_size"))          slider->setSkewFactorFromMidPoint(200);
            else if(slider->getName() == juce::String("cloud/grain_size_blur"))     slider->setSkewFactorFromMidPoint(0.1);
        }
    }
}


void MainComponent::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
    if (processor == nullptr) return;
    
    RNBO::CoreObject& coreObject    = processor->getRnboObject();
    auto parameters                 = processor->getParameters();
    RNBO::ParameterIndex index      = coreObject.getParameterIndexForID(sliderThatWasMoved->getName().toRawUTF8());
    
    if (index != -1) {
        const auto param    = processor->getParameters()[index];
        auto newVal         = sliderThatWasMoved->getValue();

        if (param && param->getValue() != newVal) {
            auto normalizedValue = coreObject.convertToNormalizedParameterValue(index, newVal);
            param->beginChangeGesture();
            param->setValueNotifyingHost(normalizedValue);
            param->endChangeGesture();
        }
    }
}


void MainComponent::updateSliderForParam(unsigned long index, double value)
{
    if (processor == nullptr) return;
    
    RNBO::CoreObject& coreObject    = processor->getRnboObject();
    auto denormalizedValue          = coreObject.convertFromNormalizedParameterValue(index, value);
    auto slider                     = slidersByParameterIndex.getReference((int) index);
    
    if (slider && (slider->getThumbBeingDragged() == -1))
        slider->setValue(denormalizedValue, NotificationType::dontSendNotification);
}


void MainComponent::paint(juce::Graphics& g) { g.fillAll(juce::Colour (0xff2c3337)); }
void MainComponent::resized() {}
