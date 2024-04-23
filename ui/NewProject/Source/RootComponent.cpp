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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "RootComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RootComponent::RootComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__component.reset (new LuluDial ("dens", "Corresponds to [trigger/denstity]. The frequency of the trigger that generates grains (unit: Hz)."));
    addAndMakeVisible (juce__component.get());
    juce__component->setName ("trigger/density");

    juce__component->setBounds (0, 0, 94, 96);

    juce__component2.reset (new LuluDial ("prob", "Corresponds to [trigger/probability]. The probability that triggers is generated for each cycle."));
    addAndMakeVisible (juce__component2.get());
    juce__component2->setName ("trigger/probability");

    juce__component2->setBounds (96, 0, 94, 96);

    juce__component3.reset (new LuluDial ("amp", "Corresponds to [cloud/amp_spread]. The amount of amplitude blur for each grain."));
    addAndMakeVisible (juce__component3.get());
    juce__component3->setName ("cloud/amp_spread");

    juce__component3->setBounds (192, 0, 94, 96);

    juce__component4.reset (new LuluDial ("stereo", "Corresponds to [cloud/stereo_spread]. The amount of stereo-spread for each grain."));
    addAndMakeVisible (juce__component4.get());
    juce__component4->setName ("cloud/stereo_spread");

    juce__component4->setBounds (288, 0, 94, 96);

    juce__component5.reset (new LuluDial ("pitch", "Corresponds to [cloud/pitch_spread]. The amount of pitch blur for each grain."));
    addAndMakeVisible (juce__component5.get());
    juce__component5->setName ("cloud/pitch_spread");

    juce__component5->setBounds (0, 96, 94, 96);

    juce__component6.reset (new LuluDial ("reverse", "Corresponds to [cloud/reverse_prob]. The probability that each grains is played backwards."));
    addAndMakeVisible (juce__component6.get());
    juce__component6->setName ("cloud/reverse_prob");

    juce__component6->setBounds (96, 96, 94, 96);

    juce__component7.reset (new LuluDial ("fb", "Corresponds to [feedback/amount]. Feedback gain (unit: dB)."));
    addAndMakeVisible (juce__component7.get());
    juce__component7->setName ("feedback/amount");

    juce__component7->setBounds (384, 0, 94, 96);

    juce__component8.reset (new LuluDial ("filter", "Corresponds to [feedback/type]. Filter characteristics in the feedback loop."));
    addAndMakeVisible (juce__component8.get());
    juce__component8->setName ("feedback/type");

    juce__component8->setBounds (480, 0, 94, 96);

    juce__component9.reset (new LuluDial ("cutoff", "Corresponds to [feedback/frequency]. Cutoff frequency of the filter in the feedback loop (unit: Hz)."));
    addAndMakeVisible (juce__component9.get());
    juce__component9->setName ("feedback/frequency");

    juce__component9->setBounds (576, 0, 94, 96);

    juce__component10.reset (new LuluDial ("res", "Corresponds to [feedback/resonance.] Resonance of the filter in the feedback loop."));
    addAndMakeVisible (juce__component10.get());
    juce__component10->setName ("feedback/resonance");

    juce__component10->setBounds (672, 0, 94, 96);

    juce__component11.reset (new LuluDial ("dw", "Corresponds to [drywet]. The amount of wet signal."));
    addAndMakeVisible (juce__component11.get());
    juce__component11->setName ("drywet");

    juce__component11->setBounds (672, 96, 94, 96);

    juce__component12.reset (new LuluToggle ("freeze", "Corresponds to [record/freeze]. When enabled, recording is stopped and texture is freezed."));
    addAndMakeVisible (juce__component12.get());
    juce__component12->setName ("record/freeze");

    juce__component12->setBounds (384, 96, 94, 96);

    juce__component13.reset (new LuluToggle ("arp", "Corresponds to [cloud/arp]. When enabled, pitches are selected in the order in which note-ons are received."));
    addAndMakeVisible (juce__component13.get());
    juce__component13->setName ("cloud/arp");

    juce__component13->setBounds (480, 96, 94, 96);

    juce__component14.reset (new LuluRangeDial ("saw", 0.5, "Corresponds to [cloud/window_saw_min] and [cloud/window_saw_max]. The peak of the window function varies within a specified range. The further away from 0.5, the more like a sawtooth wave it becomes."));
    addAndMakeVisible (juce__component14.get());
    juce__component14->setName ("cloud/window_saw");

    juce__component14->setBounds (192, 96, 94, 96);

    juce__component15.reset (new LuluRangeDial ("square", 0.0, "Corresponds to [cloud/window_square_min] and [cloud/window_square_max]. The peak of the window function varies within a specified range. The larger the value, the more like a square wave it becomes."));
    addAndMakeVisible (juce__component15.get());
    juce__component15->setName ("cloud/window_square");

    juce__component15->setBounds (288, 96, 94, 96);

    juce__component17.reset (new LuluRangeSlider ("size", 100.0, "Corresponds to [cloud/size_min] and [cloud/size_max]. The size range of each grain (unit: ms)."));
    addAndMakeVisible (juce__component17.get());
    juce__component17->setName ("cloud/size");

    juce__component17->setBounds (8, 192, 750, 24);

    juce__component16.reset (new LuluRangeSlider ("pos", 100.0, "Corresponds to [cloud/position_spread_min] and [cloud/position_spread_max]. Delay time of each grains varies within a specified range (unit: ms)."));
    addAndMakeVisible (juce__component16.get());
    juce__component16->setName ("cloud/position_spread");

    juce__component16->setBounds (8, 216, 750, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS ("lulu by @xinisnot")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centred);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (576, 132, 94, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (766, 240);


    //[Constructor] You can add your own custom stuff here..
    juce__component  ->addListener(this);   // trigger/density
    juce__component2 ->addListener(this);   // trigger/probability
    juce__component3 ->addListener(this);   // cloud/amp_spread
    juce__component4 ->addListener(this);   // cloud/stereo_spread
    juce__component5 ->addListener(this);   // cloud/pitch_spread
    juce__component6 ->addListener(this);   // cloud/reverse_prob
    juce__component7 ->addListener(this);   // feedback/amount
    juce__component8 ->addListener(this);   // feedback/type
    juce__component9 ->addListener(this);   // feedback/frequency
    juce__component10->addListener(this);   // feedback/resonance
    juce__component11->addListener(this);   // drywet
    juce__component12->addListener(this);   // record/freeze
    juce__component13->addListener(this);   // cloud/arp
    juce__component14->addListener(this);   // cloud/window_saw
    juce__component15->addListener(this);   // cloud/window_square
    juce__component16->addListener(this);   // cloud/position_spread
    juce__component17->addListener(this);   // cloud/size

    juce__component  ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component2 ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component3 ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component4 ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component5 ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component6 ->setLookAndFeel(&luluDialLaf_drawValue);
    juce__component7 ->setLookAndFeel(&luluDialLaf_drawValue_feedback);
    juce__component8 ->setLookAndFeel(&luluDialLaf_filterType);
    juce__component9 ->setLookAndFeel(&luluDialLaf_feedback);
    juce__component10->setLookAndFeel(&luluDialLaf_drawValue_feedback);
    juce__component11->setLookAndFeel(&luluDialLaf);
    juce__component12->setLookAndFeel(&luluToggleLaf);
    juce__component13->setLookAndFeel(&luluToggleLaf);
    juce__component14->setLookAndFeel(&luluRangeDialLaf);
    juce__component15->setLookAndFeel(&luluRangeDialLaf);
    juce__component16->setLookAndFeel(&luluRangeSliderLaf);
    juce__component17->setLookAndFeel(&luluRangeSliderLaf);
    //[/Constructor]
}

RootComponent::~RootComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__component = nullptr;
    juce__component2 = nullptr;
    juce__component3 = nullptr;
    juce__component4 = nullptr;
    juce__component5 = nullptr;
    juce__component6 = nullptr;
    juce__component7 = nullptr;
    juce__component8 = nullptr;
    juce__component9 = nullptr;
    juce__component10 = nullptr;
    juce__component11 = nullptr;
    juce__component12 = nullptr;
    juce__component13 = nullptr;
    juce__component14 = nullptr;
    juce__component15 = nullptr;
    juce__component17 = nullptr;
    juce__component16 = nullptr;
    juce__label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RootComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff2c3337));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RootComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void RootComponent::luluDialValueChanged(RNBO::CoreObject& coreObject, juce::Slider* sliderThatWasMoved, RNBO::ParameterIndex index)
{
    const auto param = processor->getParameters()[index];
    auto newVal = sliderThatWasMoved->getValue();

    if (param && param->getValue() != newVal)
    {
        auto normalizedValue = coreObject.convertToNormalizedParameterValue(index, newVal);
        param->beginChangeGesture();
        param->setValueNotifyingHost(normalizedValue);
        param->endChangeGesture();
    }
}

void RootComponent::luluRangeUiValueChanged(RNBO::CoreObject& coreObject, juce::Slider* sliderThatWasMoved, RNBO::ParameterIndex index_min, RNBO::ParameterIndex index_max)
{
    const auto param_min = processor->getParameters()[index_min];
    const auto param_max = processor->getParameters()[index_max];
    auto paramName = processor->getName();
    auto newVal_min = sliderThatWasMoved->getMinValue();
    auto newVal_max = sliderThatWasMoved->getMaxValue();

    if (param_min && param_min->getValue() != newVal_min)
    {
        auto normalizedValue = coreObject.convertToNormalizedParameterValue(index_min, newVal_min);
        param_min->beginChangeGesture();
        param_min->setValueNotifyingHost(normalizedValue);
        param_min->endChangeGesture();
    }

    if (param_max && param_max->getValue() != newVal_max)
    {
        auto normalizedValue = coreObject.convertToNormalizedParameterValue(index_max, newVal_max);
        param_max->beginChangeGesture();
        param_max->setValueNotifyingHost(normalizedValue);
        param_max->endChangeGesture();
    }
}


void RootComponent::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (processor == nullptr) return;
    RNBO::CoreObject& coreObject = processor->getRnboObject();
    auto parameters = processor->getParameters();
    RNBO::ParameterIndex index = coreObject.getParameterIndexForID(sliderThatWasMoved->getName().toRawUTF8());

    if (index != -1) {
        if (sliderThatWasMoved == juce__component.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component2.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component3.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component4.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component5.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component6.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component7.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component8.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component9.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component10.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component11.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component12.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        } else if (sliderThatWasMoved == juce__component13.get()) {
            luluDialValueChanged(coreObject, sliderThatWasMoved, index);
        }
    } else {
        if (sliderThatWasMoved == juce__component14.get()) {
            RNBO::ParameterIndex index_min = coreObject.getParameterIndexForID(juce::String("cloud/window_saw_min").toRawUTF8());
            RNBO::ParameterIndex index_max = coreObject.getParameterIndexForID(juce::String("cloud/window_saw_max").toRawUTF8());
            luluRangeUiValueChanged(coreObject, sliderThatWasMoved, index_min, index_max);
        } else if (sliderThatWasMoved == juce__component15.get()) {
            RNBO::ParameterIndex index_min = coreObject.getParameterIndexForID(juce::String("cloud/window_square_min").toRawUTF8());
            RNBO::ParameterIndex index_max = coreObject.getParameterIndexForID(juce::String("cloud/window_square_max").toRawUTF8());
            luluRangeUiValueChanged(coreObject, sliderThatWasMoved, index_min, index_max);
        } else if (sliderThatWasMoved == juce__component16.get()) {
            RNBO::ParameterIndex index_min = coreObject.getParameterIndexForID(juce::String("cloud/position_spread_min").toRawUTF8());
            RNBO::ParameterIndex index_max = coreObject.getParameterIndexForID(juce::String("cloud/position_spread_max").toRawUTF8());
            luluRangeUiValueChanged(coreObject, sliderThatWasMoved, index_min, index_max);
        } else if (sliderThatWasMoved == juce__component17.get()) {
            RNBO::ParameterIndex index_min = coreObject.getParameterIndexForID(juce::String("cloud/size_min").toRawUTF8());
            RNBO::ParameterIndex index_max = coreObject.getParameterIndexForID(juce::String("cloud/size_max").toRawUTF8());
            luluRangeUiValueChanged(coreObject, sliderThatWasMoved, index_min, index_max);
        }
    }
}


void RootComponent::setLuluDialValue(RNBO::CoreObject& coreObject, juce::Slider* slider, unsigned long index, double interval)
{
    RNBO::ParameterInfo parameterInfo;
    RNBO::ParameterValue value = coreObject.getParameterValue(index);

    slidersByParameterIndex.set(index, slider);
    coreObject.getParameterInfo(index, &parameterInfo);
    slider->setRange(parameterInfo.min, parameterInfo.max, interval);
    slider->setValue(value);
}


void RootComponent::setAudioProcessor(RNBO::JuceAudioProcessor *p)
{
    processor = p;

    // RNBO::ParameterInfo parameterInfo;
    RNBO::CoreObject& coreObject = processor->getRnboObject();

    RNBO::ParameterValue tmp_window_saw_min;
    RNBO::ParameterValue tmp_window_saw_max;
    RNBO::ParameterValue tmp_window_square_min;
    RNBO::ParameterValue tmp_window_square_max;
    RNBO::ParameterValue tmp_position_spread_min;
    RNBO::ParameterValue tmp_position_spread_max;
    RNBO::ParameterValue tmp_size_min;
    RNBO::ParameterValue tmp_size_max;

    for (unsigned long i = 0; i < coreObject.getNumParameters(); i++) {
        auto parameterName = coreObject.getParameterId(i);
        Slider *slider = nullptr;

        // LuluDial or LuluToggle
        if (juce::String(parameterName) == juce__component.get()->getName()) {
            // trigger/density
            slider = juce__component.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
            slider->setSkewFactorFromMidPoint(80.0);
        } else if (juce::String(parameterName) == juce__component2.get()->getName()) {
            // trigger/probability
            slider = juce__component2.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component3.get()->getName()) {
            // cloud/amp_spread
            slider = juce__component3.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component4.get()->getName()) {
            // cloud/stereo_spread
            slider = juce__component4.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component5.get()->getName()) {
            // cloud/pitch_spread
            slider = juce__component5.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component6.get()->getName()) {
            // cloud/reverse_prob
            slider = juce__component6.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component7.get()->getName()) {
            // feedback/amount
            slider = juce__component7.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component8.get()->getName()) {
            // feedback/type
            slider = juce__component8.get();
            setLuluDialValue(coreObject, slider, i, 1.0);
        } else if (juce::String(parameterName) == juce__component9.get()->getName()) {
            // feedback/frequency
            slider = juce__component9.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
            slider->setSkewFactorFromMidPoint(800.0);
        } else if (juce::String(parameterName) == juce__component10.get()->getName()) {
            // feedback/resonance
            slider = juce__component10.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component11.get()->getName()) {
            // drywet
            slider = juce__component11.get();
            setLuluDialValue(coreObject, slider, i, 0.0);
        } else if (juce::String(parameterName) == juce__component12.get()->getName()) {
            // record/freeze
            slider = juce__component12.get();
            setLuluDialValue(coreObject, slider, i, 1.0);
        } else if (juce::String(parameterName) == juce__component13.get()->getName()) {
            // cloud/arp
            slider = juce__component13.get();
            setLuluDialValue(coreObject, slider, i, 1.0);
        } else if (juce::String(parameterName) == juce::String("cloud/window_saw_min")) {
            // cloud/window_saw
            slider = juce__component14.get();
            RNBO::ParameterInfo parameterInfo;
            auto parameterName = coreObject.getParameterId(i);
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_window_saw_min = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/window_saw_max")) {
            // cloud/window_saw
            slider = juce__component14.get();
            RNBO::ParameterInfo parameterInfo;
            auto parameterName = coreObject.getParameterId(i);
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_window_saw_max = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/window_square_min")) {
            // cloud/window_square
            slider = juce__component15.get();
            RNBO::ParameterInfo parameterInfo;
            auto parameterName = coreObject.getParameterId(i);
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_window_square_min = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/window_square_max")) {
            // cloud/window_square
            slider = juce__component15.get();
            RNBO::ParameterInfo parameterInfo;
            auto parameterName = coreObject.getParameterId(i);
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_window_square_max = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/position_spread_min")) {
            // cloud/position_spread
            slider = juce__component16.get();
            RNBO::ParameterInfo parameterInfo;
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_position_spread_min = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/position_spread_max")) {
            // cloud/position_spread
            slider = juce__component16.get();
            RNBO::ParameterInfo parameterInfo;
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_position_spread_max = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/size_min")) {
            // cloud/size
            slider = juce__component17.get();
            RNBO::ParameterInfo parameterInfo;
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_size_min = coreObject.getParameterValue(i);
        } else if (juce::String(parameterName) == juce::String("cloud/size_max")) {
            // cloud/size
            slider = juce__component17.get();
            RNBO::ParameterInfo parameterInfo;
            slidersByParameterIndex.set(i, slider);
            coreObject.getParameterInfo(i, &parameterInfo);
            slider->setRange(parameterInfo.min, parameterInfo.max);
            tmp_size_max = coreObject.getParameterValue(i);
        }
    }

    juce__component14->setMaxValue(tmp_window_saw_max);
    juce__component14->setMinValue(tmp_window_saw_min);
    juce__component15->setMaxValue(tmp_window_square_max);
    juce__component15->setMinValue(tmp_window_square_min);
    juce__component16->setMaxValue(tmp_position_spread_max);
    juce__component16->setMinValue(tmp_position_spread_min);
    juce__component17->setMaxValue(tmp_size_max);
    juce__component17->setMinValue(tmp_size_min);
}


void RootComponent::updateSliderForParam(unsigned long index, double value)
{
    if (processor == nullptr) return;
    RNBO::CoreObject& coreObject = processor->getRnboObject();
    auto denormalizedValue = coreObject.convertFromNormalizedParameterValue(index, value);
    auto slider = slidersByParameterIndex.getReference((int) index);
    if (slider && (slider->getThumbBeingDragged() == -1)) {
        slider->setValue(denormalizedValue, NotificationType::dontSendNotification);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RootComponent" componentName=""
                 parentClasses="public juce::Component, public juce::Slider::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="766"
                 initialHeight="240">
  <BACKGROUND backgroundColour="ff2c3337"/>
  <GENERICCOMPONENT name="trigger/density" id="a88a56cbaafa361c" memberName="juce__component"
                    virtualName="" explicitFocusOrder="0" pos="0 0 94 96" class="LuluDial"
                    params="&quot;dens&quot;, &quot;Corresponds to [trigger/denstity]. The frequency of the trigger that generates grains (unit: Hz).&quot;"/>
  <GENERICCOMPONENT name="trigger/probability" id="d93a829d71a35dd7" memberName="juce__component2"
                    virtualName="" explicitFocusOrder="0" pos="96 0 94 96" class="LuluDial"
                    params="&quot;prob&quot;, &quot;Corresponds to [trigger/probability]. The probability that triggers is generated for each cycle.&quot;"/>
  <GENERICCOMPONENT name="cloud/amp_spread" id="553b244a5844e8a4" memberName="juce__component3"
                    virtualName="" explicitFocusOrder="0" pos="192 0 94 96" class="LuluDial"
                    params="&quot;amp&quot;, &quot;Corresponds to [cloud/amp_spread]. The amount of amplitude blur for each grain.&quot;"/>
  <GENERICCOMPONENT name="cloud/stereo_spread" id="3a132989744af231" memberName="juce__component4"
                    virtualName="" explicitFocusOrder="0" pos="288 0 94 96" class="LuluDial"
                    params="&quot;stereo&quot;, &quot;Corresponds to [cloud/stereo_spread]. The amount of stereo-spread for each grain.&quot;"/>
  <GENERICCOMPONENT name="cloud/pitch_spread" id="69e38761c82b373" memberName="juce__component5"
                    virtualName="" explicitFocusOrder="0" pos="0 96 94 96" class="LuluDial"
                    params="&quot;pitch&quot;, &quot;Corresponds to [cloud/pitch_spread]. The amount of pitch blur for each grain.&quot;"/>
  <GENERICCOMPONENT name="cloud/reverse_prob" id="a7966469528a5614" memberName="juce__component6"
                    virtualName="" explicitFocusOrder="0" pos="96 96 94 96" class="LuluDial"
                    params="&quot;reverse&quot;, &quot;Corresponds to [cloud/reverse_prob]. The probability that each grains is played backwards.&quot;"/>
  <GENERICCOMPONENT name="feedback/amount" id="b506f0eb0009a4d4" memberName="juce__component7"
                    virtualName="" explicitFocusOrder="0" pos="384 0 94 96" class="LuluDial"
                    params="&quot;fb&quot;, &quot;Corresponds to [feedback/amount]. Feedback gain (unit: dB).&quot;"/>
  <GENERICCOMPONENT name="feedback/type" id="575ffde6533637ff" memberName="juce__component8"
                    virtualName="" explicitFocusOrder="0" pos="480 0 94 96" class="LuluDial"
                    params="&quot;filter&quot;, &quot;Corresponds to [feedback/type]. Filter characteristics in the feedback loop.&quot;"/>
  <GENERICCOMPONENT name="feedback/frequency" id="4487c21a6436cc49" memberName="juce__component9"
                    virtualName="" explicitFocusOrder="0" pos="576 0 94 96" class="LuluDial"
                    params="&quot;cutoff&quot;, &quot;Corresponds to [feedback/frequency]. Cutoff frequency of the filter in the feedback loop (unit: Hz).&quot;"/>
  <GENERICCOMPONENT name="feedback/resonance" id="374fa9821f93d455" memberName="juce__component10"
                    virtualName="" explicitFocusOrder="0" pos="672 0 94 96" class="LuluDial"
                    params="&quot;res&quot;, &quot;Corresponds to [feedback/resonance.] Resonance of the filter in the feedback loop.&quot;"/>
  <GENERICCOMPONENT name="drywet" id="74d5b38edd6fc99f" memberName="juce__component11"
                    virtualName="" explicitFocusOrder="0" pos="672 96 94 96" class="LuluDial"
                    params="&quot;dw&quot;, &quot;Corresponds to [drywet]. The amount of wet signal.&quot;"/>
  <GENERICCOMPONENT name="record/freeze" id="fddf570a78af6785" memberName="juce__component12"
                    virtualName="" explicitFocusOrder="0" pos="384 96 94 96" class="LuluToggle"
                    params="&quot;freeze&quot;, &quot;Corresponds to [record/freeze]. When enabled, recording is stopped and texture is freezed.&quot;"/>
  <GENERICCOMPONENT name="cloud/arp" id="3298acec569d528c" memberName="juce__component13"
                    virtualName="" explicitFocusOrder="0" pos="480 96 94 96" class="LuluToggle"
                    params="&quot;arp&quot;, &quot;Corresponds to [cloud/arp]. When enabled, pitches are selected in the order in which note-ons are received.&quot;"/>
  <GENERICCOMPONENT name="cloud/window_saw" id="328ba8c80d3af421" memberName="juce__component14"
                    virtualName="" explicitFocusOrder="0" pos="192 96 94 96" class="LuluRangeDial"
                    params="&quot;saw&quot;, 0.5, &quot;Corresponds to [cloud/window_saw_min] and [cloud/window_saw_max]. The peak of the window function varies within a specified range. The further away from 0.5, the more like a sawtooth wave it becomes.&quot;"/>
  <GENERICCOMPONENT name="cloud/window_square" id="2b4ac4b9e6276bbc" memberName="juce__component15"
                    virtualName="" explicitFocusOrder="0" pos="288 96 94 96" class="LuluRangeDial"
                    params="&quot;square&quot;, 0.0, &quot;Corresponds to [cloud/window_square_min] and [cloud/window_square_max]. The peak of the window function varies within a specified range. The larger the value, the more like a square wave it becomes.&quot;"/>
  <GENERICCOMPONENT name="cloud/size" id="6a8ebac4af393906" memberName="juce__component17"
                    virtualName="" explicitFocusOrder="0" pos="8 192 750 24" class="LuluRangeSlider"
                    params="&quot;size&quot;, 100.0, &quot;Corresponds to [cloud/size_min] and [cloud/size_max]. The size range of each grain (unit: ms).&quot;"/>
  <GENERICCOMPONENT name="cloud/position_spread" id="90965c074bde1229" memberName="juce__component16"
                    virtualName="" explicitFocusOrder="0" pos="8 216 750 24" class="LuluRangeSlider"
                    params="&quot;pos&quot;, 100.0, &quot;Corresponds to [cloud/position_spread_min] and [cloud/position_spread_max]. Delay time of each grains varies within a specified range (unit: ms).&quot;"/>
  <LABEL name="new label" id="a1146fdc32b96514" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="576 132 94 24" edTextCol="ff000000"
         edBkgCol="0" labelText="lulu by @xinisnot" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

