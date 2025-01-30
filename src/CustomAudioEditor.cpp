#include "CustomAudioEditor.h"

CustomAudioEditor::CustomAudioEditor (RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject, float* scopeBufferPtr, float* indexBufferPtr)
    : AudioProcessorEditor (p)
    , _rnboObject(rnboObject)
    , _audioProcessor(p)
{
    _audioProcessor->AudioProcessor::addListener(this);
    _mainComponent.setScopeBufferPtr(scopeBufferPtr);
    _mainComponent.setIndexBufferPtr(indexBufferPtr);
    _mainComponent.setAudioProcessor(p);
    
    addAndMakeVisible(_mainComponent);
    setSize(_mainComponent.getWidth(), _mainComponent.getHeight());
}

CustomAudioEditor::~CustomAudioEditor()
{
    _audioProcessor->AudioProcessor::removeListener(this);
}

void CustomAudioEditor::paint (Graphics& g)
{
    g.fillAll(Colours::white);
}

void CustomAudioEditor::audioProcessorParameterChanged (AudioProcessor*, int parameterIndex, float value)
{
    _mainComponent.updateSliderForParam(parameterIndex, value);
}
