#include "JuceHeader.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include "MainComponent.h"

class CustomAudioEditor : public AudioProcessorEditor, private AudioProcessorListener
{
public:
    CustomAudioEditor(RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject, float* indexBufferPtr, float* scopeBufferPtr);
    ~CustomAudioEditor() override;
    void paint (Graphics& g) override;

private:
    void audioProcessorChanged (AudioProcessor*, const ChangeDetails&) override { }
    void audioProcessorParameterChanged(AudioProcessor*, int parameterIndex, float) override;

protected:
    AudioProcessor      *_audioProcessor;
    RNBO::CoreObject&   _rnboObject;
    MainComponent       _mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
