#include "RNBO.h"
#include "RNBO_Utils.h"
#include "RNBO_JuceAudioProcessor.h"
#include "RNBO_BinaryData.h"
#include <json/json.hpp>

class CustomAudioProcessor : public RNBO::JuceAudioProcessor {
public:
    CustomAudioProcessor(const nlohmann::json& patcher_desc, const nlohmann::json& presets, const RNBO::BinaryData& data);
    ~CustomAudioProcessor() override;
    static CustomAudioProcessor* CreateDefault();
    juce::AudioProcessorEditor* createEditor() override;
    void setScopeBufferAndIndexBuffer();

private:
    double samplerate { 0.0 };
    std::unique_ptr<float[]> scopeBuffer;
    std::unique_ptr<float[]> indexBuffer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioProcessor)
};

