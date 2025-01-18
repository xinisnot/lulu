#pragma once

#include <JuceHeader.h>
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"

class LuluOscilloscope  : public juce::Component, public juce::Timer
{
public:
    LuluOscilloscope()
    {
        startTimerHz(30);
    }

    ~LuluOscilloscope() override
    {
        stopTimer();
    }

    void timerCallback() override
    {
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll(juce::Colour (0xff2b3235));
        g.setColour (juce::Colour(0xffd0d0d0));

        float bufferSize = processor->getSampleRate() * scopeLengthInSec;
        float ratio = bufferSize / getWidth();

        juce::Path path1;

        for (int i = 0; i < getWidth(); ++i)
        {
            float sample = *(sampleBufferPtr + static_cast<int>(i * ratio));

            path1.startNewSubPath(i, getHeight() / 2);
            path1.lineTo(i, getHeight() - (sample + 1.f) * (getHeight() / 2));
            path1.closeSubPath();   
        }

        juce::Path path2 = path1;

        float currentPhase = (*(indexBufferPtr) + 1) / bufferSize;
        float path1Trans   = (1.0 - currentPhase) * getWidth() - 1.0f;
        float path2Trans   = path1Trans - getWidth();

        path1.applyTransform(juce::AffineTransform::translation(path1Trans, 0.0f));
        path2.applyTransform(juce::AffineTransform::translation(path2Trans, 0.0f));

        g.strokePath(path1, juce::PathStrokeType(1.0f));
        g.strokePath(path2, juce::PathStrokeType(1.0f));
    }

    void setSampleBufferPtr(float* ptr)
    {
        sampleBufferPtr = ptr;
    }

    void setIndexBufferPtr(float* ptr)
    {
        indexBufferPtr = ptr;
    }

    void setAudioProcessor(RNBO::JuceAudioProcessor* p)
    {
        processor = p;
    }

    void setScopeLengthInSec(float sec)
    {
        scopeLengthInSec = sec;
    }

private:
    RNBO::JuceAudioProcessor *processor = nullptr;
    float* sampleBufferPtr = nullptr;
    float* indexBufferPtr = nullptr;
    float scopeLengthInSec { 0.0f };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LuluOscilloscope)
};
