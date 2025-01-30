#include "CustomAudioProcessor.h"
#include "CustomAudioEditor.h"
#include <json/json.hpp>

#ifdef RNBO_INCLUDE_DESCRIPTION_FILE
#include <rnbo_description.h>
#endif


CustomAudioProcessor::CustomAudioProcessor(const nlohmann::json& patcher_desc, const nlohmann::json& presets, const RNBO::BinaryData& data) 
    : RNBO::JuceAudioProcessor(patcher_desc, presets, data) 
{
	// oscilloscope buffer
    RNBO::CoreObject& coreObject = getRnboObject();

    scopeBuffer = std::make_unique<float[]>(static_cast<int>(coreObject.getSampleRate() * 5.0));
    indexBuffer = std::make_unique<float[]>(1);

    RNBO::Float32AudioBuffer scopeBufferType(1, coreObject.getSampleRate());
    RNBO::Float32AudioBuffer indexBufferType(1, coreObject.getSampleRate());

    coreObject.setExternalData(
        "scope",
        reinterpret_cast<char*>(scopeBuffer.get()),
        static_cast<int>(coreObject.getSampleRate() * 5.0) * sizeof(float),
        scopeBufferType
    );

    coreObject.setExternalData(
        "scope_index",
        reinterpret_cast<char*>(indexBuffer.get()),
        1 * sizeof(float),
        indexBufferType
    );
}

CustomAudioProcessor::~CustomAudioProcessor()
{
  scopeBuffer.release();
  indexBuffer.release();
}

//create an instance of our custom plugin, optionally set description, presets and binary data (datarefs)
CustomAudioProcessor* CustomAudioProcessor::CreateDefault() {
	nlohmann::json patcher_desc, presets;

#ifdef RNBO_BINARY_DATA_STORAGE_NAME
	extern RNBO::BinaryDataImpl::Storage RNBO_BINARY_DATA_STORAGE_NAME;
	RNBO::BinaryDataImpl::Storage dataStorage = RNBO_BINARY_DATA_STORAGE_NAME;
#else
	RNBO::BinaryDataImpl::Storage dataStorage;
#endif
	RNBO::BinaryDataImpl data(dataStorage);

#ifdef RNBO_INCLUDE_DESCRIPTION_FILE
	patcher_desc = RNBO::patcher_description;
	presets = RNBO::patcher_presets;
#endif
  return new CustomAudioProcessor(patcher_desc, presets, data);
}


AudioProcessorEditor* CustomAudioProcessor::createEditor()
{
    return new CustomAudioEditor (this, this->_rnboObject, scopeBuffer.get(), indexBuffer.get());
}