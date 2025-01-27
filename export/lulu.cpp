/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_24 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_24()
    {
    }
    
    ~RNBOSubpatcher_24()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1841075377, false);
        getEngine()->flushClockEvents(this, -281953904, false);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        this->linetilde_01_perform(this->signals[0], n);
        this->dspexpr_02_perform(in2, this->signals[0], this->signals[1], n);
        this->dspexpr_01_perform(in1, this->signals[0], this->signals[2], n);
        this->linetilde_02_perform(this->signals[0], n);
        this->dspexpr_03_perform(in3, this->signals[0], this->signals[3], n);
        this->signaladder_01_perform(this->signals[3], this->signals[2], out1, n);
        this->dspexpr_04_perform(in4, this->signals[0], this->signals[2], n);
        this->signaladder_02_perform(this->signals[2], this->signals[1], out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_01_getPresetValue(getSubState(preset, "dry"));
        this->param_02_getPresetValue(getSubState(preset, "wet"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
            break;
            }
        case 1:
            {
            this->param_02_value_set(v);
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_01_value;
            }
        case 1:
            {
            return this->param_02_value;
            }
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 2;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "dry";
            }
        case 1:
            {
            return "wet";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "mixer/dry";
            }
        case 1:
            {
            return "mixer/wet";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = -70;
                info->max = 0;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "dB";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = -70;
                info->min = -70;
                info->max = 0;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "dB";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
        case 1:
            {
            {
                value = (value < -70 ? -70 : (value > 0 ? 0 : value));
                ParameterValue normalizedValue = (value - -70) / (0 - -70);
                return normalizedValue;
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
        case 1:
            {
            {
                {
                    return -70 + value * (0 - -70);
                }
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_01_value_constrain(value);
            }
        case 1:
            {
            return this->param_02_value_constrain(value);
            }
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1841075377:
            {
            this->linetilde_01_target_bang();
            break;
            }
        case -281953904:
            {
            this->linetilde_02_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void param_01_value_set(number v) {
        v = this->param_01_value_constrain(v);
        this->param_01_value = v;
        this->sendParameter(0, false);
    
        if (this->param_01_value != this->param_01_lastValue) {
            this->getEngine()->presetTouched();
            this->param_01_lastValue = this->param_01_value;
        }
    
        this->expr_01_in1_set(v);
    }
    
    void param_02_value_set(number v) {
        v = this->param_02_value_constrain(v);
        this->param_02_value = v;
        this->sendParameter(1, false);
    
        if (this->param_02_value != this->param_02_lastValue) {
            this->getEngine()->presetTouched();
            this->param_02_lastValue = this->param_02_value;
        }
    
        this->expr_02_in1_set(v);
    }
    
    void linetilde_01_target_bang() {}
    
    void linetilde_02_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 4;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    }
    
    void allocateDataRefs() {}
    
    number param_01_value_constrain(number v) const {
        v = (v > 0 ? 0 : (v < -70 ? -70 : v));
        return v;
    }
    
    void linetilde_01_time_set(number v) {
        this->linetilde_01_time = v;
    }
    
    void linetilde_01_segments_set(const list& v) {
        this->linetilde_01_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_01_time == 0) {
                this->linetilde_01_activeRamps->length = 0;
                this->linetilde_01_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_01_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_01_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_01_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_01_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_01_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_01_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_01_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_01_activeRamps->push(lastRampValue);
                    this->linetilde_01_activeRamps->push(0);
                    this->linetilde_01_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_01_keepramp)) {
                            this->linetilde_01_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_01_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_01_activeRamps->push(destinationValue);
                    this->linetilde_01_activeRamps->push(inc);
                    this->linetilde_01_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
    
        {
            list converted = {this->expr_01_out1};
            this->linetilde_01_segments_set(converted);
        }
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(rnbo_pow(10, this->expr_01_in1 * 0.05));//#map:mixer/dbtoa_obj-11:1
    }
    
    number param_02_value_constrain(number v) const {
        v = (v > 0 ? 0 : (v < -70 ? -70 : v));
        return v;
    }
    
    void linetilde_02_time_set(number v) {
        this->linetilde_02_time = v;
    }
    
    void linetilde_02_segments_set(const list& v) {
        this->linetilde_02_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_02_time == 0) {
                this->linetilde_02_activeRamps->length = 0;
                this->linetilde_02_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_02_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_02_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_02_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_02_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_02_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_02_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_02_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_02_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_02_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_02_activeRamps->push(lastRampValue);
                    this->linetilde_02_activeRamps->push(0);
                    this->linetilde_02_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_02_keepramp)) {
                            this->linetilde_02_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_02_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_02_activeRamps->push(destinationValue);
                    this->linetilde_02_activeRamps->push(inc);
                    this->linetilde_02_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
    
        {
            list converted = {this->expr_02_out1};
            this->linetilde_02_segments_set(converted);
        }
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(rnbo_pow(10, this->expr_02_in1 * 0.05));//#map:mixer/dbtoa_obj-17:1
    }
    
    void linetilde_01_perform(SampleValue * out, Index n) {
        auto __linetilde_01_time = this->linetilde_01_time;
        auto __linetilde_01_keepramp = this->linetilde_01_keepramp;
        auto __linetilde_01_currentValue = this->linetilde_01_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_01_activeRamps->length)) {
            while ((bool)(this->linetilde_01_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_01_activeRamps[0];
                number inc = this->linetilde_01_activeRamps[1];
                number rampTimeInSamples = this->linetilde_01_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_01_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_01_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_01_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -1841075377,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_01_keepramp))) {
                            __linetilde_01_time = 0;
                        }
                    }
                }
    
                __linetilde_01_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_01_currentValue;
            i++;
        }
    
        this->linetilde_01_currentValue = __linetilde_01_currentValue;
        this->linetilde_01_time = __linetilde_01_time;
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void linetilde_02_perform(SampleValue * out, Index n) {
        auto __linetilde_02_time = this->linetilde_02_time;
        auto __linetilde_02_keepramp = this->linetilde_02_keepramp;
        auto __linetilde_02_currentValue = this->linetilde_02_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_02_activeRamps->length)) {
            while ((bool)(this->linetilde_02_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_02_activeRamps[0];
                number inc = this->linetilde_02_activeRamps[1];
                number rampTimeInSamples = this->linetilde_02_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_02_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_02_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_02_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -281953904,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_02_keepramp))) {
                            __linetilde_02_time = 0;
                        }
                    }
                }
    
                __linetilde_02_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_02_currentValue;
            i++;
        }
    
        this->linetilde_02_currentValue = __linetilde_02_currentValue;
        this->linetilde_02_time = __linetilde_02_time;
    }
    
    void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
    }
    
    void param_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_02_value;
    }
    
    void param_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_02_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        linetilde_01_time = 10;
        linetilde_01_keepramp = 0;
        expr_01_in1 = 0;
        expr_01_out1 = 0;
        param_01_value = 0;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0;
        linetilde_02_time = 10;
        linetilde_02_keepramp = 0;
        expr_02_in1 = 0;
        expr_02_out1 = 0;
        param_02_value = -70;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        linetilde_01_currentValue = 1;
        param_01_lastValue = 0;
        linetilde_02_currentValue = 0;
        param_02_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        list linetilde_01_segments;
        number linetilde_01_time;
        number linetilde_01_keepramp;
        number expr_01_in1;
        number expr_01_out1;
        number param_01_value;
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        list linetilde_02_segments;
        number linetilde_02_time;
        number linetilde_02_keepramp;
        number expr_02_in1;
        number expr_02_out1;
        number param_02_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        list linetilde_01_activeRamps;
        number linetilde_01_currentValue;
        number param_01_lastValue;
        list linetilde_02_activeRamps;
        number linetilde_02_currentValue;
        number param_02_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_25 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_25()
    {
    }
    
    ~RNBOSubpatcher_25()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    template <typename T> inline number dim(T& buffer) {
        return buffer->getSize();
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        long numWraps = (long)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    template <typename T> inline void poke_default(
        T& buffer,
        SampleValue value,
        SampleValue sampleIndex,
        int channel,
        number overdub
    ) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
    
        if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
            if (overdub != 0) {
                number currentValue = buffer->getSample(channel, sampleIndex);
    
                {
                    value = value + currentValue * overdub;
                }
            }
    
            buffer->setSample(channel, sampleIndex, value);
            buffer->setTouched(true);
        }
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        this->codebox_tilde_01_perform(in1, in2, in3, in4, this->codebox_tilde_01_freeze, out1, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_03_getPresetValue(getSubState(preset, "freeze"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_03_value_set(v);
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_03_value;
            }
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 1;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "freeze";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "record/freeze";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal0[] = {"off", "on"};
                info->enumValues = eVal0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
    
                {
                    normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
                }
    
                return normalizedValue;
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
            {
            {
                {
                    value = this->applyStepsToNormalizedParameterValue(value, 2);
                }
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_03_value_constrain(value);
            }
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 5) {
            this->codebox_tilde_01_source = new Float64Buffer(this->getPatcher()->source);
        }
    
        if (index == 4) {
            this->codebox_tilde_01_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        }
    
        if (index == 1) {
            this->codebox_tilde_01_scope = new Float32Buffer(this->getPatcher()->scope);
        }
    
        if (index == 0) {
            this->codebox_tilde_01_scope_index = new Float32Buffer(this->getPatcher()->scope_index);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_tilde_01_source = new Float64Buffer(this->getPatcher()->source);
        this->codebox_tilde_01_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        this->codebox_tilde_01_scope = new Float32Buffer(this->getPatcher()->scope);
        this->codebox_tilde_01_scope_index = new Float32Buffer(this->getPatcher()->scope_index);
    }
    
    protected:
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(0, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        this->codebox_tilde_01_freeze_set(v);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 4;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->codebox_tilde_01_counter_src_init();
        this->codebox_tilde_01_counter_view_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
    
        {
            this->scheduleParamInit(0, 0);
        }
    }
    
    void allocateDataRefs() {
        this->codebox_tilde_01_source = this->codebox_tilde_01_source->allocateIfNeeded();
        this->codebox_tilde_01_sample_index = this->codebox_tilde_01_sample_index->allocateIfNeeded();
        this->codebox_tilde_01_scope = this->codebox_tilde_01_scope->allocateIfNeeded();
        this->codebox_tilde_01_scope_index = this->codebox_tilde_01_scope_index->allocateIfNeeded();
    }
    
    number param_03_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void codebox_tilde_01_freeze_set(number v) {
        this->codebox_tilde_01_freeze = v;
    }
    
    void codebox_tilde_01_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        const Sample * in4,
        number freeze,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number state = freeze == 0;
            number index_src = this->codebox_tilde_01_counter_src_next(state, 0, this->dim(this->codebox_tilde_01_source))[0];
            number index_view = this->codebox_tilde_01_counter_view_next(state, 0, this->dim(this->codebox_tilde_01_scope))[0];
            this->poke_default(this->codebox_tilde_01_sample_index, index_src, 0, 0, 0);//#map:_###_obj_###_:14
            this->poke_default(this->codebox_tilde_01_scope_index, index_view, 0, 0, 0);//#map:_###_obj_###_:15
    
            if (state != 0) {
                this->poke_default(
                    this->codebox_tilde_01_source,
                    in1[(Index)i] + in3[(Index)i],
                    index_src,
                    0,
                    0
                );//#map:_###_obj_###_:19
    
                this->poke_default(
                    this->codebox_tilde_01_source,
                    in2[(Index)i] + in4[(Index)i],
                    index_src,
                    1,
                    0
                );//#map:_###_obj_###_:20
    
                this->poke_default(
                    this->codebox_tilde_01_scope,
                    (in1[(Index)i] + in2[(Index)i]) * 0.5,
                    index_view,
                    0,
                    0
                );//#map:_###_obj_###_:21
            }//#map:_###_obj_###_:17
    
            out1[(Index)i] = in1[(Index)i];//#map:_###_obj_###_:24
            out2[(Index)i] = in2[(Index)i];//#map:_###_obj_###_:25
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    array<number, 3> codebox_tilde_01_counter_src_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->codebox_tilde_01_counter_src_count = 0;
            this->codebox_tilde_01_counter_src_carry = 0;
        } else {
            this->codebox_tilde_01_counter_src_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->codebox_tilde_01_counter_src_count >= limit) || (a < 0 && this->codebox_tilde_01_counter_src_count <= limit)) {
                    this->codebox_tilde_01_counter_src_count = 0;
                    this->codebox_tilde_01_counter_src_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->codebox_tilde_01_counter_src_count,
            carry_flag,
            this->codebox_tilde_01_counter_src_carry
        };
    }
    
    void codebox_tilde_01_counter_src_init() {
        this->codebox_tilde_01_counter_src_count = -1;
    }
    
    void codebox_tilde_01_counter_src_reset() {
        this->codebox_tilde_01_counter_src_carry = 0;
        this->codebox_tilde_01_counter_src_count = 0;
    }
    
    array<number, 3> codebox_tilde_01_counter_view_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->codebox_tilde_01_counter_view_count = 0;
            this->codebox_tilde_01_counter_view_carry = 0;
        } else {
            this->codebox_tilde_01_counter_view_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->codebox_tilde_01_counter_view_count >= limit) || (a < 0 && this->codebox_tilde_01_counter_view_count <= limit)) {
                    this->codebox_tilde_01_counter_view_count = 0;
                    this->codebox_tilde_01_counter_view_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->codebox_tilde_01_counter_view_count,
            carry_flag,
            this->codebox_tilde_01_counter_view_carry
        };
    }
    
    void codebox_tilde_01_counter_view_init() {
        this->codebox_tilde_01_counter_view_count = -1;
    }
    
    void codebox_tilde_01_counter_view_reset() {
        this->codebox_tilde_01_counter_view_carry = 0;
        this->codebox_tilde_01_counter_view_count = 0;
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        codebox_tilde_01_in1 = 0;
        codebox_tilde_01_in2 = 0;
        codebox_tilde_01_in3 = 0;
        codebox_tilde_01_in4 = 0;
        codebox_tilde_01_freeze = 0;
        param_03_value = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        codebox_tilde_01_counter_src_carry = 0;
        codebox_tilde_01_counter_src_count = 0;
        codebox_tilde_01_counter_view_carry = 0;
        codebox_tilde_01_counter_view_count = 0;
        param_03_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number codebox_tilde_01_in1;
        number codebox_tilde_01_in2;
        number codebox_tilde_01_in3;
        number codebox_tilde_01_in4;
        number codebox_tilde_01_freeze;
        number param_03_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        int codebox_tilde_01_counter_src_carry;
        number codebox_tilde_01_counter_src_count;
        int codebox_tilde_01_counter_view_carry;
        number codebox_tilde_01_counter_view_count;
        Float64BufferRef codebox_tilde_01_source;
        Float64BufferRef codebox_tilde_01_sample_index;
        Float32BufferRef codebox_tilde_01_scope;
        Float32BufferRef codebox_tilde_01_scope_index;
        number param_03_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_26 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_21 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_26;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_21()
            {
            }
            
            ~RNBOSubpatcher_21()
            {
            }
            
            virtual RNBOSubpatcher_26* getPatcher() const {
                return static_cast<RNBOSubpatcher_26 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_01_out1_bang_bang() {
                this->codebox_01_in1_bang();
            }
            
            void eventinlet_01_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->codebox_01_in1_set(converted);
                }
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void eventoutlet_01_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_01_out1_number_set(v);
            }
            
            void codebox_01_out1_set(number v) {
                this->codebox_01_out1 = v;
                this->eventoutlet_01_in1_number_set(this->codebox_01_out1);
            }
            
            void codebox_01_in1_set(number in1) {
                this->codebox_01_in1 = in1;
                number amp = 0;
            
                if (this->codebox_01_in1 >= -70) {
                    amp = rnbo_pow(10., this->codebox_01_in1 * 0.05);//#map:_###_obj_###_:5
                }//#map:feedback/dbtoa_with_-70inf/codebox_obj-51:3
            
                this->codebox_01_out1_set(amp);//#map:feedback/dbtoa_with_-70inf/codebox_obj-51:8
            }
            
            void eventinlet_01_out1_number_set(number v) {
                this->codebox_01_in1_set(v);
            }
            
            void codebox_01_in1_bang() {
                number amp = 0;
            
                if (this->codebox_01_in1 >= -70) {
                    amp = rnbo_pow(10., this->codebox_01_in1 * 0.05);//#map:_###_obj_###_:5
                }//#map:feedback/dbtoa_with_-70inf/codebox_obj-51:3
            
                this->codebox_01_out1_set(amp);//#map:feedback/dbtoa_with_-70inf/codebox_obj-51:8
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                codebox_01_in1 = 0;
                codebox_01_out1 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number codebox_01_in1;
                number codebox_01_out1;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_26()
    {
    }
    
    ~RNBOSubpatcher_26()
    {
        delete this->p_01;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -281953904, false);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->feedbackwriter_01_perform(in1, n);
        this->feedbackwriter_02_perform(in2, n);
        this->p_01_perform(n);
        this->linetilde_03_perform(this->signals[0], n);
        this->feedbackreader_01_perform(this->signals[1], n);
        this->dcblock_tilde_01_perform(this->signals[1], this->dcblock_tilde_01_gain, this->signals[2], n);
        this->dspexpr_05_perform(this->signals[2], this->signals[0], this->signals[1], n);
        this->gen_01_perform(this->signals[1], this->signals[2], n);
        this->onepole_lin_tilde_01_perform(this->signals[2], this->onepole_lin_tilde_01_linearFreq, out1, n);
        this->feedbackreader_02_perform(this->signals[2], n);
        this->dcblock_tilde_02_perform(this->signals[2], this->dcblock_tilde_02_gain, this->signals[1], n);
        this->dspexpr_06_perform(this->signals[1], this->signals[0], this->signals[2], n);
        this->gen_02_perform(this->signals[2], this->signals[0], n);
        this->onepole_lin_tilde_02_perform(this->signals[0], this->onepole_lin_tilde_02_linearFreq, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 3; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
            this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->dcblock_tilde_01_dspsetup(forceDSPSetup);
        this->onepole_lin_tilde_01_dspsetup(forceDSPSetup);
        this->dcblock_tilde_02_dspsetup(forceDSPSetup);
        this->onepole_lin_tilde_02_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_21();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_04_getPresetValue(getSubState(preset, "damp"));
        this->param_05_getPresetValue(getSubState(preset, "amount"));
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "dbtoa_with_-70inf"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_04_value_set(v);
            break;
            }
        case 1:
            {
            this->param_05_value_set(v);
            break;
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_04_value;
            }
        case 1:
            {
            return this->param_05_value;
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 2 + this->p_01->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "damp";
            }
        case 1:
            {
            return "amount";
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "feedback/damp";
            }
        case 1:
            {
            return "feedback/amount";
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = -70;
                info->min = -70;
                info->max = 30;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "dB";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 2;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 2;
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 1:
            {
            {
                value = (value < -70 ? -70 : (value > 30 ? 30 : value));
                ParameterValue normalizedValue = (value - -70) / (30 - -70);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 1:
            {
            {
                {
                    return -70 + value * (30 - -70);
                }
            }
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_04_value_constrain(value);
            }
        case 1:
            {
            return this->param_05_value_constrain(value);
            }
        default:
            {
            index -= 2;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -281953904:
            {
            this->linetilde_03_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_01->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(0, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->onepole_lin_tilde_02_linearFreq_set(v);
        this->onepole_lin_tilde_01_linearFreq_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(1, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->p_01_in1_number_set(v);
    }
    
    void linetilde_03_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->p_01->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
    }
    
    number param_04_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void onepole_lin_tilde_02_linearFreq_set(number v) {
        this->onepole_lin_tilde_02_linearFreq = v;
    }
    
    void onepole_lin_tilde_01_linearFreq_set(number v) {
        this->onepole_lin_tilde_01_linearFreq = v;
    }
    
    number param_05_value_constrain(number v) const {
        v = (v > 30 ? 30 : (v < -70 ? -70 : v));
        return v;
    }
    
    void linetilde_03_time_set(number v) {
        this->linetilde_03_time = v;
    }
    
    void linetilde_03_segments_set(const list& v) {
        this->linetilde_03_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_03_time == 0) {
                this->linetilde_03_activeRamps->length = 0;
                this->linetilde_03_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_03_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_03_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_03_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_03_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_03_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_03_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_03_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_03_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_03_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_03_activeRamps->push(lastRampValue);
                    this->linetilde_03_activeRamps->push(0);
                    this->linetilde_03_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_03_keepramp)) {
                            this->linetilde_03_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_03_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_03_activeRamps->push(destinationValue);
                    this->linetilde_03_activeRamps->push(inc);
                    this->linetilde_03_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void pack_01_out_set(const list& v) {
        this->linetilde_03_segments_set(v);
    }
    
    void pack_01_in1_set(number v) {
        this->pack_01_in1 = v;
        list array = list(0, 0);
        array[0] = this->pack_01_in1;
        array[1] = this->pack_01_in2;
        this->pack_01_out_set(array);
    }
    
    void p_01_out1_number_set(number v) {
        this->pack_01_in1_set(v);
    }
    
    void p_01_in1_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_01_out1_number_set(v);
    }
    
    void feedbackwriter_01_perform(const SampleValue * input, Index n) {
        auto& buffer = this->feedbacktilde_01_feedbackbuffer;
    
        for (Index i = 0; i < n; i++) {
            buffer[(Index)i] = input[(Index)i];
        }
    }
    
    void feedbackwriter_02_perform(const SampleValue * input, Index n) {
        auto& buffer = this->feedbacktilde_02_feedbackbuffer;
    
        for (Index i = 0; i < n; i++) {
            buffer[(Index)i] = input[(Index)i];
        }
    }
    
    void p_01_perform(Index n) {
        // subpatcher: dbtoa_with_-70inf
        this->p_01->process(nullptr, 0, nullptr, 0, n);
    }
    
    void linetilde_03_perform(SampleValue * out, Index n) {
        auto __linetilde_03_time = this->linetilde_03_time;
        auto __linetilde_03_keepramp = this->linetilde_03_keepramp;
        auto __linetilde_03_currentValue = this->linetilde_03_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_03_activeRamps->length)) {
            while ((bool)(this->linetilde_03_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_03_activeRamps[0];
                number inc = this->linetilde_03_activeRamps[1];
                number rampTimeInSamples = this->linetilde_03_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_03_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_03_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_03_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -281953904,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_03_keepramp))) {
                            __linetilde_03_time = 0;
                        }
                    }
                }
    
                __linetilde_03_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_03_currentValue;
            i++;
        }
    
        this->linetilde_03_currentValue = __linetilde_03_currentValue;
        this->linetilde_03_time = __linetilde_03_time;
    }
    
    void feedbackreader_01_perform(SampleValue * output, Index n) {
        auto& buffer = this->feedbacktilde_01_feedbackbuffer;
    
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = buffer[(Index)i];
        }
    }
    
    void dcblock_tilde_01_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
        RNBO_UNUSED(gain);
        auto __dcblock_tilde_01_ym1 = this->dcblock_tilde_01_ym1;
        auto __dcblock_tilde_01_xm1 = this->dcblock_tilde_01_xm1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number y = x[(Index)i] - __dcblock_tilde_01_xm1 + __dcblock_tilde_01_ym1 * 0.9997;
            __dcblock_tilde_01_xm1 = x[(Index)i];
            __dcblock_tilde_01_ym1 = y;
            out1[(Index)i] = y;
        }
    
        this->dcblock_tilde_01_xm1 = __dcblock_tilde_01_xm1;
        this->dcblock_tilde_01_ym1 = __dcblock_tilde_01_ym1;
    }
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void gen_01_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            // gen title: rational_tanh
            number expr_1_0 = 0;
    
            if (in1[(Index)i] < -3) {
                expr_1_0 = -1;
            } else if (in1[(Index)i] > 3) {
                expr_1_0 = 1;
            } else {
                expr_1_0 = (27 + 9 * in1[(Index)i] * in1[(Index)i] == 0. ? 0. : in1[(Index)i] * (27 + in1[(Index)i] * in1[(Index)i]) / (27 + 9 * in1[(Index)i] * in1[(Index)i]));
            }
    
            out1[(Index)i] = expr_1_0;
        }
    }
    
    void onepole_lin_tilde_01_perform(const Sample * x, number linearFreq, SampleValue * out1, Index n) {
        auto __onepole_lin_tilde_01_lastY = this->onepole_lin_tilde_01_lastY;
        auto __onepole_lin_tilde_01_b1 = this->onepole_lin_tilde_01_b1;
        auto __onepole_lin_tilde_01_a0 = this->onepole_lin_tilde_01_a0;
        auto __onepole_lin_tilde_01_needsUpdate = this->onepole_lin_tilde_01_needsUpdate;
        auto __onepole_lin_tilde_01_freq = this->onepole_lin_tilde_01_freq;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (__onepole_lin_tilde_01_freq != linearFreq || (bool)(__onepole_lin_tilde_01_needsUpdate)) {
                __onepole_lin_tilde_01_freq = linearFreq;
                __onepole_lin_tilde_01_a0 = (linearFreq > 0.99999 ? 0.99999 : (linearFreq < 0.00001 ? 0.00001 : linearFreq));
                __onepole_lin_tilde_01_b1 = 1.0 - __onepole_lin_tilde_01_a0;
                __onepole_lin_tilde_01_needsUpdate = false;
            }
    
            __onepole_lin_tilde_01_lastY = __onepole_lin_tilde_01_a0 * x[(Index)i] + __onepole_lin_tilde_01_b1 * __onepole_lin_tilde_01_lastY;
            out1[(Index)i] = __onepole_lin_tilde_01_lastY;
        }
    
        this->onepole_lin_tilde_01_freq = __onepole_lin_tilde_01_freq;
        this->onepole_lin_tilde_01_needsUpdate = __onepole_lin_tilde_01_needsUpdate;
        this->onepole_lin_tilde_01_a0 = __onepole_lin_tilde_01_a0;
        this->onepole_lin_tilde_01_b1 = __onepole_lin_tilde_01_b1;
        this->onepole_lin_tilde_01_lastY = __onepole_lin_tilde_01_lastY;
    }
    
    void feedbackreader_02_perform(SampleValue * output, Index n) {
        auto& buffer = this->feedbacktilde_02_feedbackbuffer;
    
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = buffer[(Index)i];
        }
    }
    
    void dcblock_tilde_02_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
        RNBO_UNUSED(gain);
        auto __dcblock_tilde_02_ym1 = this->dcblock_tilde_02_ym1;
        auto __dcblock_tilde_02_xm1 = this->dcblock_tilde_02_xm1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number y = x[(Index)i] - __dcblock_tilde_02_xm1 + __dcblock_tilde_02_ym1 * 0.9997;
            __dcblock_tilde_02_xm1 = x[(Index)i];
            __dcblock_tilde_02_ym1 = y;
            out1[(Index)i] = y;
        }
    
        this->dcblock_tilde_02_xm1 = __dcblock_tilde_02_xm1;
        this->dcblock_tilde_02_ym1 = __dcblock_tilde_02_ym1;
    }
    
    void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void gen_02_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            // gen title: rational_tanh
            number expr_1_0 = 0;
    
            if (in1[(Index)i] < -3) {
                expr_1_0 = -1;
            } else if (in1[(Index)i] > 3) {
                expr_1_0 = 1;
            } else {
                expr_1_0 = (27 + 9 * in1[(Index)i] * in1[(Index)i] == 0. ? 0. : in1[(Index)i] * (27 + in1[(Index)i] * in1[(Index)i]) / (27 + 9 * in1[(Index)i] * in1[(Index)i]));
            }
    
            out1[(Index)i] = expr_1_0;
        }
    }
    
    void onepole_lin_tilde_02_perform(const Sample * x, number linearFreq, SampleValue * out1, Index n) {
        auto __onepole_lin_tilde_02_lastY = this->onepole_lin_tilde_02_lastY;
        auto __onepole_lin_tilde_02_b1 = this->onepole_lin_tilde_02_b1;
        auto __onepole_lin_tilde_02_a0 = this->onepole_lin_tilde_02_a0;
        auto __onepole_lin_tilde_02_needsUpdate = this->onepole_lin_tilde_02_needsUpdate;
        auto __onepole_lin_tilde_02_freq = this->onepole_lin_tilde_02_freq;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (__onepole_lin_tilde_02_freq != linearFreq || (bool)(__onepole_lin_tilde_02_needsUpdate)) {
                __onepole_lin_tilde_02_freq = linearFreq;
                __onepole_lin_tilde_02_a0 = (linearFreq > 0.99999 ? 0.99999 : (linearFreq < 0.00001 ? 0.00001 : linearFreq));
                __onepole_lin_tilde_02_b1 = 1.0 - __onepole_lin_tilde_02_a0;
                __onepole_lin_tilde_02_needsUpdate = false;
            }
    
            __onepole_lin_tilde_02_lastY = __onepole_lin_tilde_02_a0 * x[(Index)i] + __onepole_lin_tilde_02_b1 * __onepole_lin_tilde_02_lastY;
            out1[(Index)i] = __onepole_lin_tilde_02_lastY;
        }
    
        this->onepole_lin_tilde_02_freq = __onepole_lin_tilde_02_freq;
        this->onepole_lin_tilde_02_needsUpdate = __onepole_lin_tilde_02_needsUpdate;
        this->onepole_lin_tilde_02_a0 = __onepole_lin_tilde_02_a0;
        this->onepole_lin_tilde_02_b1 = __onepole_lin_tilde_02_b1;
        this->onepole_lin_tilde_02_lastY = __onepole_lin_tilde_02_lastY;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void onepole_lin_tilde_01_dspsetup(bool force) {
        if ((bool)(this->onepole_lin_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->onepole_lin_tilde_01_needsUpdate = true;
        this->onepole_lin_tilde_01_setupDone = true;
    }
    
    void dcblock_tilde_01_reset() {
        this->dcblock_tilde_01_xm1 = 0;
        this->dcblock_tilde_01_ym1 = 0;
    }
    
    void dcblock_tilde_01_dspsetup(bool force) {
        if ((bool)(this->dcblock_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->dcblock_tilde_01_reset();
        this->dcblock_tilde_01_setupDone = true;
    }
    
    void onepole_lin_tilde_02_dspsetup(bool force) {
        if ((bool)(this->onepole_lin_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->onepole_lin_tilde_02_needsUpdate = true;
        this->onepole_lin_tilde_02_setupDone = true;
    }
    
    void dcblock_tilde_02_reset() {
        this->dcblock_tilde_02_xm1 = 0;
        this->dcblock_tilde_02_ym1 = 0;
    }
    
    void dcblock_tilde_02_dspsetup(bool force) {
        if ((bool)(this->dcblock_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->dcblock_tilde_02_reset();
        this->dcblock_tilde_02_setupDone = true;
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        onepole_lin_tilde_01_x = 0;
        onepole_lin_tilde_01_linearFreq = 0;
        gen_01_in1 = 0;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        dcblock_tilde_01_x = 0;
        dcblock_tilde_01_gain = 0.9997;
        onepole_lin_tilde_02_x = 0;
        onepole_lin_tilde_02_linearFreq = 0;
        gen_02_in1 = 0;
        dcblock_tilde_02_x = 0;
        dcblock_tilde_02_gain = 0.9997;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        param_04_value = 1;
        p_01_target = 0;
        linetilde_03_time = 0;
        linetilde_03_keepramp = 0;
        pack_01_in1 = 0;
        pack_01_in2 = 50;
        param_05_value = -70;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        onepole_lin_tilde_01_freq = 0;
        onepole_lin_tilde_01_needsUpdate = false;
        onepole_lin_tilde_01_lastY = 0;
        onepole_lin_tilde_01_a0 = 0;
        onepole_lin_tilde_01_b1 = 0;
        onepole_lin_tilde_01_setupDone = false;
        dcblock_tilde_01_xm1 = 0;
        dcblock_tilde_01_ym1 = 0;
        dcblock_tilde_01_setupDone = false;
        feedbacktilde_01_feedbackbuffer = nullptr;
        onepole_lin_tilde_02_freq = 0;
        onepole_lin_tilde_02_needsUpdate = false;
        onepole_lin_tilde_02_lastY = 0;
        onepole_lin_tilde_02_a0 = 0;
        onepole_lin_tilde_02_b1 = 0;
        onepole_lin_tilde_02_setupDone = false;
        dcblock_tilde_02_xm1 = 0;
        dcblock_tilde_02_ym1 = 0;
        dcblock_tilde_02_setupDone = false;
        feedbacktilde_02_feedbackbuffer = nullptr;
        param_04_lastValue = 0;
        linetilde_03_currentValue = 0;
        param_05_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number onepole_lin_tilde_01_x;
        number onepole_lin_tilde_01_linearFreq;
        number gen_01_in1;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number dcblock_tilde_01_x;
        number dcblock_tilde_01_gain;
        number onepole_lin_tilde_02_x;
        number onepole_lin_tilde_02_linearFreq;
        number gen_02_in1;
        number dcblock_tilde_02_x;
        number dcblock_tilde_02_gain;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number param_04_value;
        number p_01_target;
        list linetilde_03_segments;
        number linetilde_03_time;
        number linetilde_03_keepramp;
        number pack_01_in1;
        number pack_01_in2;
        number param_05_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[3];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number onepole_lin_tilde_01_freq;
        bool onepole_lin_tilde_01_needsUpdate;
        number onepole_lin_tilde_01_lastY;
        number onepole_lin_tilde_01_a0;
        number onepole_lin_tilde_01_b1;
        bool onepole_lin_tilde_01_setupDone;
        number dcblock_tilde_01_xm1;
        number dcblock_tilde_01_ym1;
        bool dcblock_tilde_01_setupDone;
        signal feedbacktilde_01_feedbackbuffer;
        number onepole_lin_tilde_02_freq;
        bool onepole_lin_tilde_02_needsUpdate;
        number onepole_lin_tilde_02_lastY;
        number onepole_lin_tilde_02_a0;
        number onepole_lin_tilde_02_b1;
        bool onepole_lin_tilde_02_setupDone;
        number dcblock_tilde_02_xm1;
        number dcblock_tilde_02_ym1;
        bool dcblock_tilde_02_setupDone;
        signal feedbacktilde_02_feedbackbuffer;
        number param_04_lastValue;
        list linetilde_03_activeRamps;
        number linetilde_03_currentValue;
        number param_05_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_21* p_01;
    
};

class RNBOSubpatcher_27 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_27()
    {
    }
    
    ~RNBOSubpatcher_27()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1333657855, false);
        getEngine()->flushClockEvents(this, -611950441, false);
        getEngine()->flushClockEvents(this, -1584063977, false);
    }
    
    number random(number low, number high) {
        number range = high - low;
        return globalrandom() * range + low;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        long numWraps = (long)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numOutputs);
        RNBO_UNUSED(outputs);
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        this->phasor_01_perform(this->phasor_01_freq, this->signals[0], n);
        this->delta_tilde_01_perform(this->signals[0], this->signals[1], n);
        this->dspexpr_07_perform(this->signals[1], this->dspexpr_07_in2, this->signals[0], n);
        this->edge_01_perform(this->signals[0], n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->phasor_01_dspsetup(forceDSPSetup);
        this->delta_tilde_01_dspsetup(forceDSPSetup);
        this->edge_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_06_getPresetValue(getSubState(preset, "density"));
        this->param_07_getPresetValue(getSubState(preset, "probability"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_06_value_set(v);
            break;
            }
        case 1:
            {
            this->param_07_value_set(v);
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_06_value;
            }
        case 1:
            {
            return this->param_07_value;
            }
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 2;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "density";
            }
        case 1:
            {
            return "probability";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "trigger/density";
            }
        case 1:
            {
            return "trigger/probability";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 2000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "Hz";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
                ParameterValue normalizedValue = (value - 0) / (2000 - 0);
                return normalizedValue;
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 1:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 0:
            {
            {
                {
                    return 0 + value * (2000 - 0);
                }
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_06_value_constrain(value);
            }
        case 1:
            {
            return this->param_07_value_constrain(value);
            }
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1333657855:
            {
            this->codebox_02_in1_bang();
            break;
            }
        case -611950441:
            {
            this->edge_01_onout_bang();
            break;
            }
        case -1584063977:
            {
            this->edge_01_offout_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 7) {
            this->codebox_02_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_02_note_count = new Float64Buffer(this->getPatcher()->note_count);
    }
    
    protected:
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(0, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->phasor_01_freq_set(v);
    }
    
    void param_07_value_set(number v) {
        v = this->param_07_value_constrain(v);
        this->param_07_value = v;
        this->sendParameter(1, false);
    
        if (this->param_07_value != this->param_07_lastValue) {
            this->getEngine()->presetTouched();
            this->param_07_lastValue = this->param_07_value;
        }
    
        this->codebox_02_probability_set(v);
    }
    
    void codebox_02_in1_bang() {
        if (this->codebox_02_note_count->getSampleSafe(0, 0) > 0) {
            if (this->random(0, 1) <= this->codebox_02_probability) {
                this->codebox_02_out1_set(this->codebox_02_counter);//#map:_###_obj_###_:12
                this->codebox_02_counter += 1;//#map:_###_obj_###_:13
                this->codebox_02_counter = this->wrap(this->codebox_02_counter, 1, this->codebox_02_voice_num + 1);//#map:_###_obj_###_:14
            }//#map:_###_obj_###_:10
        }//#map:trigger/codebox_obj-12:7
    }
    
    void edge_01_onout_bang() {
        this->codebox_02_in1_bang();
    }
    
    void edge_01_offout_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 0;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->getEngine()->scheduleClockEvent(this, -1333657855, 0 + this->_currentTime);;
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    }
    
    void allocateDataRefs() {
        this->codebox_02_note_count = this->codebox_02_note_count->allocateIfNeeded();
    }
    
    number param_06_value_constrain(number v) const {
        v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void phasor_01_freq_set(number v) {
        this->phasor_01_freq = v;
    }
    
    number param_07_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number codebox_02_probability_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void codebox_02_probability_set(number v) {
        v = this->codebox_02_probability_constrain(v);
        this->codebox_02_probability = v;
    }
    
    void eventoutlet_02_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_07_out1_number_set(v);
    }
    
    void codebox_02_out1_set(number v) {
        this->codebox_02_out1 = v;
        this->eventoutlet_02_in1_number_set(this->codebox_02_out1);
    }
    
    void phasor_01_perform(number freq, SampleValue * out, Index n) {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->phasor_01_ph_next(freq, -1);
            this->phasor_01_sigbuf[(Index)i] = -1;
        }
    }
    
    void delta_tilde_01_perform(const Sample * x, SampleValue * out1, Index n) {
        auto __delta_tilde_01_prev = this->delta_tilde_01_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = (number)(x[(Index)i] - __delta_tilde_01_prev);
            __delta_tilde_01_prev = x[(Index)i];
            out1[(Index)i] = temp;
        }
    
        this->delta_tilde_01_prev = __delta_tilde_01_prev;
    }
    
    void dspexpr_07_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
        }
    }
    
    void edge_01_perform(const SampleValue * input, Index n) {
        auto __edge_01_currentState = this->edge_01_currentState;
    
        for (Index i = 0; i < n; i++) {
            if (__edge_01_currentState == 1) {
                if (input[(Index)i] == 0.) {
                    this->getEngine()->scheduleClockEvent(this, -1584063977, this->sampsToMs(i) + this->_currentTime);;
                    __edge_01_currentState = 0;
                }
            } else {
                if (input[(Index)i] != 0.) {
                    this->getEngine()->scheduleClockEvent(this, -611950441, this->sampsToMs(i) + this->_currentTime);;
                    __edge_01_currentState = 1;
                }
            }
        }
    
        this->edge_01_currentState = __edge_01_currentState;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void edge_01_dspsetup(bool force) {
        if ((bool)(this->edge_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->edge_01_setupDone = true;
    }
    
    void delta_tilde_01_reset() {
        this->delta_tilde_01_prev = 0;
    }
    
    void delta_tilde_01_dspsetup(bool force) {
        if ((bool)(this->delta_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->delta_tilde_01_reset();
        this->delta_tilde_01_setupDone = true;
    }
    
    number phasor_01_ph_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->phasor_01_ph_conv;
    
        if (this->phasor_01_ph_currentPhase < 0.)
            this->phasor_01_ph_currentPhase = 1. + this->phasor_01_ph_currentPhase;
    
        if (this->phasor_01_ph_currentPhase > 1.)
            this->phasor_01_ph_currentPhase = this->phasor_01_ph_currentPhase - 1.;
    
        number tmp = this->phasor_01_ph_currentPhase;
        this->phasor_01_ph_currentPhase += pincr;
        return tmp;
    }
    
    void phasor_01_ph_reset() {
        this->phasor_01_ph_currentPhase = 0;
    }
    
    void phasor_01_ph_dspsetup() {
        this->phasor_01_ph_conv = (number)1 / this->sr;
    }
    
    void phasor_01_dspsetup(bool force) {
        if ((bool)(this->phasor_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->phasor_01_conv = (number)1 / this->samplerate();
        this->phasor_01_setupDone = true;
        this->phasor_01_ph_dspsetup();
    }
    
    void param_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_07_value;
    }
    
    void param_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_07_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        codebox_02_out1 = 0;
        codebox_02_probability = 1;
        codebox_02_voice_num = 2500;
        param_06_value = 1;
        dspexpr_07_in1 = 0;
        dspexpr_07_in2 = 0;
        delta_tilde_01_x = 0;
        phasor_01_freq = 0;
        param_07_value = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        codebox_02_counter = 1;
        param_06_lastValue = 0;
        edge_01_setupDone = false;
        delta_tilde_01_prev = 0;
        delta_tilde_01_setupDone = false;
        phasor_01_sigbuf = nullptr;
        phasor_01_lastLockedPhase = 0;
        phasor_01_conv = 0;
        phasor_01_ph_currentPhase = 0;
        phasor_01_ph_conv = 0;
        phasor_01_setupDone = false;
        param_07_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number codebox_02_out1;
        number codebox_02_probability;
        number codebox_02_voice_num;
        number param_06_value;
        number dspexpr_07_in1;
        number dspexpr_07_in2;
        number delta_tilde_01_x;
        number phasor_01_freq;
        number param_07_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number codebox_02_counter;
        Float64BufferRef codebox_02_note_count;
        number param_06_lastValue;
        number edge_01_currentState;
        bool edge_01_setupDone;
        number delta_tilde_01_prev;
        bool delta_tilde_01_setupDone;
        signal phasor_01_sigbuf;
        number phasor_01_lastLockedPhase;
        number phasor_01_conv;
        number phasor_01_ph_currentPhase;
        number phasor_01_ph_conv;
        bool phasor_01_setupDone;
        number param_07_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_28 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_22 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_28;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_22()
            {
            }
            
            ~RNBOSubpatcher_22()
            {
            }
            
            virtual RNBOSubpatcher_28* getPatcher() const {
                return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_02_out1_bang_bang() {
                this->floatnum_01_input_bang_bang();
            }
            
            void eventinlet_02_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->floatnum_01_input_number_set(converted);
                }
            }
            
            void eventinlet_03_out1_bang_bang() {
                this->trigger_01_input_bang_bang();
            }
            
            void eventinlet_03_out1_list_set(const list& v) {
                this->trigger_01_input_list_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void maximum_01_index_set(number v) {
                this->maximum_01_index = v;
            }
            
            void eventoutlet_04_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_02_out2_number_set(v);
            }
            
            void maximum_01_out_set(number v) {
                this->maximum_01_out = v;
                this->eventoutlet_04_in1_number_set(v);
            }
            
            void maximum_01_input_set(const list& v) {
                this->maximum_01_input = jsCreateListCopy(v);
            
                if (v->length == 1) {
                    if (v[0] > this->maximum_01_right) {
                        this->maximum_01_index_set(0);
                        this->maximum_01_out_set(v[0]);
                    } else {
                        this->maximum_01_index_set(1);
                        this->maximum_01_out_set(this->maximum_01_right);
                    }
                } else if (v->length > 0) {
                    int idx = 0;
                    number maximum = v[0];
            
                    for (Index i = 1; i < v->length; i++) {
                        if (v[(Index)i] > maximum) {
                            maximum = v[(Index)i];
                            idx = i;
                        }
                    }
            
                    this->maximum_01_index_set(idx);
                    this->maximum_01_out_set(maximum);
                }
            }
            
            void minimum_01_index_set(number v) {
                this->minimum_01_index = v;
            }
            
            void eventoutlet_03_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_02_out1_number_set(v);
            }
            
            void minimum_01_out_set(number v) {
                this->minimum_01_out = v;
                this->eventoutlet_03_in1_number_set(v);
            }
            
            void minimum_01_input_set(const list& v) {
                this->minimum_01_input = jsCreateListCopy(v);
            
                if (v->length == 1) {
                    if (v[0] < this->minimum_01_right) {
                        this->minimum_01_index_set(0);
                        this->minimum_01_out_set(v[0]);
                    } else {
                        this->minimum_01_index_set(1);
                        this->minimum_01_out_set(this->minimum_01_right);
                    }
                } else if (v->length > 0) {
                    int idx = 0;
                    number minimum = v[0];
            
                    for (Index i = 1; i < v->length; i++) {
                        if (v[(Index)i] < minimum) {
                            minimum = v[(Index)i];
                            idx = i;
                        }
                    }
            
                    this->minimum_01_index_set(idx);
                    this->minimum_01_out_set(minimum);
                }
            }
            
            void floatnum_01_out_set(number v) {
                {
                    list converted = {v};
                    this->maximum_01_input_set(converted);
                }
            
                {
                    list converted = {v};
                    this->minimum_01_input_set(converted);
                }
            }
            
            void floatnum_01_input_number_set(number v) {
                this->floatnum_01_input_number = v;
                this->floatnum_01_stored = v;
                this->floatnum_01_out_set(v);
            }
            
            void eventinlet_02_out1_number_set(number v) {
                this->floatnum_01_input_number_set(v);
            }
            
            void maximum_01_right_set(number v) {
                this->maximum_01_right = v;
            }
            
            void minimum_01_right_set(number v) {
                this->minimum_01_right = v;
            }
            
            void trigger_01_out2_set(number v) {
                this->maximum_01_right_set(v);
                this->minimum_01_right_set(v);
            }
            
            void floatnum_01_input_bang_bang() {
                this->floatnum_01_out_set(this->floatnum_01_stored);
            }
            
            void trigger_01_out1_bang() {
                this->floatnum_01_input_bang_bang();
            }
            
            void trigger_01_input_number_set(number v) {
                this->trigger_01_out2_set(v);
                this->trigger_01_out1_bang();
            }
            
            void eventinlet_03_out1_number_set(number v) {
                this->trigger_01_input_number_set(v);
            }
            
            void trigger_01_input_bang_bang() {
                this->trigger_01_out2_set(0);
                this->trigger_01_out1_bang();
            }
            
            void trigger_01_input_list_set(const list& v) {
                this->trigger_01_out2_set((v->length > 0 ? v[0] : 0));
                this->trigger_01_out1_bang();
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                floatnum_01_input_number = 0;
                floatnum_01_value = 0;
                minimum_01_right = 0;
                minimum_01_out = 0;
                minimum_01_index = 0;
                maximum_01_right = 0;
                maximum_01_out = 0;
                maximum_01_index = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                floatnum_01_stored = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number floatnum_01_input_number;
                number floatnum_01_value;
                list minimum_01_input;
                number minimum_01_right;
                number minimum_01_out;
                number minimum_01_index;
                list maximum_01_input;
                number maximum_01_right;
                number maximum_01_out;
                number maximum_01_index;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number floatnum_01_stored;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_23 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_28;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_23()
            {
            }
            
            ~RNBOSubpatcher_23()
            {
            }
            
            virtual RNBOSubpatcher_28* getPatcher() const {
                return static_cast<RNBOSubpatcher_28 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void eventinlet_04_out1_bang_bang() {
                this->floatnum_02_input_bang_bang();
            }
            
            void eventinlet_04_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->floatnum_02_input_number_set(converted);
                }
            }
            
            void eventinlet_05_out1_bang_bang() {
                this->trigger_02_input_bang_bang();
            }
            
            void eventinlet_05_out1_list_set(const list& v) {
                this->trigger_02_input_list_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void maximum_02_index_set(number v) {
                this->maximum_02_index = v;
            }
            
            void eventoutlet_06_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_03_out2_number_set(v);
            }
            
            void maximum_02_out_set(number v) {
                this->maximum_02_out = v;
                this->eventoutlet_06_in1_number_set(v);
            }
            
            void maximum_02_input_set(const list& v) {
                this->maximum_02_input = jsCreateListCopy(v);
            
                if (v->length == 1) {
                    if (v[0] > this->maximum_02_right) {
                        this->maximum_02_index_set(0);
                        this->maximum_02_out_set(v[0]);
                    } else {
                        this->maximum_02_index_set(1);
                        this->maximum_02_out_set(this->maximum_02_right);
                    }
                } else if (v->length > 0) {
                    int idx = 0;
                    number maximum = v[0];
            
                    for (Index i = 1; i < v->length; i++) {
                        if (v[(Index)i] > maximum) {
                            maximum = v[(Index)i];
                            idx = i;
                        }
                    }
            
                    this->maximum_02_index_set(idx);
                    this->maximum_02_out_set(maximum);
                }
            }
            
            void minimum_02_index_set(number v) {
                this->minimum_02_index = v;
            }
            
            void eventoutlet_05_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_03_out1_number_set(v);
            }
            
            void minimum_02_out_set(number v) {
                this->minimum_02_out = v;
                this->eventoutlet_05_in1_number_set(v);
            }
            
            void minimum_02_input_set(const list& v) {
                this->minimum_02_input = jsCreateListCopy(v);
            
                if (v->length == 1) {
                    if (v[0] < this->minimum_02_right) {
                        this->minimum_02_index_set(0);
                        this->minimum_02_out_set(v[0]);
                    } else {
                        this->minimum_02_index_set(1);
                        this->minimum_02_out_set(this->minimum_02_right);
                    }
                } else if (v->length > 0) {
                    int idx = 0;
                    number minimum = v[0];
            
                    for (Index i = 1; i < v->length; i++) {
                        if (v[(Index)i] < minimum) {
                            minimum = v[(Index)i];
                            idx = i;
                        }
                    }
            
                    this->minimum_02_index_set(idx);
                    this->minimum_02_out_set(minimum);
                }
            }
            
            void floatnum_02_out_set(number v) {
                {
                    list converted = {v};
                    this->maximum_02_input_set(converted);
                }
            
                {
                    list converted = {v};
                    this->minimum_02_input_set(converted);
                }
            }
            
            void floatnum_02_input_number_set(number v) {
                this->floatnum_02_input_number = v;
                this->floatnum_02_stored = v;
                this->floatnum_02_out_set(v);
            }
            
            void eventinlet_04_out1_number_set(number v) {
                this->floatnum_02_input_number_set(v);
            }
            
            void maximum_02_right_set(number v) {
                this->maximum_02_right = v;
            }
            
            void minimum_02_right_set(number v) {
                this->minimum_02_right = v;
            }
            
            void trigger_02_out2_set(number v) {
                this->maximum_02_right_set(v);
                this->minimum_02_right_set(v);
            }
            
            void floatnum_02_input_bang_bang() {
                this->floatnum_02_out_set(this->floatnum_02_stored);
            }
            
            void trigger_02_out1_bang() {
                this->floatnum_02_input_bang_bang();
            }
            
            void trigger_02_input_number_set(number v) {
                this->trigger_02_out2_set(v);
                this->trigger_02_out1_bang();
            }
            
            void eventinlet_05_out1_number_set(number v) {
                this->trigger_02_input_number_set(v);
            }
            
            void trigger_02_input_bang_bang() {
                this->trigger_02_out2_set(0);
                this->trigger_02_out1_bang();
            }
            
            void trigger_02_input_list_set(const list& v) {
                this->trigger_02_out2_set((v->length > 0 ? v[0] : 0));
                this->trigger_02_out1_bang();
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                floatnum_02_input_number = 0;
                floatnum_02_value = 0;
                minimum_02_right = 0;
                minimum_02_out = 0;
                minimum_02_index = 0;
                maximum_02_right = 0;
                maximum_02_out = 0;
                maximum_02_index = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                floatnum_02_stored = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number floatnum_02_input_number;
                number floatnum_02_value;
                list minimum_02_input;
                number minimum_02_right;
                number minimum_02_out;
                number minimum_02_index;
                list maximum_02_input;
                number maximum_02_right;
                number maximum_02_out;
                number maximum_02_index;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number floatnum_02_stored;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_28()
    {
    }
    
    ~RNBOSubpatcher_28()
    {
        delete this->p_02;
        delete this->p_03;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1313779944, false);
        getEngine()->flushClockEvents(this, 1151781846, false);
        getEngine()->flushClockEvents(this, -611950441, false);
        getEngine()->flushClockEvents(this, -1584063977, false);
        getEngine()->flushClockEvents(this, -1735137014, false);
        getEngine()->flushClockEvents(this, -871642103, false);
        getEngine()->flushClockEvents(this, 892732297, false);
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    number random(number low, number high) {
        number range = high - low;
        return globalrandom() * range + low;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        long numWraps = (long)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number cubicinterp(number a, number w, number x, number y, number z) {
        number a1 = 1. + a;
        number aa = a * a1;
        number b = 1. - a;
        number b1 = 2. - a;
        number bb = b * b1;
        number fw = -.1666667 * bb * a;
        number fx = .5 * bb * a1;
        number fy = .5 * aa * b1;
        number fz = -.1666667 * aa * b;
        return w * fw + x * fx + y * fy + z * fz;
    }
    
    inline number fastcubicinterp(number a, number w, number x, number y, number z) {
        number a2 = a * a;
        number f0 = z - y - w + x;
        number f1 = w - x - f0;
        number f2 = y - w;
        number f3 = x;
        return f0 * a * a2 + f1 * a2 + f2 * a + f3;
    }
    
    inline number splineinterp(number a, number w, number x, number y, number z) {
        number a2 = a * a;
        number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
        number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
        number f2 = -0.5 * w + 0.5 * y;
        return f0 * a * a2 + f1 * a2 + f2 * a + x;
    }
    
    inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
        number ym2py2 = y0 + y4;
        number ym1py1 = y1 + y3;
        number y2mym2 = y4 - y0;
        number y1mym1 = y3 - y1;
        number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
        number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
        number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
        number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
        number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
        number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
        number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
        return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
    }
    
    inline number cosT8(number r) {
        number t84 = 56.0;
        number t83 = 1680.0;
        number t82 = 20160.0;
        number t81 = 2.4801587302e-05;
        number t73 = 42.0;
        number t72 = 840.0;
        number t71 = 1.9841269841e-04;
    
        if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
            number rr = r * r;
            return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
        } else if (r > 0.0) {
            r -= 1.57079632679489661923132169163975144;
            number rr = r * r;
            return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
        } else {
            r += 1.57079632679489661923132169163975144;
            number rr = r * r;
            return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
        }
    }
    
    inline number cosineinterp(number frac, number x, number y) {
        number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
        return x * (1.0 - a2) + y * a2;
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    template <typename T> inline array<SampleValue, 1 + 1> peek_default(T& buffer, SampleValue sampleIndex, Index channelOffset) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
        constexpr int ___N2 = 1 + 1;
        array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);
    
        if (bufferSize == 0 || (5 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
            return out;
        } else {
            for (Index channel = 0; channel < 1; channel++) {
                Index channelIndex = (Index)(channel + channelOffset);
    
                {
                    if (channelIndex >= bufferChannels || channelIndex < 0) {
                        out[(Index)channel] = 0;
                        continue;
                    }
                }
    
                SampleValue bufferreadsample_result;
    
                {
                    auto& __buffer = buffer;
    
                    if (sampleIndex < 0.0) {
                        bufferreadsample_result = 0.0;
                    }
    
                    SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        bufferreadsample_result = __buffer->getSample(channelIndex, truncIndex);
                    }
                }
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
            return out;
        }
    }
    
    inline number intnum(const number value) {
        return trunc(value);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    number minimum(number x, number y) {
        return (y < x ? y : x);
    }
    
    template <typename T> inline number dim(T& buffer) {
        return buffer->getSize();
    }
    
    template <typename T> inline array<SampleValue, 1 + 1> sample_default(T& buffer, SampleValue sampleIndex, Index channelOffset) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
        constexpr int ___N3 = 1 + 1;
        array<SampleValue, ___N3> out = FIXEDSIZEARRAYINIT(1 + 1);
    
        {
            SampleValue bufferphasetoindex_result;
    
            {
                auto __end = bufferSize;
                auto __start = 0;
                auto __phase = sampleIndex;
                number size;
    
                {
                    size = __end - __start - 1;
                }
    
                {
                    bufferphasetoindex_result = __phase * size;
                }
            }
    
            sampleIndex = bufferphasetoindex_result;
        }
    
        if (bufferSize == 0 || (5 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
            for (Index i = 0; i < 1 + 1; i++) {
                out[(Index)i] = 0;
            }
        } else {
            for (Index channel = 0; channel < 1; channel++) {
                Index channelIndex = (Index)(channel + channelOffset);
    
                {
                    if (channelIndex >= bufferChannels || channelIndex < 0) {
                        out[(Index)channel] = 0;
                        continue;
                    }
                }
    
                SampleValue bufferreadsample_result;
    
                {
                    auto& __buffer = buffer;
    
                    if (sampleIndex < 0.0) {
                        bufferreadsample_result = 0.0;
                    }
    
                    SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        number frac = sampleIndex - truncIndex;
                        number wrap = bufferSize - 1;
    
                        {
                            SampleIndex index1 = (SampleIndex)(truncIndex);
    
                            if (index1 < 0)
                                index1 = wrap;
    
                            SampleIndex index2 = (SampleIndex)(index1 + 1);
    
                            if (index2 > wrap)
                                index2 = 0;
    
                            bufferreadsample_result = this->linearinterp(
                                frac,
                                __buffer->getSample(channelIndex, index1),
                                __buffer->getSample(channelIndex, index2)
                            );
                        }
                    }
                }
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
        }
    
        return out;
    }
    
    template <typename T> inline array<SampleValue, 1 + 1> peek_boundmode_wrap_interp_linear(T& buffer, SampleValue sampleIndex, Index channelOffset) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
        constexpr int ___N2 = 1 + 1;
        array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);
    
        if (bufferSize == 0 || (3 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
            return out;
        } else {
            {
                SampleValue bufferbindindex_result;
    
                {
                    {
                        {
                            bufferbindindex_result = this->wrap(sampleIndex, 0, bufferSize);
                        }
                    }
                }
    
                sampleIndex = bufferbindindex_result;
            }
    
            for (Index channel = 0; channel < 1; channel++) {
                Index channelIndex = (Index)(channel + channelOffset);
    
                {
                    if (channelIndex >= bufferChannels || channelIndex < 0) {
                        out[(Index)channel] = 0;
                        continue;
                    }
                }
    
                SampleValue bufferreadsample_result;
    
                {
                    auto& __buffer = buffer;
    
                    if (sampleIndex < 0.0) {
                        bufferreadsample_result = 0.0;
                    }
    
                    SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        number frac = sampleIndex - truncIndex;
                        number wrap = bufferSize - 1;
    
                        {
                            SampleIndex index1 = (SampleIndex)(truncIndex);
    
                            if (index1 < 0)
                                index1 = wrap;
    
                            SampleIndex index2 = (SampleIndex)(index1 + 1);
    
                            if (index2 > wrap)
                                index2 = 0;
    
                            bufferreadsample_result = this->linearinterp(
                                frac,
                                __buffer->getSample(channelIndex, index1),
                                __buffer->getSample(channelIndex, index2)
                            );
                        }
                    }
                }
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
            return out;
        }
    }
    
    MillisecondTime sampstoms(number samps) {
        return samps * 1000 / this->sr;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->click_01_perform(this->signals[0], n);
    
        this->gen_03_perform(
            this->signals[0],
            this->gen_03_position_min,
            this->gen_03_position_max,
            this->gen_03_grain_size,
            this->gen_03_grain_size_blur,
            this->gen_03_grain_size1,
            this->gen_03_grain_size2,
            this->gen_03_grain_amp_blur,
            this->gen_03_stereo_spread,
            this->gen_03_pitch_spread_ratio,
            this->gen_03_grain_reverse_prob,
            this->gen_03_window_tilt,
            this->gen_03_window_skirt,
            this->gen_03_buf_source_length,
            this->gen_03_pre_delay,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            n
        );
    
        this->signaladder_03_perform(this->signals[1], out1, out1, n);
        this->signaladder_04_perform(this->signals[2], out2, out2, n);
        this->edge_02_perform(this->signals[3], n);
        this->edge_03_perform(this->signals[4], n);
        this->p_02_perform(n);
        this->p_03_perform(n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 5; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->click_01_buf = resizeSignal(this->click_01_buf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->gen_03_dspsetup(forceDSPSetup);
        this->edge_02_dspsetup(forceDSPSetup);
        this->edge_03_dspsetup(forceDSPSetup);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_02->setVoiceIndex(index);
        this->p_03->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_02->setNoteNumber(noteNumber);
        this->p_03->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_02 = new RNBOSubpatcher_22();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_23();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_08_getPresetValue(getSubState(preset, "window_tilt"));
        this->param_09_getPresetValue(getSubState(preset, "window_skirt"));
        this->param_10_getPresetValue(getSubState(preset, "reverse_prob"));
        this->param_11_getPresetValue(getSubState(preset, "amp_blur"));
        this->param_12_getPresetValue(getSubState(preset, "pitch_blur"));
        this->param_13_getPresetValue(getSubState(preset, "stereo_spread"));
        this->param_14_getPresetValue(getSubState(preset, "position1"));
        this->param_15_getPresetValue(getSubState(preset, "position2"));
        this->param_16_getPresetValue(getSubState(preset, "grain_size1"));
        this->param_17_getPresetValue(getSubState(preset, "grain_size2"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "sort_lowHigh[1]"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "sort_lowHigh"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_08_value_set(v);
            break;
            }
        case 1:
            {
            this->param_09_value_set(v);
            break;
            }
        case 2:
            {
            this->param_10_value_set(v);
            break;
            }
        case 3:
            {
            this->param_11_value_set(v);
            break;
            }
        case 4:
            {
            this->param_12_value_set(v);
            break;
            }
        case 5:
            {
            this->param_13_value_set(v);
            break;
            }
        case 6:
            {
            this->param_14_value_set(v);
            break;
            }
        case 7:
            {
            this->param_15_value_set(v);
            break;
            }
        case 8:
            {
            this->param_16_value_set(v);
            break;
            }
        case 9:
            {
            this->param_17_value_set(v);
            break;
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_08_value;
            }
        case 1:
            {
            return this->param_09_value;
            }
        case 2:
            {
            return this->param_10_value;
            }
        case 3:
            {
            return this->param_11_value;
            }
        case 4:
            {
            return this->param_12_value;
            }
        case 5:
            {
            return this->param_13_value;
            }
        case 6:
            {
            return this->param_14_value;
            }
        case 7:
            {
            return this->param_15_value;
            }
        case 8:
            {
            return this->param_16_value;
            }
        case 9:
            {
            return this->param_17_value;
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 2500; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 10 + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "window_tilt";
            }
        case 1:
            {
            return "window_skirt";
            }
        case 2:
            {
            return "reverse_prob";
            }
        case 3:
            {
            return "amp_blur";
            }
        case 4:
            {
            return "pitch_blur";
            }
        case 5:
            {
            return "stereo_spread";
            }
        case 6:
            {
            return "position1";
            }
        case 7:
            {
            return "position2";
            }
        case 8:
            {
            return "grain_size1";
            }
        case 9:
            {
            return "grain_size2";
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "cloud/window_tilt";
            }
        case 1:
            {
            return "cloud/window_skirt";
            }
        case 2:
            {
            return "cloud/reverse_prob";
            }
        case 3:
            {
            return "cloud/amp_blur";
            }
        case 4:
            {
            return "cloud/pitch_blur";
            }
        case 5:
            {
            return "cloud/stereo_spread";
            }
        case 6:
            {
            return "cloud/position1";
            }
        case 7:
            {
            return "cloud/position2";
            }
        case 8:
            {
            return "cloud/grain_size1";
            }
        case 9:
            {
            return "cloud/grain_size2";
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.5;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.5;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1200;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "cent";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 6:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "msec";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 7:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "msec";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 8:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 80;
                info->min = 0.00001;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "msec";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 9:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 80;
                info->min = 0.00001;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "msec";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 10;
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_02)
            return 10;
    
        if (subpatcher == this->p_03)
            return 10 + this->p_02->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 4:
            {
            {
                value = (value < 0 ? 0 : (value > 1200 ? 1200 : value));
                ParameterValue normalizedValue = (value - 0) / (1200 - 0);
                return normalizedValue;
            }
            }
        case 6:
        case 7:
            {
            {
                value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
                ParameterValue normalizedValue = (value - 0) / (5000 - 0);
                return normalizedValue;
            }
            }
        case 8:
        case 9:
            {
            {
                value = (value < 0.00001 ? 0.00001 : (value > 5000 ? 5000 : value));
                ParameterValue normalizedValue = (value - 0.00001) / (5000 - 0.00001);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 4:
            {
            {
                {
                    return 0 + value * (1200 - 0);
                }
            }
            }
        case 6:
        case 7:
            {
            {
                {
                    return 0 + value * (5000 - 0);
                }
            }
            }
        case 8:
        case 9:
            {
            {
                {
                    return 0.00001 + value * (5000 - 0.00001);
                }
            }
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_08_value_constrain(value);
            }
        case 1:
            {
            return this->param_09_value_constrain(value);
            }
        case 2:
            {
            return this->param_10_value_constrain(value);
            }
        case 3:
            {
            return this->param_11_value_constrain(value);
            }
        case 4:
            {
            return this->param_12_value_constrain(value);
            }
        case 5:
            {
            return this->param_13_value_constrain(value);
            }
        case 6:
            {
            return this->param_14_value_constrain(value);
            }
        case 7:
            {
            return this->param_15_value_constrain(value);
            }
        case 8:
            {
            return this->param_16_value_constrain(value);
            }
        case 9:
            {
            return this->param_17_value_constrain(value);
            }
        default:
            {
            index -= 10;
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1313779944:
            {
            this->edge_02_onout_bang();
            break;
            }
        case 1151781846:
            {
            this->edge_02_offout_bang();
            break;
            }
        case -611950441:
            {
            this->edge_03_onout_bang();
            break;
            }
        case -1584063977:
            {
            this->edge_03_offout_bang();
            break;
            }
        case -1735137014:
            {
            this->loadbang_01_startupbang_bang();
            break;
            }
        case -871642103:
            {
            this->loadbang_02_startupbang_bang();
            break;
            }
        case 892732297:
            {
            this->loadmess_01_startupbang_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("startupbang"):
            {
            if (TAG("cloud/loadbang_obj-4") == objectId)
                this->loadbang_01_startupbang_bang();
    
            if (TAG("cloud/loadbang_obj-24") == objectId)
                this->loadbang_02_startupbang_bang();
    
            if (TAG("cloud/loadmess_obj-19") == objectId)
                this->loadmess_01_startupbang_bang();
    
            break;
            }
        }
    
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("cloud/loadbang_obj-4"):
            {
            return "cloud/loadbang_obj-4";
            }
        case TAG("cloud/loadbang_obj-24"):
            {
            return "cloud/loadbang_obj-24";
            }
        case TAG("cloud/loadmess_obj-19"):
            {
            return "cloud/loadmess_obj-19";
            }
        }
    
        auto subpatchResult_0 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 5) {
            this->gen_03_buf_source = new Float64Buffer(this->getPatcher()->source);
            this->dim_01_buffer = new Float64Buffer(this->getPatcher()->source);
            this->dim_01_bufferUpdated();
        }
    
        if (index == 8) {
            this->gen_03_buf_window = new Float64Buffer(this->getPatcher()->window);
        }
    
        if (index == 6) {
            this->gen_03_buf_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        }
    
        if (index == 7) {
            this->gen_03_buf_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    
        if (index == 4) {
            this->gen_03_buf_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        }
    
        if (index == 3) {
            this->gen_03_buf_envelope = new Float64Buffer(this->getPatcher()->envelope);
        }
    
        if (index == 9) {
            this->gen_03_cycle_17_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->gen_03_cycle_19_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        }
    
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->gen_03_buf_source = new Float64Buffer(this->getPatcher()->source);
        this->dim_01_buffer = new Float64Buffer(this->getPatcher()->source);
        this->gen_03_buf_window = new Float64Buffer(this->getPatcher()->window);
        this->gen_03_buf_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        this->gen_03_buf_note_count = new Float64Buffer(this->getPatcher()->note_count);
        this->gen_03_buf_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        this->gen_03_buf_envelope = new Float64Buffer(this->getPatcher()->envelope);
        this->gen_03_cycle_17_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->gen_03_cycle_19_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
    }
    
    protected:
    
    void param_08_value_set(number v) {
        v = this->param_08_value_constrain(v);
        this->param_08_value = v;
        this->sendParameter(0, false);
    
        if (this->param_08_value != this->param_08_lastValue) {
            this->getEngine()->presetTouched();
            this->param_08_lastValue = this->param_08_value;
        }
    
        this->gen_03_window_tilt_set(v);
    }
    
    void param_09_value_set(number v) {
        v = this->param_09_value_constrain(v);
        this->param_09_value = v;
        this->sendParameter(1, false);
    
        if (this->param_09_value != this->param_09_lastValue) {
            this->getEngine()->presetTouched();
            this->param_09_lastValue = this->param_09_value;
        }
    
        this->gen_03_window_skirt_set(v);
    }
    
    void param_10_value_set(number v) {
        v = this->param_10_value_constrain(v);
        this->param_10_value = v;
        this->sendParameter(2, false);
    
        if (this->param_10_value != this->param_10_lastValue) {
            this->getEngine()->presetTouched();
            this->param_10_lastValue = this->param_10_value;
        }
    
        this->gen_03_grain_reverse_prob_set(v);
    }
    
    void param_11_value_set(number v) {
        v = this->param_11_value_constrain(v);
        this->param_11_value = v;
        this->sendParameter(3, false);
    
        if (this->param_11_value != this->param_11_lastValue) {
            this->getEngine()->presetTouched();
            this->param_11_lastValue = this->param_11_value;
        }
    
        this->gen_03_grain_amp_blur_set(v);
    }
    
    void param_12_value_set(number v) {
        v = this->param_12_value_constrain(v);
        this->param_12_value = v;
        this->sendParameter(4, false);
    
        if (this->param_12_value != this->param_12_lastValue) {
            this->getEngine()->presetTouched();
            this->param_12_lastValue = this->param_12_value;
        }
    
        this->expr_03_in1_set(v);
    }
    
    void param_13_value_set(number v) {
        v = this->param_13_value_constrain(v);
        this->param_13_value = v;
        this->sendParameter(5, false);
    
        if (this->param_13_value != this->param_13_lastValue) {
            this->getEngine()->presetTouched();
            this->param_13_lastValue = this->param_13_value;
        }
    
        this->gen_03_stereo_spread_set(v);
    }
    
    void param_14_value_set(number v) {
        v = this->param_14_value_constrain(v);
        this->param_14_value = v;
        this->sendParameter(6, false);
    
        if (this->param_14_value != this->param_14_lastValue) {
            this->getEngine()->presetTouched();
            this->param_14_lastValue = this->param_14_value;
        }
    
        this->p_02_in1_number_set(v);
    }
    
    void param_15_value_set(number v) {
        v = this->param_15_value_constrain(v);
        this->param_15_value = v;
        this->sendParameter(7, false);
    
        if (this->param_15_value != this->param_15_lastValue) {
            this->getEngine()->presetTouched();
            this->param_15_lastValue = this->param_15_value;
        }
    
        this->p_02_in2_number_set(v);
    }
    
    void param_16_value_set(number v) {
        v = this->param_16_value_constrain(v);
        this->param_16_value = v;
        this->sendParameter(8, false);
    
        if (this->param_16_value != this->param_16_lastValue) {
            this->getEngine()->presetTouched();
            this->param_16_lastValue = this->param_16_value;
        }
    
        this->p_03_in1_number_set(v);
    }
    
    void param_17_value_set(number v) {
        v = this->param_17_value_constrain(v);
        this->param_17_value = v;
        this->sendParameter(9, false);
    
        if (this->param_17_value != this->param_17_lastValue) {
            this->getEngine()->presetTouched();
            this->param_17_lastValue = this->param_17_value;
        }
    
        this->p_03_in2_number_set(v);
    }
    
    void eventinlet_06_out1_bang_bang() {
        this->click_01_click_bang_bang();
    }
    
    void eventinlet_06_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->click_01_click_number_set(converted);
        }
    }
    
    void edge_02_onout_bang() {}
    
    void edge_02_offout_bang() {
        this->voice_01_mute_bang_bang();
    }
    
    void edge_03_onout_bang() {
        this->voice_01_mute_bang_bang();
    }
    
    void edge_03_offout_bang() {}
    
    void loadbang_01_startupbang_bang() {
        this->loadbang_01_output_bang();
    }
    
    void loadbang_02_startupbang_bang() {
        this->loadbang_02_output_bang();
    }
    
    void loadmess_01_startupbang_bang() {
        this->loadmess_01_message_bang();
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->gen_03_h_is_scheduled_init();
        this->gen_03_h_grain_amp_init();
        this->gen_03_h_grain_size_init();
        this->gen_03_h_grain_pan_l_init();
        this->gen_03_h_grain_pan_r_init();
        this->gen_03_h_grain_inc_init();
        this->gen_03_h_grain_count_init();
        this->gen_03_h_window_phase_init();
        this->gen_03_h_window_delta_init();
        this->gen_03_h_window_tilt_init();
        this->gen_03_h_window_skirt_init();
        this->gen_03_h_envelope_init();
        this->gen_03_noise_4_init();
        this->gen_03_noise_6_init();
        this->gen_03_noise_9_init();
        this->gen_03_noise_11_init();
        this->gen_03_noise_15_init();
        this->gen_03_noise_16_init();
        this->gen_03_noise_25_init();
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_02->startup();
        this->p_03->startup();
        this->getEngine()->scheduleClockEvent(this, -1735137014, 0 + this->_currentTime);;
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
        this->getEngine()->scheduleClockEvent(this, 892732297, 0 + this->_currentTime);;
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    
        {
            this->scheduleParamInit(2, 0);
        }
    
        {
            this->scheduleParamInit(3, 0);
        }
    
        {
            this->scheduleParamInit(4, 0);
        }
    
        {
            this->scheduleParamInit(5, 0);
        }
    
        {
            this->scheduleParamInit(6, 0);
        }
    
        {
            this->scheduleParamInit(7, 0);
        }
    
        {
            this->scheduleParamInit(8, 0);
        }
    
        {
            this->scheduleParamInit(9, 0);
        }
    }
    
    void allocateDataRefs() {
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->gen_03_cycle_17_buffer->requestSize(16384, 1);
        this->gen_03_cycle_17_buffer->setSampleRate(this->sr);
        this->gen_03_cycle_19_buffer->requestSize(16384, 1);
        this->gen_03_cycle_19_buffer->setSampleRate(this->sr);
        this->gen_03_buf_source = this->gen_03_buf_source->allocateIfNeeded();
        this->dim_01_buffer = this->dim_01_buffer->allocateIfNeeded();
        this->gen_03_buf_window = this->gen_03_buf_window->allocateIfNeeded();
        this->gen_03_buf_notes_state = this->gen_03_buf_notes_state->allocateIfNeeded();
        this->gen_03_buf_note_count = this->gen_03_buf_note_count->allocateIfNeeded();
        this->gen_03_buf_sample_index = this->gen_03_buf_sample_index->allocateIfNeeded();
        this->gen_03_buf_envelope = this->gen_03_buf_envelope->allocateIfNeeded();
        this->gen_03_cycle_17_buffer = this->gen_03_cycle_17_buffer->allocateIfNeeded();
        this->gen_03_cycle_19_buffer = this->gen_03_cycle_19_buffer->allocateIfNeeded();
    }
    
    void voice_01_mutestatus_set(number ) {}
    
    void voice_01_mutein_list_set(const list& v) {
        if (v[0] == this->voice() || v[0] == 0) {
            this->voice_01_mutestatus_set(v[1]);
        }
    }
    
    void voice_01_activevoices_set(number ) {}
    
    void click_01_click_number_set(number v) {
        for (SampleIndex i = (SampleIndex)(this->click_01_lastclick + 1); i < this->sampleOffsetIntoNextAudioBuffer; i++) {
            this->click_01_buf[(Index)i] = 0;
        }
    
        this->click_01_lastclick = this->sampleOffsetIntoNextAudioBuffer;
        this->click_01_buf[(Index)this->click_01_lastclick] = v;
    }
    
    void eventinlet_06_out1_number_set(number v) {
        this->click_01_click_number_set(v);
    }
    
    number param_08_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_window_tilt_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_tilt_set(number v) {
        v = this->gen_03_window_tilt_constrain(v);
        this->gen_03_window_tilt = v;
    }
    
    number param_09_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_window_skirt_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_skirt_set(number v) {
        v = this->gen_03_window_skirt_constrain(v);
        this->gen_03_window_skirt = v;
    }
    
    number param_10_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_grain_reverse_prob_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_grain_reverse_prob_set(number v) {
        v = this->gen_03_grain_reverse_prob_constrain(v);
        this->gen_03_grain_reverse_prob = v;
    }
    
    number param_11_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_grain_amp_blur_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_grain_amp_blur_set(number v) {
        v = this->gen_03_grain_amp_blur_constrain(v);
        this->gen_03_grain_amp_blur = v;
    }
    
    number param_12_value_constrain(number v) const {
        v = (v > 1200 ? 1200 : (v < 0 ? 0 : v));
        return v;
    }
    
    void gen_03_pitch_spread_ratio_set(number v) {
        this->gen_03_pitch_spread_ratio = v;
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->gen_03_pitch_spread_ratio_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(fixnan(rnbo_pow(2, this->expr_03_in1 / (number)1200)));//#map:cloud/expr_obj-20:1
    }
    
    number param_13_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_stereo_spread_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_stereo_spread_set(number v) {
        v = this->gen_03_stereo_spread_constrain(v);
        this->gen_03_stereo_spread = v;
    }
    
    number param_14_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
        return v;
    }
    
    number gen_03_position_max_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_position_max_set(number v) {
        v = this->gen_03_position_max_constrain(v);
        this->gen_03_position_max = v;
    }
    
    void mstosamps_02_out1_set(number v) {
        this->gen_03_position_max_set(v);
    }
    
    void mstosamps_02_ms_set(number ms) {
        this->mstosamps_02_ms = ms;
    
        {
            this->mstosamps_02_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    void p_02_out2_number_set(number v) {
        this->mstosamps_02_ms_set(v);
    }
    
    number gen_03_position_min_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_position_min_set(number v) {
        v = this->gen_03_position_min_constrain(v);
        this->gen_03_position_min = v;
    }
    
    void mstosamps_01_out1_set(number v) {
        this->gen_03_position_min_set(v);
    }
    
    void mstosamps_01_ms_set(number ms) {
        this->mstosamps_01_ms = ms;
    
        {
            this->mstosamps_01_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    void p_02_out1_number_set(number v) {
        this->mstosamps_01_ms_set(v);
    }
    
    void p_02_in1_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_02_out1_number_set(v);
    }
    
    number param_15_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_02_in2_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_03_out1_number_set(v);
    }
    
    number param_16_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0.00001 ? 0.00001 : v));
        return v;
    }
    
    number gen_03_grain_size2_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_grain_size2_set(number v) {
        v = this->gen_03_grain_size2_constrain(v);
        this->gen_03_grain_size2 = v;
    }
    
    void mstosamps_04_out1_set(number v) {
        this->gen_03_grain_size2_set(v);
    }
    
    void mstosamps_04_ms_set(number ms) {
        this->mstosamps_04_ms = ms;
    
        {
            this->mstosamps_04_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    void p_03_out2_number_set(number v) {
        this->mstosamps_04_ms_set(v);
    }
    
    number gen_03_grain_size1_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_grain_size1_set(number v) {
        v = this->gen_03_grain_size1_constrain(v);
        this->gen_03_grain_size1 = v;
    }
    
    void mstosamps_03_out1_set(number v) {
        this->gen_03_grain_size1_set(v);
    }
    
    void mstosamps_03_ms_set(number ms) {
        this->mstosamps_03_ms = ms;
    
        {
            this->mstosamps_03_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    void p_03_out1_number_set(number v) {
        this->mstosamps_03_ms_set(v);
    }
    
    void p_03_in1_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->eventinlet_04_out1_number_set(v);
    }
    
    number param_17_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0.00001 ? 0.00001 : v));
        return v;
    }
    
    void p_03_in2_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->eventinlet_05_out1_number_set(v);
    }
    
    void click_01_click_bang_bang() {
        this->click_01_click_number_set(1);
    }
    
    void voice_01_muteout_set(const list& v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_08_mute_set(v);
    }
    
    void voice_01_mute_bang_bang() {
        this->voice_01_muteout_set({this->voice(), 1});
    }
    
    void loadbang_01_output_bang() {
        this->voice_01_mute_bang_bang();
    }
    
    number gen_03_buf_source_length_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_buf_source_length_set(number v) {
        v = this->gen_03_buf_source_length_constrain(v);
        this->gen_03_buf_source_length = v;
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->gen_03_buf_source_length_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
    
        this->expr_04_out1_set(
            (this->expr_04_in2 == 0 ? 0 : (this->expr_04_in2 == 0. ? 0. : this->expr_04_in1 / this->expr_04_in2))
        );//#map:cloud//_obj-28:1
    }
    
    void dim_01_out_set(number v) {
        this->expr_04_in1_set(v);
    }
    
    void dim_01_outms_set(number ) {}
    
    void dim_01_input_bang() {
        auto size = this->dim(this->dim_01_buffer);
        this->dim_01_out_set(size);
        this->dim_01_outms_set(this->sampstoms(size));
    }
    
    void loadbang_02_output_bang() {
        this->dim_01_input_bang();
    }
    
    number gen_03_pre_delay_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_pre_delay_set(number v) {
        v = this->gen_03_pre_delay_constrain(v);
        this->gen_03_pre_delay = v;
    }
    
    void mstosamps_05_out1_set(number v) {
        this->gen_03_pre_delay_set(v);
    }
    
    void mstosamps_05_ms_set(number ms) {
        this->mstosamps_05_ms = ms;
    
        {
            this->mstosamps_05_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    void loadmess_01_message_bang() {
        list v = this->loadmess_01_message;
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->mstosamps_05_ms_set(converted);
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void click_01_perform(SampleValue * out, Index n) {
        auto __click_01_lastclick = this->click_01_lastclick;
    
        for (SampleIndex i = 0; i <= __click_01_lastclick; i++) {
            out[(Index)i] = this->click_01_buf[(Index)i];
        }
    
        for (SampleIndex i = (SampleIndex)(__click_01_lastclick + 1); i < (SampleIndex)(n); i++) {
            out[(Index)i] = 0;
        }
    
        __click_01_lastclick = -1;
        this->click_01_lastclick = __click_01_lastclick;
    }
    
    void gen_03_perform(
        const Sample * in1,
        number position_min,
        number position_max,
        number grain_size,
        number grain_size_blur,
        number grain_size1,
        number grain_size2,
        number grain_amp_blur,
        number stereo_spread,
        number pitch_spread_ratio,
        number grain_reverse_prob,
        number window_tilt,
        number window_skirt,
        number buf_source_length,
        number pre_delay,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        Index n
    ) {
        RNBO_UNUSED(buf_source_length);
        RNBO_UNUSED(grain_size_blur);
        RNBO_UNUSED(grain_size);
        auto __gen_03_h_window_delta_value = this->gen_03_h_window_delta_value;
        auto __gen_03_h_window_phase_value = this->gen_03_h_window_phase_value;
        auto __gen_03_h_window_skirt_value = this->gen_03_h_window_skirt_value;
        auto __gen_03_h_window_tilt_value = this->gen_03_h_window_tilt_value;
        auto __gen_03_h_grain_count_value = this->gen_03_h_grain_count_value;
        auto __gen_03_h_envelope_value = this->gen_03_h_envelope_value;
        auto __gen_03_h_grain_inc_value = this->gen_03_h_grain_inc_value;
        auto __gen_03_h_grain_pan_r_value = this->gen_03_h_grain_pan_r_value;
        auto __gen_03_h_grain_pan_l_value = this->gen_03_h_grain_pan_l_value;
        auto __gen_03_h_grain_size_value = this->gen_03_h_grain_size_value;
        auto __gen_03_h_grain_amp_value = this->gen_03_h_grain_amp_value;
        auto __gen_03_h_is_scheduled_value = this->gen_03_h_is_scheduled_value;
        Index i;
    
        for (i = 0; i < n; i++) {
            number mute_0 = 0;
    
            if (__gen_03_h_is_scheduled_value == 0) {
                number peek_1 = 0;
                number peek_2 = 0;
                auto result_1 = this->peek_default(this->gen_03_buf_note_count, 0, 0);
                peek_2 = result_1[1];
                peek_1 = result_1[0];
    
                if ((bool)(in1[(Index)i]) && peek_1 > 0) {
                    number peek_3 = 0;
                    number peek_4 = 0;
                    auto result_2 = this->peek_default(this->gen_03_buf_note_count, 0, 0);
                    peek_4 = result_2[1];
                    peek_3 = result_2[0];
                    number unipolarNoise_3 = 0;
    
                    {
                        unipolarNoise_3 = (this->gen_03_noise_4_next() + 1) * 0.5;
                    }
    
                    auto note_index_5 = this->intnum(peek_3 * unipolarNoise_3);
                    auto position_offset_7 = this->scale(this->gen_03_noise_6_next(), -1, 1, position_min, position_max, 1);
                    number unipolarNoise_8 = 0;
    
                    {
                        unipolarNoise_8 = (this->gen_03_noise_9_next() + 1) * 0.5;
                    }
    
                    number pitch_spread_10 = unipolarNoise_8 * (pitch_spread_ratio - ((pitch_spread_ratio == 0. ? 0. : (number)1 / pitch_spread_ratio))) + ((pitch_spread_ratio == 0. ? 0. : (number)1 / pitch_spread_ratio));
                    number pan_12 = stereo_spread * this->gen_03_noise_11_next() * 0.125 + 0.125;
                    number peek_5 = 0;
                    number peek_6 = 0;
                    auto result_13 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 1);
                    peek_6 = result_13[1];
                    peek_5 = result_13[0];
                    number unipolarNoise_14 = 0;
    
                    {
                        unipolarNoise_14 = (this->gen_03_noise_15_next() + 1) * 0.5;
                    }
    
                    __gen_03_h_grain_amp_value = (1 - unipolarNoise_14 * grain_amp_blur) * peek_5;
                    __gen_03_h_grain_size_value = this->scale(this->gen_03_noise_16_next(), -1, 1, grain_size1, grain_size2, 1);
                    array<number, 2> result_18 = this->gen_03_cycle_17_next(pan_12, 0);
                    __gen_03_h_grain_pan_l_value = result_18[0];
                    array<number, 2> result_20 = this->gen_03_cycle_19_next(pan_12 + 0.75, 0);
                    __gen_03_h_grain_pan_r_value = result_20[0];
                    number peek_7 = 0;
                    number peek_8 = 0;
                    auto result_21 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 2);
                    peek_8 = result_21[1];
                    peek_7 = result_21[0];
                    __gen_03_h_grain_inc_value = peek_7 * pitch_spread_10;
                    number envelope_index = 0;
                    auto result_22 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 0);
                    envelope_index = result_22[0];
                    auto result_23 = this->peek_default(this->gen_03_buf_envelope, envelope_index, 0);
                    __gen_03_h_envelope_value = result_23[0];
                    number unipolarNoise_24 = 0;
    
                    {
                        unipolarNoise_24 = (this->gen_03_noise_25_next() + 1) * 0.5;
                    }
    
                    if (grain_reverse_prob <= unipolarNoise_24) {
                        number peek_9 = 0;
                        number peek_10 = 0;
                        auto result_26 = this->peek_default(this->gen_03_buf_sample_index, 0, 0);
                        peek_10 = result_26[1];
                        peek_9 = result_26[0];
                        __gen_03_h_grain_count_value = peek_9 + __gen_03_h_grain_size_value * this->minimum(0, 1 - __gen_03_h_grain_inc_value) - position_offset_7 - pre_delay;
                        __gen_03_h_grain_count_value = this->wrap(__gen_03_h_grain_count_value, 0, this->dim(this->gen_03_buf_source));
                    } else {
                        __gen_03_h_grain_inc_value = __gen_03_h_grain_inc_value * -1;
                        number peek_11 = 0;
                        number peek_12 = 0;
                        auto result_27 = this->peek_default(this->gen_03_buf_sample_index, 0, 0);
                        peek_12 = result_27[1];
                        peek_11 = result_27[0];
                        __gen_03_h_grain_count_value = peek_11 - position_offset_7;
                        __gen_03_h_grain_count_value = this->wrap(__gen_03_h_grain_count_value, 0, this->dim(this->gen_03_buf_source));
                    }
    
                    __gen_03_h_window_tilt_value = window_tilt;
                    __gen_03_h_window_skirt_value = window_skirt;
                    __gen_03_h_window_phase_value = 0;
                    __gen_03_h_window_delta_value = (__gen_03_h_grain_size_value == 0. ? 0. : (number)1 / __gen_03_h_grain_size_value);
                    __gen_03_h_is_scheduled_value = 1;
                } else {
                    mute_0 = 1;
                }
            }
    
            number yL_28 = 0;
            number yR_29 = 0;
    
            if (__gen_03_h_is_scheduled_value == 1) {
                number phaseDistortion_30 = 0;
    
                {
                    auto pulse_33 = __gen_03_h_window_skirt_value;
                    auto tilt_32 = __gen_03_h_window_tilt_value;
                    auto x_31 = __gen_03_h_window_phase_value;
                    number y_34 = x_31;
    
                    if (tilt_32 != 0.5) {
                        number phaseDistortionSaw_35 = 0;
    
                        {
                            auto amount_37 = tilt_32;
                            auto x_36 = x_31;
                            number y_38 = 0;
    
                            if (x_36 < amount_37) {
                                y_38 = this->scale(x_36, 0, amount_37, 0, 0.5, 1);
                            } else {
                                y_38 = this->scale(x_36, amount_37, 1, 0.5, 1, 1);
                            }
    
                            phaseDistortionSaw_35 = y_38;
                        }
    
                        y_34 = phaseDistortionSaw_35;
                    }
    
                    if (pulse_33 != 0.5) {
                        number phaseDistortionPulse_39 = 0;
    
                        {
                            auto amount_41 = 1 - pulse_33 * 2;
                            auto x_40 = y_34;
                            number a_42 = ((amount_41 > 0.999999999 ? 0.999999999 : (amount_41 < 0 ? 0 : amount_41))) * 0.5;
                            number y_43 = 0;
    
                            if (x_40 < a_42) {
                                y_43 = 0;
                            } else if (1 - a_42 < x_40) {
                                y_43 = 1;
                            } else {
                                y_43 = this->scale(x_40, a_42, 1 - a_42, 0, 1, 1);
                            }
    
                            phaseDistortionPulse_39 = y_43;
                        }
    
                        number phaseDistortionSquare_44 = 0;
    
                        {
                            auto amount_46 = (pulse_33 - 0.5) * 2;
                            auto x_45 = y_34;
                            number y_47 = 0;
                            number tmp_48 = (1 - ((amount_46 > 0.999999999 ? 0.999999999 : (amount_46 < 0 ? 0 : amount_46)))) * 0.5;
    
                            if (x_45 < tmp_48) {
                                y_47 = this->scale(x_45, 0, tmp_48, 0, 0.5, 1);
                            } else if (x_45 > 1 - tmp_48) {
                                y_47 = this->scale(x_45, 1 - tmp_48, 1, 0.5, 1, 1);
                            } else {
                                y_47 = 0.5;
                            }
    
                            phaseDistortionSquare_44 = y_47;
                        }
    
                        y_34 = (pulse_33 < 0.5 ? phaseDistortionPulse_39 : phaseDistortionSquare_44);
                    }
    
                    phaseDistortion_30 = y_34;
                }
    
                number p_49 = phaseDistortion_30;
                number w = 0;
                auto result_50 = this->sample_default(this->gen_03_buf_window, p_49, 0);
                w = result_50[0];
                number peek_13 = 0;
                number peek_14 = 0;
                auto result_51 = this->peek_boundmode_wrap_interp_linear(this->gen_03_buf_source, __gen_03_h_grain_count_value, 0);
                peek_14 = result_51[1];
                peek_13 = result_51[0];
                yL_28 = peek_13 * __gen_03_h_grain_amp_value * __gen_03_h_grain_pan_l_value * w * __gen_03_h_envelope_value;
                number peek_15 = 0;
                number peek_16 = 0;
                auto result_52 = this->peek_boundmode_wrap_interp_linear(this->gen_03_buf_source, __gen_03_h_grain_count_value, 1);
                peek_16 = result_52[1];
                peek_15 = result_52[0];
                yR_29 = peek_15 * __gen_03_h_grain_amp_value * __gen_03_h_grain_pan_r_value * w * __gen_03_h_envelope_value;
                __gen_03_h_window_phase_value = __gen_03_h_window_phase_value + __gen_03_h_window_delta_value;
                __gen_03_h_grain_count_value = __gen_03_h_grain_count_value + __gen_03_h_grain_inc_value;
    
                if (__gen_03_h_window_phase_value >= 1) {
                    __gen_03_h_is_scheduled_value = 0;
                }
            }
    
            number expr_17_53 = yL_28;
            number expr_18_54 = yR_29;
            number expr_19_55 = __gen_03_h_is_scheduled_value;
            number expr_20_56 = mute_0;
            out3[(Index)i] = expr_19_55;
            out1[(Index)i] = expr_17_53;
            out4[(Index)i] = expr_20_56;
            out2[(Index)i] = expr_18_54;
        }
    
        this->gen_03_h_is_scheduled_value = __gen_03_h_is_scheduled_value;
        this->gen_03_h_grain_amp_value = __gen_03_h_grain_amp_value;
        this->gen_03_h_grain_size_value = __gen_03_h_grain_size_value;
        this->gen_03_h_grain_pan_l_value = __gen_03_h_grain_pan_l_value;
        this->gen_03_h_grain_pan_r_value = __gen_03_h_grain_pan_r_value;
        this->gen_03_h_grain_inc_value = __gen_03_h_grain_inc_value;
        this->gen_03_h_envelope_value = __gen_03_h_envelope_value;
        this->gen_03_h_grain_count_value = __gen_03_h_grain_count_value;
        this->gen_03_h_window_tilt_value = __gen_03_h_window_tilt_value;
        this->gen_03_h_window_skirt_value = __gen_03_h_window_skirt_value;
        this->gen_03_h_window_phase_value = __gen_03_h_window_phase_value;
        this->gen_03_h_window_delta_value = __gen_03_h_window_delta_value;
    }
    
    void signaladder_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_04_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void edge_02_perform(const SampleValue * input, Index n) {
        auto __edge_02_currentState = this->edge_02_currentState;
    
        for (Index i = 0; i < n; i++) {
            if (__edge_02_currentState == 1) {
                if (input[(Index)i] == 0.) {
                    this->getEngine()->scheduleClockEvent(this, 1151781846, this->sampsToMs(i) + this->_currentTime);;
                    __edge_02_currentState = 0;
                }
            } else {
                if (input[(Index)i] != 0.) {
                    this->getEngine()->scheduleClockEvent(this, -1313779944, this->sampsToMs(i) + this->_currentTime);;
                    __edge_02_currentState = 1;
                }
            }
        }
    
        this->edge_02_currentState = __edge_02_currentState;
    }
    
    void edge_03_perform(const SampleValue * input, Index n) {
        auto __edge_03_currentState = this->edge_03_currentState;
    
        for (Index i = 0; i < n; i++) {
            if (__edge_03_currentState == 1) {
                if (input[(Index)i] == 0.) {
                    this->getEngine()->scheduleClockEvent(this, -1584063977, this->sampsToMs(i) + this->_currentTime);;
                    __edge_03_currentState = 0;
                }
            } else {
                if (input[(Index)i] != 0.) {
                    this->getEngine()->scheduleClockEvent(this, -611950441, this->sampsToMs(i) + this->_currentTime);;
                    __edge_03_currentState = 1;
                }
            }
        }
    
        this->edge_03_currentState = __edge_03_currentState;
    }
    
    void p_02_perform(Index n) {
        // subpatcher: sort_lowHigh
        this->p_02->process(nullptr, 0, nullptr, 0, n);
    }
    
    void p_03_perform(Index n) {
        // subpatcher: sort_lowHigh
        this->p_03->process(nullptr, 0, nullptr, 0, n);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number gen_03_h_is_scheduled_getvalue() {
        return this->gen_03_h_is_scheduled_value;
    }
    
    void gen_03_h_is_scheduled_setvalue(number val) {
        this->gen_03_h_is_scheduled_value = val;
    }
    
    void gen_03_h_is_scheduled_reset() {
        this->gen_03_h_is_scheduled_value = 0;
    }
    
    void gen_03_h_is_scheduled_init() {
        this->gen_03_h_is_scheduled_value = 0;
    }
    
    number gen_03_h_grain_amp_getvalue() {
        return this->gen_03_h_grain_amp_value;
    }
    
    void gen_03_h_grain_amp_setvalue(number val) {
        this->gen_03_h_grain_amp_value = val;
    }
    
    void gen_03_h_grain_amp_reset() {
        this->gen_03_h_grain_amp_value = 0;
    }
    
    void gen_03_h_grain_amp_init() {
        this->gen_03_h_grain_amp_value = 0;
    }
    
    number gen_03_h_grain_size_getvalue() {
        return this->gen_03_h_grain_size_value;
    }
    
    void gen_03_h_grain_size_setvalue(number val) {
        this->gen_03_h_grain_size_value = val;
    }
    
    void gen_03_h_grain_size_reset() {
        this->gen_03_h_grain_size_value = 0;
    }
    
    void gen_03_h_grain_size_init() {
        this->gen_03_h_grain_size_value = 0;
    }
    
    number gen_03_h_grain_pan_l_getvalue() {
        return this->gen_03_h_grain_pan_l_value;
    }
    
    void gen_03_h_grain_pan_l_setvalue(number val) {
        this->gen_03_h_grain_pan_l_value = val;
    }
    
    void gen_03_h_grain_pan_l_reset() {
        this->gen_03_h_grain_pan_l_value = 0;
    }
    
    void gen_03_h_grain_pan_l_init() {
        this->gen_03_h_grain_pan_l_value = 0;
    }
    
    number gen_03_h_grain_pan_r_getvalue() {
        return this->gen_03_h_grain_pan_r_value;
    }
    
    void gen_03_h_grain_pan_r_setvalue(number val) {
        this->gen_03_h_grain_pan_r_value = val;
    }
    
    void gen_03_h_grain_pan_r_reset() {
        this->gen_03_h_grain_pan_r_value = 0;
    }
    
    void gen_03_h_grain_pan_r_init() {
        this->gen_03_h_grain_pan_r_value = 0;
    }
    
    number gen_03_h_grain_inc_getvalue() {
        return this->gen_03_h_grain_inc_value;
    }
    
    void gen_03_h_grain_inc_setvalue(number val) {
        this->gen_03_h_grain_inc_value = val;
    }
    
    void gen_03_h_grain_inc_reset() {
        this->gen_03_h_grain_inc_value = 0;
    }
    
    void gen_03_h_grain_inc_init() {
        this->gen_03_h_grain_inc_value = 0;
    }
    
    number gen_03_h_grain_count_getvalue() {
        return this->gen_03_h_grain_count_value;
    }
    
    void gen_03_h_grain_count_setvalue(number val) {
        this->gen_03_h_grain_count_value = val;
    }
    
    void gen_03_h_grain_count_reset() {
        this->gen_03_h_grain_count_value = 0;
    }
    
    void gen_03_h_grain_count_init() {
        this->gen_03_h_grain_count_value = 0;
    }
    
    number gen_03_h_window_phase_getvalue() {
        return this->gen_03_h_window_phase_value;
    }
    
    void gen_03_h_window_phase_setvalue(number val) {
        this->gen_03_h_window_phase_value = val;
    }
    
    void gen_03_h_window_phase_reset() {
        this->gen_03_h_window_phase_value = 0;
    }
    
    void gen_03_h_window_phase_init() {
        this->gen_03_h_window_phase_value = 0;
    }
    
    number gen_03_h_window_delta_getvalue() {
        return this->gen_03_h_window_delta_value;
    }
    
    void gen_03_h_window_delta_setvalue(number val) {
        this->gen_03_h_window_delta_value = val;
    }
    
    void gen_03_h_window_delta_reset() {
        this->gen_03_h_window_delta_value = 0;
    }
    
    void gen_03_h_window_delta_init() {
        this->gen_03_h_window_delta_value = 0;
    }
    
    number gen_03_h_window_tilt_getvalue() {
        return this->gen_03_h_window_tilt_value;
    }
    
    void gen_03_h_window_tilt_setvalue(number val) {
        this->gen_03_h_window_tilt_value = val;
    }
    
    void gen_03_h_window_tilt_reset() {
        this->gen_03_h_window_tilt_value = 0;
    }
    
    void gen_03_h_window_tilt_init() {
        this->gen_03_h_window_tilt_value = 0;
    }
    
    number gen_03_h_window_skirt_getvalue() {
        return this->gen_03_h_window_skirt_value;
    }
    
    void gen_03_h_window_skirt_setvalue(number val) {
        this->gen_03_h_window_skirt_value = val;
    }
    
    void gen_03_h_window_skirt_reset() {
        this->gen_03_h_window_skirt_value = 0;
    }
    
    void gen_03_h_window_skirt_init() {
        this->gen_03_h_window_skirt_value = 0;
    }
    
    number gen_03_h_envelope_getvalue() {
        return this->gen_03_h_envelope_value;
    }
    
    void gen_03_h_envelope_setvalue(number val) {
        this->gen_03_h_envelope_value = val;
    }
    
    void gen_03_h_envelope_reset() {
        this->gen_03_h_envelope_value = 0;
    }
    
    void gen_03_h_envelope_init() {
        this->gen_03_h_envelope_value = 0;
    }
    
    void gen_03_noise_4_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_4_state
        );
    }
    
    void gen_03_noise_4_init() {
        this->gen_03_noise_4_reset();
    }
    
    void gen_03_noise_4_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_4_state);
    }
    
    number gen_03_noise_4_next() {
        return xoshiro_next(this->gen_03_noise_4_state);
    }
    
    void gen_03_noise_6_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_6_state
        );
    }
    
    void gen_03_noise_6_init() {
        this->gen_03_noise_6_reset();
    }
    
    void gen_03_noise_6_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_6_state);
    }
    
    number gen_03_noise_6_next() {
        return xoshiro_next(this->gen_03_noise_6_state);
    }
    
    void gen_03_noise_9_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_9_state
        );
    }
    
    void gen_03_noise_9_init() {
        this->gen_03_noise_9_reset();
    }
    
    void gen_03_noise_9_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_9_state);
    }
    
    number gen_03_noise_9_next() {
        return xoshiro_next(this->gen_03_noise_9_state);
    }
    
    void gen_03_noise_11_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_11_state
        );
    }
    
    void gen_03_noise_11_init() {
        this->gen_03_noise_11_reset();
    }
    
    void gen_03_noise_11_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_11_state);
    }
    
    number gen_03_noise_11_next() {
        return xoshiro_next(this->gen_03_noise_11_state);
    }
    
    void gen_03_noise_15_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_15_state
        );
    }
    
    void gen_03_noise_15_init() {
        this->gen_03_noise_15_reset();
    }
    
    void gen_03_noise_15_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_15_state);
    }
    
    number gen_03_noise_15_next() {
        return xoshiro_next(this->gen_03_noise_15_state);
    }
    
    void gen_03_noise_16_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_16_state
        );
    }
    
    void gen_03_noise_16_init() {
        this->gen_03_noise_16_reset();
    }
    
    void gen_03_noise_16_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_16_state);
    }
    
    number gen_03_noise_16_next() {
        return xoshiro_next(this->gen_03_noise_16_state);
    }
    
    number gen_03_cycle_17_ph_next(number freq, number reset) {
        RNBO_UNUSED(reset);
    
        {
            {}
        }
    
        number pincr = freq * this->gen_03_cycle_17_ph_conv;
    
        if (this->gen_03_cycle_17_ph_currentPhase < 0.)
            this->gen_03_cycle_17_ph_currentPhase = 1. + this->gen_03_cycle_17_ph_currentPhase;
    
        if (this->gen_03_cycle_17_ph_currentPhase > 1.)
            this->gen_03_cycle_17_ph_currentPhase = this->gen_03_cycle_17_ph_currentPhase - 1.;
    
        number tmp = this->gen_03_cycle_17_ph_currentPhase;
        this->gen_03_cycle_17_ph_currentPhase += pincr;
        return tmp;
    }
    
    void gen_03_cycle_17_ph_reset() {
        this->gen_03_cycle_17_ph_currentPhase = 0;
    }
    
    void gen_03_cycle_17_ph_dspsetup() {
        this->gen_03_cycle_17_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    array<number, 2> gen_03_cycle_17_next(number frequency, number phase_offset) {
        RNBO_UNUSED(phase_offset);
    
        {
            uint32_t uint_phase;
    
            {
                uint_phase = uint32_trunc(frequency * 4294967296.0);
            }
    
            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = this->gen_03_cycle_17_buffer[(Index)idx];
            number y1 = this->gen_03_cycle_17_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);
            return {y, uint_phase * 0.232830643653869629e-9};
        }
    }
    
    void gen_03_cycle_17_dspsetup() {
        this->gen_03_cycle_17_phasei = 0;
        this->gen_03_cycle_17_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
        this->gen_03_cycle_17_wrap = (long)(this->gen_03_cycle_17_buffer->getSize()) - 1;
    }
    
    void gen_03_cycle_17_reset() {
        this->gen_03_cycle_17_phasei = 0;
    }
    
    void gen_03_cycle_17_bufferUpdated() {
        this->gen_03_cycle_17_wrap = (long)(this->gen_03_cycle_17_buffer->getSize()) - 1;
    }
    
    number gen_03_cycle_19_ph_next(number freq, number reset) {
        RNBO_UNUSED(reset);
    
        {
            {}
        }
    
        number pincr = freq * this->gen_03_cycle_19_ph_conv;
    
        if (this->gen_03_cycle_19_ph_currentPhase < 0.)
            this->gen_03_cycle_19_ph_currentPhase = 1. + this->gen_03_cycle_19_ph_currentPhase;
    
        if (this->gen_03_cycle_19_ph_currentPhase > 1.)
            this->gen_03_cycle_19_ph_currentPhase = this->gen_03_cycle_19_ph_currentPhase - 1.;
    
        number tmp = this->gen_03_cycle_19_ph_currentPhase;
        this->gen_03_cycle_19_ph_currentPhase += pincr;
        return tmp;
    }
    
    void gen_03_cycle_19_ph_reset() {
        this->gen_03_cycle_19_ph_currentPhase = 0;
    }
    
    void gen_03_cycle_19_ph_dspsetup() {
        this->gen_03_cycle_19_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    array<number, 2> gen_03_cycle_19_next(number frequency, number phase_offset) {
        RNBO_UNUSED(phase_offset);
    
        {
            uint32_t uint_phase;
    
            {
                uint_phase = uint32_trunc(frequency * 4294967296.0);
            }
    
            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = this->gen_03_cycle_19_buffer[(Index)idx];
            number y1 = this->gen_03_cycle_19_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);
            return {y, uint_phase * 0.232830643653869629e-9};
        }
    }
    
    void gen_03_cycle_19_dspsetup() {
        this->gen_03_cycle_19_phasei = 0;
        this->gen_03_cycle_19_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
        this->gen_03_cycle_19_wrap = (long)(this->gen_03_cycle_19_buffer->getSize()) - 1;
    }
    
    void gen_03_cycle_19_reset() {
        this->gen_03_cycle_19_phasei = 0;
    }
    
    void gen_03_cycle_19_bufferUpdated() {
        this->gen_03_cycle_19_wrap = (long)(this->gen_03_cycle_19_buffer->getSize()) - 1;
    }
    
    void gen_03_noise_25_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_25_state
        );
    }
    
    void gen_03_noise_25_init() {
        this->gen_03_noise_25_reset();
    }
    
    void gen_03_noise_25_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_25_state);
    }
    
    number gen_03_noise_25_next() {
        return xoshiro_next(this->gen_03_noise_25_state);
    }
    
    void gen_03_dspsetup(bool force) {
        if ((bool)(this->gen_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->gen_03_setupDone = true;
        this->gen_03_cycle_17_ph_dspsetup();
        this->gen_03_cycle_17_dspsetup();
        this->gen_03_cycle_19_ph_dspsetup();
        this->gen_03_cycle_19_dspsetup();
    }
    
    void edge_02_dspsetup(bool force) {
        if ((bool)(this->edge_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->edge_02_setupDone = true;
    }
    
    void param_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_08_value;
    }
    
    void param_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_08_value_set(preset["value"]);
    }
    
    void param_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_09_value;
    }
    
    void param_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_09_value_set(preset["value"]);
    }
    
    void param_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_10_value;
    }
    
    void param_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_10_value_set(preset["value"]);
    }
    
    void edge_03_dspsetup(bool force) {
        if ((bool)(this->edge_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->edge_03_setupDone = true;
    }
    
    void param_11_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_11_value;
    }
    
    void param_11_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_11_value_set(preset["value"]);
    }
    
    void param_12_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_12_value;
    }
    
    void param_12_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_12_value_set(preset["value"]);
    }
    
    void param_13_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_13_value;
    }
    
    void param_13_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_13_value_set(preset["value"]);
    }
    
    void param_14_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_14_value;
    }
    
    void param_14_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_14_value_set(preset["value"]);
    }
    
    void param_15_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_15_value;
    }
    
    void param_15_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_15_value_set(preset["value"]);
    }
    
    void param_16_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_16_value;
    }
    
    void param_16_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_16_value_set(preset["value"]);
    }
    
    void param_17_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_17_value;
    }
    
    void param_17_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_17_value_set(preset["value"]);
    }
    
    void dim_01_bufferUpdated() {
        auto size = this->dim(this->dim_01_buffer);
        this->dim_01_out_set(size);
        this->dim_01_outms_set(this->sampstoms(size));
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        gen_03_in1 = 0;
        gen_03_position_min = 0;
        gen_03_position_max = 0;
        gen_03_grain_size = 480;
        gen_03_grain_size_blur = 0;
        gen_03_grain_size1 = 0;
        gen_03_grain_size2 = 0;
        gen_03_grain_amp_blur = 0;
        gen_03_stereo_spread = 0;
        gen_03_pitch_spread_ratio = 1;
        gen_03_grain_reverse_prob = 0;
        gen_03_window_tilt = 0.5;
        gen_03_window_skirt = 0.5;
        gen_03_buf_source_length = 0;
        gen_03_pre_delay = 0;
        param_08_value = 0.5;
        param_09_value = 0.5;
        param_10_value = 0;
        voice_01_mute_number = 0;
        param_11_value = 0;
        expr_03_in1 = 0;
        expr_03_out1 = 0;
        param_12_value = 0;
        param_13_value = 0;
        mstosamps_01_ms = 0;
        p_02_target = 0;
        param_14_value = 0;
        mstosamps_02_ms = 0;
        param_15_value = 0;
        mstosamps_03_ms = 0;
        p_03_target = 0;
        param_16_value = 80;
        mstosamps_04_ms = 0;
        param_17_value = 80;
        expr_04_in1 = 0;
        expr_04_in2 = 128;
        expr_04_out1 = 0;
        loadmess_01_message = { 15 };
        mstosamps_05_ms = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        gen_03_h_is_scheduled_value = 0;
        gen_03_h_grain_amp_value = 0;
        gen_03_h_grain_size_value = 0;
        gen_03_h_grain_pan_l_value = 0;
        gen_03_h_grain_pan_r_value = 0;
        gen_03_h_grain_inc_value = 0;
        gen_03_h_grain_count_value = 0;
        gen_03_h_window_phase_value = 0;
        gen_03_h_window_delta_value = 0;
        gen_03_h_window_tilt_value = 0;
        gen_03_h_window_skirt_value = 0;
        gen_03_h_envelope_value = 0;
        gen_03_cycle_17_ph_currentPhase = 0;
        gen_03_cycle_17_ph_conv = 0;
        gen_03_cycle_17_wrap = 0;
        gen_03_cycle_19_ph_currentPhase = 0;
        gen_03_cycle_19_ph_conv = 0;
        gen_03_cycle_19_wrap = 0;
        gen_03_setupDone = false;
        click_01_lastclick = -1;
        click_01_buf = nullptr;
        edge_02_setupDone = false;
        param_08_lastValue = 0;
        param_09_lastValue = 0;
        param_10_lastValue = 0;
        edge_03_setupDone = false;
        param_11_lastValue = 0;
        param_12_lastValue = 0;
        param_13_lastValue = 0;
        param_14_lastValue = 0;
        param_15_lastValue = 0;
        param_16_lastValue = 0;
        param_17_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number gen_03_in1;
        number gen_03_position_min;
        number gen_03_position_max;
        number gen_03_grain_size;
        number gen_03_grain_size_blur;
        number gen_03_grain_size1;
        number gen_03_grain_size2;
        number gen_03_grain_amp_blur;
        number gen_03_stereo_spread;
        number gen_03_pitch_spread_ratio;
        number gen_03_grain_reverse_prob;
        number gen_03_window_tilt;
        number gen_03_window_skirt;
        number gen_03_buf_source_length;
        number gen_03_pre_delay;
        number param_08_value;
        number param_09_value;
        number param_10_value;
        number voice_01_mute_number;
        number param_11_value;
        number expr_03_in1;
        number expr_03_out1;
        number param_12_value;
        number param_13_value;
        number mstosamps_01_ms;
        number p_02_target;
        number param_14_value;
        number mstosamps_02_ms;
        number param_15_value;
        number mstosamps_03_ms;
        number p_03_target;
        number param_16_value;
        number mstosamps_04_ms;
        number param_17_value;
        number expr_04_in1;
        number expr_04_in2;
        number expr_04_out1;
        list loadmess_01_message;
        number mstosamps_05_ms;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[5];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float64BufferRef gen_03_buf_source;
        Float64BufferRef gen_03_buf_window;
        Float64BufferRef gen_03_buf_notes_state;
        Float64BufferRef gen_03_buf_note_count;
        Float64BufferRef gen_03_buf_sample_index;
        Float64BufferRef gen_03_buf_envelope;
        number gen_03_h_is_scheduled_value;
        number gen_03_h_grain_amp_value;
        number gen_03_h_grain_size_value;
        number gen_03_h_grain_pan_l_value;
        number gen_03_h_grain_pan_r_value;
        number gen_03_h_grain_inc_value;
        number gen_03_h_grain_count_value;
        number gen_03_h_window_phase_value;
        number gen_03_h_window_delta_value;
        number gen_03_h_window_tilt_value;
        number gen_03_h_window_skirt_value;
        number gen_03_h_envelope_value;
        UInt gen_03_noise_4_state[4] = { };
        UInt gen_03_noise_6_state[4] = { };
        UInt gen_03_noise_9_state[4] = { };
        UInt gen_03_noise_11_state[4] = { };
        UInt gen_03_noise_15_state[4] = { };
        UInt gen_03_noise_16_state[4] = { };
        number gen_03_cycle_17_ph_currentPhase;
        number gen_03_cycle_17_ph_conv;
        Float64BufferRef gen_03_cycle_17_buffer;
        long gen_03_cycle_17_wrap;
        uint32_t gen_03_cycle_17_phasei;
        SampleValue gen_03_cycle_17_f2i;
        number gen_03_cycle_19_ph_currentPhase;
        number gen_03_cycle_19_ph_conv;
        Float64BufferRef gen_03_cycle_19_buffer;
        long gen_03_cycle_19_wrap;
        uint32_t gen_03_cycle_19_phasei;
        SampleValue gen_03_cycle_19_f2i;
        UInt gen_03_noise_25_state[4] = { };
        bool gen_03_setupDone;
        SampleIndex click_01_lastclick;
        signal click_01_buf;
        number edge_02_currentState;
        bool edge_02_setupDone;
        number param_08_lastValue;
        number param_09_lastValue;
        number param_10_lastValue;
        number edge_03_currentState;
        bool edge_03_setupDone;
        number param_11_lastValue;
        number param_12_lastValue;
        number param_13_lastValue;
        number param_14_lastValue;
        number param_15_lastValue;
        number param_16_lastValue;
        number param_17_lastValue;
        Float64BufferRef dim_01_buffer;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_22* p_02;
        RNBOSubpatcher_23* p_03;
    
};

class RNBOSubpatcher_29 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_29()
    {
    }
    
    ~RNBOSubpatcher_29()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -871642103, false);
        getEngine()->flushClockEvents(this, 1821745152, false);
        getEngine()->flushClockEvents(this, -1468824490, false);
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        long numWraps = (long)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    template <typename T> inline void poke_default(
        T& buffer,
        SampleValue value,
        SampleValue sampleIndex,
        int channel,
        number overdub
    ) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
    
        if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
            if (overdub != 0) {
                number currentValue = buffer->getSample(channel, sampleIndex);
    
                {
                    value = value + currentValue * overdub;
                }
            }
    
            buffer->setSample(channel, sampleIndex, value);
            buffer->setTouched(true);
        }
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    int notenumber() {
        return this->_noteNumber;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numOutputs);
        RNBO_UNUSED(outputs);
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
    
        if (this->getIsMuted())
            return;
    
        this->adsr_01_perform(
            this->adsr_01_attack,
            this->adsr_01_decay,
            this->adsr_01_sustain,
            this->adsr_01_release,
            this->zeroBuffer,
            this->signals[0],
            n
        );
    
        this->dspexpr_08_perform(this->signals[0], this->signals[0], this->signals[1], n);
    
        this->poke_tilde_01_perform(
            this->poke_tilde_01_index,
            this->poke_tilde_01_channel,
            this->poke_tilde_01_overdub,
            this->signals[1],
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
            this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->adsr_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_18_getPresetValue(getSubState(preset, "attack"));
        this->param_19_getPresetValue(getSubState(preset, "release"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_18_value_set(v);
            break;
            }
        case 1:
            {
            this->param_19_value_set(v);
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_18_value;
            }
        case 1:
            {
            return this->param_19_value;
            }
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 128; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 2;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "attack";
            }
        case 1:
            {
            return "release";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "envelope/attack";
            }
        case 1:
            {
            return "envelope/release";
            }
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 5000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
                ParameterValue normalizedValue = (value - 0) / (5000 - 0);
                return normalizedValue;
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
        case 1:
            {
            {
                {
                    return 0 + value * (5000 - 0);
                }
            }
            }
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_18_value_constrain(value);
            }
        case 1:
            {
            return this->param_19_value_constrain(value);
            }
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -871642103:
            {
            this->loadbang_03_startupbang_bang();
            break;
            }
        case 1821745152:
            {
            this->codebox_03_in1_bang();
            break;
            }
        case -1468824490:
            {
            this->adsr_01_mute_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("startupbang"):
            {
            if (TAG("envelope/loadbang_obj-10") == objectId)
                this->loadbang_03_startupbang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("envelope/loadbang_obj-10"):
            {
            return "envelope/loadbang_obj-10";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 3) {
            this->poke_tilde_01_buffer = new Float64Buffer(this->getPatcher()->envelope);
        }
    
        if (index == 6) {
            this->codebox_03_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        }
    
        if (index == 7) {
            this->codebox_03_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    
        if (index == 2) {
            this->codebox_03_note_on_check = new Float64Buffer(this->getPatcher()->note_on_check);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->poke_tilde_01_buffer = new Float64Buffer(this->getPatcher()->envelope);
        this->codebox_03_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        this->codebox_03_note_count = new Float64Buffer(this->getPatcher()->note_count);
        this->codebox_03_note_on_check = new Float64Buffer(this->getPatcher()->note_on_check);
    }
    
    protected:
    
    void param_18_value_set(number v) {
        v = this->param_18_value_constrain(v);
        this->param_18_value = v;
        this->sendParameter(0, false);
    
        if (this->param_18_value != this->param_18_lastValue) {
            this->getEngine()->presetTouched();
            this->param_18_lastValue = this->param_18_value;
        }
    
        this->adsr_01_attack_set(v);
    }
    
    void param_19_value_set(number v) {
        v = this->param_19_value_constrain(v);
        this->param_19_value = v;
        this->sendParameter(1, false);
    
        if (this->param_19_value != this->param_19_lastValue) {
            this->getEngine()->presetTouched();
            this->param_19_lastValue = this->param_19_value;
        }
    
        this->adsr_01_release_set(v);
    }
    
    void eventinlet_07_out1_bang_bang() {}
    
    void eventinlet_07_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->adsr_01_trigger_number_set(converted);
        }
    }
    
    void loadbang_03_startupbang_bang() {
        this->loadbang_03_output_bang();
    }
    
    void codebox_03_in1_bang() {
        number is_note_on = this->codebox_03_note_on_check->getSampleSafe(0, this->codebox_03_pitch);
    
        if (this->codebox_03_note_count->getSampleSafe(0, 0) > 0 && (bool)(is_note_on)) {
            this->poke_default(this->codebox_03_note_on_check, 0, this->codebox_03_pitch, 0, 0);//#map:_###_obj_###_:12
            number index_to_erase = 0;
            number index_last_elm = this->codebox_03_note_count->getSampleSafe(0, 0) - 1;
    
            while (index_to_erase != index_last_elm) {
                if (this->codebox_03_notes_state->getSampleSafe(0, index_to_erase) == this->codebox_03_pitch)
                    break;//#map:_###_obj_###_:20;//#map:_###_obj_###_:20
    
                index_to_erase += 1;//#map:_###_obj_###_:21
            }
    
            while (index_to_erase != index_last_elm) {
                number right_index = index_to_erase + 1;
                number right_pitch = this->codebox_03_notes_state->getSampleSafe(0, right_index);
                number right_level = this->codebox_03_notes_state->getSampleSafe(1, right_index);
                number right_ratio = this->codebox_03_notes_state->getSampleSafe(2, right_index);
                this->poke_default(this->codebox_03_notes_state, right_pitch, index_to_erase, 0, 0);//#map:_###_obj_###_:32
                this->poke_default(this->codebox_03_notes_state, right_level, index_to_erase, 1, 0);//#map:_###_obj_###_:33
                this->poke_default(this->codebox_03_notes_state, right_ratio, index_to_erase, 2, 0);//#map:_###_obj_###_:34
                index_to_erase += 1;//#map:_###_obj_###_:35
            }
    
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 0, 0);//#map:_###_obj_###_:39
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 1, 0);//#map:_###_obj_###_:40
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 2, 0);//#map:_###_obj_###_:41
            this->poke_default(this->codebox_03_note_count, index_last_elm, 0, 0, 0);//#map:_###_obj_###_:44
            this->codebox_03_out1_set(1);//#map:_###_obj_###_:46
        }//#map:envelope/codebox_obj-6:9
    }
    
    void adsr_01_mute_bang() {
        this->codebox_03_in1_bang();
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 0;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
        this->getEngine()->scheduleClockEvent(this, 1821745152, 0 + this->_currentTime);;
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    }
    
    void allocateDataRefs() {
        this->poke_tilde_01_buffer = this->poke_tilde_01_buffer->allocateIfNeeded();
        this->codebox_03_notes_state = this->codebox_03_notes_state->allocateIfNeeded();
        this->codebox_03_note_count = this->codebox_03_note_count->allocateIfNeeded();
        this->codebox_03_note_on_check = this->codebox_03_note_on_check->allocateIfNeeded();
    }
    
    void voice_02_mutestatus_set(number ) {}
    
    void voice_02_mutein_list_set(const list& v) {
        if (v[0] == this->voice() || v[0] == 0) {
            this->voice_02_mutestatus_set(v[1]);
        }
    }
    
    void voice_02_activevoices_set(number ) {}
    
    void adsr_01_trigger_number_set(number v) {
        this->adsr_01_trigger_number = v;
    
        if (v != 0)
            this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
    
        for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
            this->adsr_01_triggerValueBuf[(Index)i] = v;
        }
    }
    
    void eventinlet_07_out1_number_set(number v) {
        this->adsr_01_trigger_number_set(v);
    }
    
    number param_18_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_attack_set(number v) {
        this->adsr_01_attack = v;
    }
    
    number param_19_value_constrain(number v) const {
        v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_release_set(number v) {
        this->adsr_01_release = v;
    }
    
    void voice_02_noteNumber_set(number ) {}
    
    number codebox_03_pitch_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 127)
            v = 127;
    
        return v;
    }
    
    void codebox_03_pitch_set(number v) {
        v = this->codebox_03_pitch_constrain(v);
        this->codebox_03_pitch = v;
    }
    
    void trigger_03_out2_set(number v) {
        this->codebox_03_pitch_set(v);
    }
    
    void poke_tilde_01_index_set(number v) {
        this->poke_tilde_01_index = v;
    }
    
    void trigger_03_out1_set(number v) {
        this->poke_tilde_01_index_set(v);
    }
    
    void trigger_03_input_number_set(number v) {
        this->trigger_03_out2_set(trunc(v));
        this->trigger_03_out1_set(trunc(v));
    }
    
    void expr_05_out1_set(number v) {
        this->expr_05_out1 = v;
        this->trigger_03_input_number_set(this->expr_05_out1);
    }
    
    void expr_05_in1_set(number in1) {
        this->expr_05_in1 = in1;
        this->expr_05_out1_set(this->expr_05_in1 - this->expr_05_in2);//#map:envelope/-_obj-11:1
    }
    
    void voice_02_voicenumber_set(number v) {
        this->expr_05_in1_set(v);
    }
    
    void voice_02_voicebang_bang() {
        this->voice_02_noteNumber_set(this->notenumber());
        this->voice_02_voicenumber_set(this->voice());
    }
    
    void loadbang_03_output_bang() {
        this->voice_02_voicebang_bang();
    }
    
    void voice_02_muteout_set(const list& v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_09_mute_set(v);
    }
    
    void voice_02_mute_number_set(number v) {
        this->voice_02_mute_number = v;
        this->voice_02_muteout_set({this->voice(), v});
    }
    
    void codebox_03_out1_set(number v) {
        this->codebox_03_out1 = v;
        this->voice_02_mute_number_set(this->codebox_03_out1);
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void adsr_01_perform(
        number attack,
        number decay,
        number sustain,
        number release,
        const SampleValue * trigger_signal,
        SampleValue * out,
        Index n
    ) {
        RNBO_UNUSED(trigger_signal);
        RNBO_UNUSED(sustain);
        RNBO_UNUSED(decay);
        auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
        auto __adsr_01_time = this->adsr_01_time;
        auto __adsr_01_amplitude = this->adsr_01_amplitude;
        auto __adsr_01_outval = this->adsr_01_outval;
        auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
        auto __adsr_01_phase = this->adsr_01_phase;
        auto __adsr_01_legato = this->adsr_01_legato;
        auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
        auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
        auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
        bool bangMute = false;
    
        for (Index i = 0; i < n; i++) {
            number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
            number clampeddecay = (0 > __adsr_01_mspersamp ? 0 : __adsr_01_mspersamp);
            number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
            number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
            number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];
    
            if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
                if ((bool)(__adsr_01_legato)) {
                    if (__adsr_01_phase != 0) {
                        __adsr_01_startingpoint = __adsr_01_outval;
                    } else {
                        __adsr_01_startingpoint = 0;
                    }
                } else {
                    __adsr_01_startingpoint = 0;
                }
    
                __adsr_01_amplitude = currentTriggerVal;
                __adsr_01_phase = 1;
                __adsr_01_time = 0.0;
                bangMute = false;
            } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                    __adsr_01_time = 0.0;
                }
            }
    
            __adsr_01_time += __adsr_01_mspersamp;
    
            if (__adsr_01_phase == 0) {
                __adsr_01_outval = 0;
            } else if (__adsr_01_phase == 1) {
                if (__adsr_01_time > clampedattack) {
                    __adsr_01_time -= clampedattack;
                    __adsr_01_phase = 2;
                    __adsr_01_outval = __adsr_01_amplitude;
                } else {
                    __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                }
            } else if (__adsr_01_phase == 2) {
                if (__adsr_01_time > clampeddecay) {
                    __adsr_01_time -= clampeddecay;
                    __adsr_01_phase = 3;
                    __adsr_01_outval = __adsr_01_amplitude * 1;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * 1 + (__adsr_01_amplitude - __adsr_01_amplitude * 1) * (1. - __adsr_01_time / clampeddecay);
                }
            } else if (__adsr_01_phase == 3) {
                if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                    __adsr_01_time -= clampedsustain;
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * 1;
                }
            } else if (__adsr_01_phase == 4) {
                if (__adsr_01_time > clampedrelease) {
                    __adsr_01_time = 0;
                    __adsr_01_phase = 0;
                    __adsr_01_outval = 0;
                    __adsr_01_amplitude = 0;
                    bangMute = true;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                }
            }
    
            out[(Index)i] = __adsr_01_outval;
            this->adsr_01_triggerBuf[(Index)i] = 0;
            this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
            __adsr_01_lastTriggerVal = currentTriggerVal;
        }
    
        if ((bool)(bangMute)) {
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1468824490,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                0
            );;
        }
    
        this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
        this->adsr_01_phase = __adsr_01_phase;
        this->adsr_01_startingpoint = __adsr_01_startingpoint;
        this->adsr_01_outval = __adsr_01_outval;
        this->adsr_01_amplitude = __adsr_01_amplitude;
        this->adsr_01_time = __adsr_01_time;
    }
    
    void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void poke_tilde_01_perform(
        number index,
        number channel,
        number overdub,
        const SampleValue * value_signal,
        Index n
    ) {
        RNBO_UNUSED(overdub);
        RNBO_UNUSED(channel);
        auto __poke_tilde_01_buffer = this->poke_tilde_01_buffer;
    
        for (Index i = 0; i < n; i++) {
            this->poke_default(__poke_tilde_01_buffer, value_signal[(Index)i], index, 0, 0);
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void adsr_01_dspsetup(bool force) {
        if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->adsr_01_mspersamp = (number)1000 / this->sr;
        this->adsr_01_setupDone = true;
    }
    
    void param_18_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_18_value;
    }
    
    void param_18_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_18_value_set(preset["value"]);
    }
    
    void param_19_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_19_value;
    }
    
    void param_19_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_19_value_set(preset["value"]);
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_08_in1 = 0;
        dspexpr_08_in2 = 0;
        poke_tilde_01_value_number = 0;
        poke_tilde_01_index = 0;
        poke_tilde_01_channel = 0;
        poke_tilde_01_overdub = 0;
        adsr_01_trigger_number = 0;
        adsr_01_attack = 0;
        adsr_01_decay = 0;
        adsr_01_sustain = 1;
        adsr_01_release = 0;
        adsr_01_legato = 0;
        adsr_01_maxsustain = -1;
        param_18_value = 0;
        expr_05_in1 = 0;
        expr_05_in2 = 1;
        expr_05_out1 = 0;
        voice_02_mute_number = 0;
        codebox_03_out1 = 0;
        codebox_03_pitch = 0;
        param_19_value = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        adsr_01_phase = 3;
        adsr_01_mspersamp = 0;
        adsr_01_time = 0;
        adsr_01_lastTriggerVal = 0;
        adsr_01_amplitude = 0;
        adsr_01_outval = 0;
        adsr_01_startingpoint = 0;
        adsr_01_triggerBuf = nullptr;
        adsr_01_triggerValueBuf = nullptr;
        adsr_01_setupDone = false;
        param_18_lastValue = 0;
        param_19_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_08_in1;
        number dspexpr_08_in2;
        number poke_tilde_01_value_number;
        list poke_tilde_01_value_list;
        number poke_tilde_01_index;
        number poke_tilde_01_channel;
        number poke_tilde_01_overdub;
        number adsr_01_trigger_number;
        number adsr_01_attack;
        number adsr_01_decay;
        number adsr_01_sustain;
        number adsr_01_release;
        number adsr_01_legato;
        number adsr_01_maxsustain;
        number param_18_value;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_out1;
        number voice_02_mute_number;
        number codebox_03_out1;
        number codebox_03_pitch;
        number param_19_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[2];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float64BufferRef poke_tilde_01_buffer;
        Int adsr_01_phase;
        number adsr_01_mspersamp;
        number adsr_01_time;
        number adsr_01_lastTriggerVal;
        number adsr_01_amplitude;
        number adsr_01_outval;
        number adsr_01_startingpoint;
        signal adsr_01_triggerBuf;
        signal adsr_01_triggerValueBuf;
        bool adsr_01_setupDone;
        number param_18_lastValue;
        Float64BufferRef codebox_03_notes_state;
        Float64BufferRef codebox_03_note_count;
        Float64BufferRef codebox_03_note_on_check;
        number param_19_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_30 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_30()
    {
    }
    
    ~RNBOSubpatcher_30()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        long numWraps = (long)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    template <typename T> inline void poke_default(
        T& buffer,
        SampleValue value,
        SampleValue sampleIndex,
        int channel,
        number overdub
    ) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
    
        if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
            if (overdub != 0) {
                number currentValue = buffer->getSample(channel, sampleIndex);
    
                {
                    value = value + currentValue * overdub;
                }
            }
    
            buffer->setSample(channel, sampleIndex, value);
            buffer->setTouched(true);
        }
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numOutputs);
        RNBO_UNUSED(outputs);
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 6) {
            this->codebox_04_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        }
    
        if (index == 7) {
            this->codebox_04_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    
        if (index == 2) {
            this->codebox_04_note_on_check = new Float64Buffer(this->getPatcher()->note_on_check);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_04_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        this->codebox_04_note_count = new Float64Buffer(this->getPatcher()->note_count);
        this->codebox_04_note_on_check = new Float64Buffer(this->getPatcher()->note_on_check);
    }
    
    protected:
    
    void eventinlet_08_out1_bang_bang() {
        this->codebox_04_in1_bang();
    }
    
    void eventinlet_08_out1_list_set(const list& v) {
        {
            if (v->length > 1)
                this->codebox_04_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->codebox_04_in1_set(converted);
        }
    }
    
    void eventinlet_09_out1_bang_bang() {
        this->codebox_04_in2_bang();
    }
    
    void eventinlet_09_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->codebox_04_in2_set(converted);
        }
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 0;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->codebox_04_notes_state = this->codebox_04_notes_state->allocateIfNeeded();
        this->codebox_04_note_count = this->codebox_04_note_count->allocateIfNeeded();
        this->codebox_04_note_on_check = this->codebox_04_note_on_check->allocateIfNeeded();
    }
    
    void codebox_04_in2_set(number v) {
        this->codebox_04_in2 = v;
    }
    
    void eventinlet_09_out1_number_set(number v) {
        this->codebox_04_in2_set(v);
    }
    
    void eventoutlet_07_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_10_out1_number_set(v);
    }
    
    void codebox_04_out1_set(number v) {
        this->codebox_04_out1 = v;
        this->eventoutlet_07_in1_number_set(this->codebox_04_out1);
    }
    
    void eventoutlet_08_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_10_out2_number_set(v);
    }
    
    void codebox_04_out2_set(number v) {
        this->codebox_04_out2 = v;
        this->eventoutlet_08_in1_number_set(this->codebox_04_out2);
    }
    
    void codebox_04_in1_set(number in1) {
        this->codebox_04_in1 = in1;
        number velocity = this->codebox_04_in2;
        number pitch = this->codebox_04_in1;
        number already = this->codebox_04_note_on_check->getSampleSafe(0, pitch);
    
        if (velocity > 0 && already == 0) {
            this->poke_default(this->codebox_04_note_on_check, 1, pitch, 0, 0);//#map:_###_obj_###_:12
            number index_to_write = this->codebox_04_note_count->getSampleSafe(0, 0);
            number note_level = velocity * velocity / (number)16129;
            number freq_ratio = fixnan(rnbo_pow(2, (pitch - 60) / (number)12));
            this->poke_default(this->codebox_04_notes_state, pitch, index_to_write, 0, 0);//#map:_###_obj_###_:20
            this->poke_default(this->codebox_04_notes_state, note_level, index_to_write, 1, 0);//#map:_###_obj_###_:21
            this->poke_default(this->codebox_04_notes_state, freq_ratio, index_to_write, 2, 0);//#map:_###_obj_###_:22
            this->poke_default(this->codebox_04_note_count, index_to_write + 1, 0, 0, 0);//#map:_###_obj_###_:25
            this->codebox_04_out1_set(pitch + 1);//#map:_###_obj_###_:28
        } else {
            this->codebox_04_out2_set(pitch + 1);//#map:_###_obj_###_:33
        }//#map:midi_process/codebox_obj-11:9
    }
    
    void eventinlet_08_out1_number_set(number v) {
        this->codebox_04_in1_set(v);
    }
    
    void codebox_04_in1_bang() {
        number velocity = this->codebox_04_in2;
        number pitch = this->codebox_04_in1;
        number already = this->codebox_04_note_on_check->getSampleSafe(0, pitch);
    
        if (velocity > 0 && already == 0) {
            this->poke_default(this->codebox_04_note_on_check, 1, pitch, 0, 0);//#map:_###_obj_###_:12
            number index_to_write = this->codebox_04_note_count->getSampleSafe(0, 0);
            number note_level = velocity * velocity / (number)16129;
            number freq_ratio = fixnan(rnbo_pow(2, (pitch - 60) / (number)12));
            this->poke_default(this->codebox_04_notes_state, pitch, index_to_write, 0, 0);//#map:_###_obj_###_:20
            this->poke_default(this->codebox_04_notes_state, note_level, index_to_write, 1, 0);//#map:_###_obj_###_:21
            this->poke_default(this->codebox_04_notes_state, freq_ratio, index_to_write, 2, 0);//#map:_###_obj_###_:22
            this->poke_default(this->codebox_04_note_count, index_to_write + 1, 0, 0, 0);//#map:_###_obj_###_:25
            this->codebox_04_out1_set(pitch + 1);//#map:_###_obj_###_:28
        } else {
            this->codebox_04_out2_set(pitch + 1);//#map:_###_obj_###_:33
        }//#map:midi_process/codebox_obj-11:9
    }
    
    void codebox_04_in2_bang() {}
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        codebox_04_in1 = 0;
        codebox_04_in2 = 0;
        codebox_04_out1 = 0;
        codebox_04_out2 = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number codebox_04_in1;
        number codebox_04_in2;
        number codebox_04_out1;
        number codebox_04_out2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float64BufferRef codebox_04_notes_state;
        Float64BufferRef codebox_04_note_count;
        Float64BufferRef codebox_04_note_on_check;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_04;
    delete this->p_05;
    delete this->p_06;
    delete this->p_07;
    for (int i = 0; i < 2500; i++) {
        delete p_08[i];
    }
    for (int i = 0; i < 128; i++) {
        delete p_09[i];
    }
    delete this->p_10;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

number hann(number x) {
    x = (x > 1 ? 1 : (x < 0 ? 0 : x));
    return 0.5 * (1 - rnbo_cos(6.28318530717958647692 * x));
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number samplerate() const {
    return this->sr;
}

Index vectorsize() const {
    return this->vs;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->p_07_perform(n);
    this->p_08_perform(this->signals[0], this->signals[1], n);
    this->p_06_perform(this->signals[0], this->signals[1], this->signals[2], this->signals[3], n);

    this->p_05_perform(
        in1,
        in2,
        this->signals[2],
        this->signals[3],
        this->signals[4],
        this->signals[5],
        n
    );

    this->p_04_perform(
        this->signals[4],
        this->signals[5],
        this->signals[0],
        this->signals[1],
        out1,
        out2,
        n
    );

    this->p_09_perform(n);
    this->p_10_perform(n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 6; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->data_01_dspsetup(forceDSPSetup);
    this->data_02_dspsetup(forceDSPSetup);
    this->data_03_dspsetup(forceDSPSetup);
    this->data_04_dspsetup(forceDSPSetup);
    this->data_05_dspsetup(forceDSPSetup);
    this->data_06_dspsetup(forceDSPSetup);
    this->data_07_dspsetup(forceDSPSetup);
    this->data_08_dspsetup(forceDSPSetup);
    this->data_09_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    this->p_10->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->scope_index);
        break;
        }
    case 1:
        {
        return addressOf(this->scope);
        break;
        }
    case 2:
        {
        return addressOf(this->note_on_check);
        break;
        }
    case 3:
        {
        return addressOf(this->envelope);
        break;
        }
    case 4:
        {
        return addressOf(this->sample_index);
        break;
        }
    case 5:
        {
        return addressOf(this->source);
        break;
        }
    case 6:
        {
        return addressOf(this->notes_state);
        break;
        }
    case 7:
        {
        return addressOf(this->note_count);
        break;
        }
    case 8:
        {
        return addressOf(this->window);
        break;
        }
    case 9:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 10;
}

void fillwindow(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (number channel = 0; channel < buffer->getChannels(); channel++) {
        for (int index = 0; index < bufsize; index++) {
            number x = index / bufsize;
            number value = this->hann(x);
            buffer->setSample(channel, index, value);
        }
    }
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 8:
        {
        this->fillwindow(ref);
        break;
        }
    case 9:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->data_01_buffer = new Float32Buffer(this->scope_index);
        this->data_01_bufferUpdated();
    }

    if (index == 1) {
        this->data_02_buffer = new Float32Buffer(this->scope);
        this->data_02_bufferUpdated();
    }

    if (index == 2) {
        this->data_03_buffer = new Float64Buffer(this->note_on_check);
        this->data_03_bufferUpdated();
    }

    if (index == 3) {
        this->data_04_buffer = new Float64Buffer(this->envelope);
        this->data_04_bufferUpdated();
    }

    if (index == 4) {
        this->data_05_buffer = new Float64Buffer(this->sample_index);
        this->data_05_bufferUpdated();
    }

    if (index == 5) {
        this->data_09_buffer = new Float64Buffer(this->source);
        this->data_09_bufferUpdated();
    }

    if (index == 6) {
        this->data_06_buffer = new Float64Buffer(this->notes_state);
        this->data_06_bufferUpdated();
    }

    if (index == 7) {
        this->data_07_buffer = new Float64Buffer(this->note_count);
        this->data_07_bufferUpdated();
    }

    if (index == 8) {
        this->data_08_buffer = new Float64Buffer(this->window);
        this->data_08_bufferUpdated();
    }

    this->p_04->processDataViewUpdate(index, time);
    this->p_05->processDataViewUpdate(index, time);
    this->p_06->processDataViewUpdate(index, time);
    this->p_07->processDataViewUpdate(index, time);

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->processDataViewUpdate(index, time);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->processDataViewUpdate(index, time);
    }

    this->p_10->processDataViewUpdate(index, time);
}

void initialize() {
    this->scope_index = initDataRef("scope_index", false, nullptr, "buffer~");
    this->scope = initDataRef("scope", false, nullptr, "buffer~");
    this->note_on_check = initDataRef("note_on_check", false, nullptr, "data");
    this->envelope = initDataRef("envelope", false, nullptr, "data");
    this->sample_index = initDataRef("sample_index", true, nullptr, "data");
    this->source = initDataRef("source", true, nullptr, "data");
    this->notes_state = initDataRef("notes_state", true, nullptr, "data");
    this->note_count = initDataRef("note_count", true, nullptr, "data");
    this->window = initDataRef("window", true, nullptr, "data");
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->scope_index->setIndex(0);
    this->data_01_buffer = new Float32Buffer(this->scope_index);
    this->scope->setIndex(1);
    this->data_02_buffer = new Float32Buffer(this->scope);
    this->note_on_check->setIndex(2);
    this->data_03_buffer = new Float64Buffer(this->note_on_check);
    this->envelope->setIndex(3);
    this->data_04_buffer = new Float64Buffer(this->envelope);
    this->sample_index->setIndex(4);
    this->data_05_buffer = new Float64Buffer(this->sample_index);
    this->source->setIndex(5);
    this->data_09_buffer = new Float64Buffer(this->source);
    this->notes_state->setIndex(6);
    this->data_06_buffer = new Float64Buffer(this->notes_state);
    this->note_count->setIndex(7);
    this->data_07_buffer = new Float64Buffer(this->note_count);
    this->window->setIndex(8);
    this->data_08_buffer = new Float64Buffer(this->window);
    this->RNBODefaultSinus->setIndex(9);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_04 = new RNBOSubpatcher_24();
    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    this->p_05 = new RNBOSubpatcher_25();
    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
    this->p_06 = new RNBOSubpatcher_26();
    this->p_06->setEngineAndPatcher(this->getEngine(), this);
    this->p_06->initialize();
    this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
    this->p_07 = new RNBOSubpatcher_27();
    this->p_07->setEngineAndPatcher(this->getEngine(), this);
    this->p_07->initialize();
    this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));

    for (Index i = 0; i < 2500; i++) {
        this->p_08[(Index)i] = new RNBOSubpatcher_28();
        this->p_08[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->p_08[(Index)i]->initialize();
        this->p_08[(Index)i]->setParameterOffset(this->getParameterOffset(this->p_08[0]));
        this->p_08[(Index)i]->setVoiceIndex(i + 1);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[(Index)i] = new RNBOSubpatcher_29();
        this->p_09[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->p_09[(Index)i]->initialize();
        this->p_09[(Index)i]->setParameterOffset(this->getParameterOffset(this->p_09[0]));
        this->p_09[(Index)i]->setVoiceIndex(i + 1);
    }

    this->p_10 = new RNBOSubpatcher_30();
    this->p_10->setEngineAndPatcher(this->getEngine(), this);
    this->p_10->initialize();
    this->p_10->setParameterOffset(this->getParameterOffset(this->p_10));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "mixer"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "record"));
    this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "feedback"));
    this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "trigger"));

    for (Index i = 0; i < 2500; i++)
        this->p_08[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "cloud", i));

    for (Index i = 0; i < 128; i++)
        this->p_09[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "envelope", i));

    this->p_10->getPreset(getSubState(getSubState(preset, "__sps"), "midi_process"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->p_04->param_01_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "mixer"), "dry"));
    this->p_04->param_02_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "mixer"), "wet"));
    this->p_05->param_03_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "record"), "freeze"));
    this->p_06->param_04_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "damp"));

    this->p_06->param_05_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "amount")
    );

    this->p_07->param_06_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "trigger"), "density")
    );

    this->p_07->param_07_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "trigger"), "probability")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_08_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_tilt")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_09_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_skirt")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_10_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "reverse_prob")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_11_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "amp_blur")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_12_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "pitch_blur")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_13_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "stereo_spread")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_14_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "position1")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_15_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "position2")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_16_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "grain_size1")
    );

    for (Index i0 = 0; i0 < 2500; i0++) this->p_08[i0]->param_17_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "grain_size2")
    );

    for (Index i0 = 0; i0 < 128; i0++) this->p_09[i0]->param_18_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "envelope", i0), "attack")
    );

    for (Index i0 = 0; i0 < 128; i0++) this->p_09[i0]->param_19_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "envelope", i0), "release")
    );
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    RNBO_UNUSED(v);
    this->updateTime(time);

    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            this->p_04->setParameterValue(index, v, time);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            this->p_05->setParameterValue(index, v, time);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            this->p_06->setParameterValue(index, v, time);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            this->p_07->setParameterValue(index, v, time);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters())
            this->p_08[0]->setPolyParameterValue((PatcherInterface**)this->p_08, index, v, time);

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters())
            this->p_09[0]->setPolyParameterValue((PatcherInterface**)this->p_09, index, v, time);

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            this->p_10->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterValue(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterValue(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterValue(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterValue(index);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters())
            return this->p_08[0]->getPolyParameterValue((PatcherInterface**)this->p_08, index);

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters())
            return this->p_09[0]->getPolyParameterValue((PatcherInterface**)this->p_09, index);

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08[0]->getNumParameters() + this->p_09[0]->getNumParameters() + this->p_10->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterName(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterName(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterName(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterName(index);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters()) {
            {
                return this->p_08[0]->getParameterName(index);
            }
        }

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters()) {
            {
                return this->p_09[0]->getParameterName(index);
            }
        }

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterId(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterId(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterId(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterId(index);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters()) {
            {
                return this->p_08[0]->getParameterId(index);
            }
        }

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters()) {
            {
                return this->p_09[0]->getParameterId(index);
            }
        }

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        default:
            {
            index -= 0;

            if (index < this->p_04->getNumParameters())
                this->p_04->getParameterInfo(index, info);

            index -= this->p_04->getNumParameters();

            if (index < this->p_05->getNumParameters())
                this->p_05->getParameterInfo(index, info);

            index -= this->p_05->getNumParameters();

            if (index < this->p_06->getNumParameters())
                this->p_06->getParameterInfo(index, info);

            index -= this->p_06->getNumParameters();

            if (index < this->p_07->getNumParameters())
                this->p_07->getParameterInfo(index, info);

            index -= this->p_07->getNumParameters();

            if (index < this->p_08[0]->getNumParameters()) {
                for (Index i = 0; i < 2500; i++) {
                    this->p_08[i]->getParameterInfo(index, info);
                }
            }

            index -= this->p_08[0]->getNumParameters();

            if (index < this->p_09[0]->getNumParameters()) {
                for (Index i = 0; i < 128; i++) {
                    this->p_09[i]->getParameterInfo(index, info);
                }
            }

            index -= this->p_09[0]->getNumParameters();

            if (index < this->p_10->getNumParameters())
                this->p_10->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_04)
        return 0;

    if (subpatcher == this->p_05)
        return 0 + this->p_04->getNumParameters();

    if (subpatcher == this->p_06)
        return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters();

    if (subpatcher == this->p_07)
        return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();

    if (subpatcher == this->p_08[0])
        return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();

    if (subpatcher == this->p_09[0])
        return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08[0]->getNumParameters();

    if (subpatcher == this->p_10)
        return 0 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters() + this->p_08[0]->getNumParameters() + this->p_09[0]->getNumParameters();

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertToNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertToNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertToNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->convertToNormalizedParameterValue(index, value);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters()) {
            {
                return this->p_08[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters()) {
            {
                return this->p_09[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertFromNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertFromNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertFromNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->convertFromNormalizedParameterValue(index, value);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters()) {
            {
                return this->p_08[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters()) {
            {
                return this->p_09[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->p_04->getNumParameters())
            return this->p_04->constrainParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->constrainParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->constrainParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->constrainParameterValue(index, value);

        index -= this->p_07->getNumParameters();

        if (index < this->p_08[0]->getNumParameters()) {
            {
                return this->p_08[0]->constrainParameterValue(index, value);
            }
        }

        index -= this->p_08[0]->getNumParameters();

        if (index < this->p_09[0]->getNumParameters()) {
            {
                return this->p_09[0]->constrainParameterValue(index, value);
            }
        }

        index -= this->p_09[0]->getNumParameters();

        if (index < this->p_10->getNumParameters())
            return this->p_10->constrainParameterValue(index, value);

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_04->processNumMessage(tag, objectId, time, payload);
    this->p_05->processNumMessage(tag, objectId, time, payload);
    this->p_06->processNumMessage(tag, objectId, time, payload);
    this->p_07->processNumMessage(tag, objectId, time, payload);

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->processNumMessage(tag, objectId, time, payload);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->processNumMessage(tag, objectId, time, payload);
    }

    this->p_10->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_04->processListMessage(tag, objectId, time, payload);
    this->p_05->processListMessage(tag, objectId, time, payload);
    this->p_06->processListMessage(tag, objectId, time, payload);
    this->p_07->processListMessage(tag, objectId, time, payload);

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->processListMessage(tag, objectId, time, payload);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->processListMessage(tag, objectId, time, payload);
    }

    this->p_10->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_04->processBangMessage(tag, objectId, time);
    this->p_05->processBangMessage(tag, objectId, time);
    this->p_06->processBangMessage(tag, objectId, time);
    this->p_07->processBangMessage(tag, objectId, time);

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->processBangMessage(tag, objectId, time);
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->processBangMessage(tag, objectId, time);
    }

    this->p_10->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->p_04->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_05->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    auto subpatchResult_2 = this->p_06->resolveTag(tag);

    if (subpatchResult_2)
        return subpatchResult_2;

    auto subpatchResult_3 = this->p_07->resolveTag(tag);

    if (subpatchResult_3)
        return subpatchResult_3;

    auto subpatchResult_4 = this->p_08[0]->resolveTag(tag);

    if (subpatchResult_4)
        return subpatchResult_4;

    auto subpatchResult_5 = this->p_09[0]->resolveTag(tag);

    if (subpatchResult_5)
        return subpatchResult_5;

    auto subpatchResult_6 = this->p_10->resolveTag(tag);

    if (subpatchResult_6)
        return subpatchResult_6;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_04->allocateDataRefs();
    this->p_05->allocateDataRefs();
    this->p_06->allocateDataRefs();
    this->p_07->allocateDataRefs();

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->allocateDataRefs();
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->allocateDataRefs();
    }

    this->p_10->allocateDataRefs();
    this->data_01_buffer->requestSize(1, 1);
    this->data_01_buffer->setSampleRate(this->sr);
    this->data_03_buffer->requestSize(128, 1);
    this->data_03_buffer->setSampleRate(this->sr);
    this->data_04_buffer->requestSize(128, 1);
    this->data_04_buffer->setSampleRate(this->sr);
    this->data_05_buffer->requestSize(1, 1);
    this->data_05_buffer->setSampleRate(this->sr);
    this->data_06_buffer->requestSize(128, 3);
    this->data_06_buffer->setSampleRate(this->sr);
    this->data_07_buffer->requestSize(1, 1);
    this->data_07_buffer->setSampleRate(this->sr);
    this->data_08_buffer->requestSize(65536, 1);
    this->data_08_buffer->setSampleRate(this->sr);
    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->scope_index->hasRequestedSize()) {
        if (this->scope_index->wantsFill())
            this->zeroDataRef(this->scope_index);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->data_02_buffer = this->data_02_buffer->allocateIfNeeded();

    if (this->scope->hasRequestedSize()) {
        if (this->scope->wantsFill())
            this->zeroDataRef(this->scope);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->data_03_buffer = this->data_03_buffer->allocateIfNeeded();

    if (this->note_on_check->hasRequestedSize()) {
        if (this->note_on_check->wantsFill())
            this->zeroDataRef(this->note_on_check);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->data_04_buffer = this->data_04_buffer->allocateIfNeeded();

    if (this->envelope->hasRequestedSize()) {
        if (this->envelope->wantsFill())
            this->zeroDataRef(this->envelope);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->data_05_buffer = this->data_05_buffer->allocateIfNeeded();

    if (this->sample_index->hasRequestedSize()) {
        if (this->sample_index->wantsFill())
            this->zeroDataRef(this->sample_index);

        this->getEngine()->sendDataRefUpdated(4);
    }

    this->data_09_buffer = this->data_09_buffer->allocateIfNeeded();

    if (this->source->hasRequestedSize()) {
        if (this->source->wantsFill())
            this->zeroDataRef(this->source);

        this->getEngine()->sendDataRefUpdated(5);
    }

    this->data_06_buffer = this->data_06_buffer->allocateIfNeeded();

    if (this->notes_state->hasRequestedSize()) {
        if (this->notes_state->wantsFill())
            this->zeroDataRef(this->notes_state);

        this->getEngine()->sendDataRefUpdated(6);
    }

    this->data_07_buffer = this->data_07_buffer->allocateIfNeeded();

    if (this->note_count->hasRequestedSize()) {
        if (this->note_count->wantsFill())
            this->zeroDataRef(this->note_count);

        this->getEngine()->sendDataRefUpdated(7);
    }

    this->data_08_buffer = this->data_08_buffer->allocateIfNeeded();

    if (this->window->hasRequestedSize()) {
        if (this->window->wantsFill())
            this->fillwindow(this->window);

        this->getEngine()->sendDataRefUpdated(8);
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(9);
    }
}

void initializeObjects() {
    this->data_01_init();
    this->data_02_init();
    this->data_03_init();
    this->data_04_init();
    this->data_05_init();
    this->data_06_init();
    this->data_07_init();
    this->data_08_init();
    this->data_09_init();
    this->p_04->initializeObjects();
    this->p_05->initializeObjects();
    this->p_06->initializeObjects();
    this->p_07->initializeObjects();

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->initializeObjects();
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->initializeObjects();
    }

    this->p_10->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_04->startup();
    this->p_05->startup();
    this->p_06->startup();
    this->p_07->startup();

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->startup();
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->startup();
    }

    this->p_10->startup();
    this->processParamInitEvents();
}

void notein_01_outchannel_set(number ) {}

void notein_01_releasevelocity_set(number ) {}

void p_10_in2_number_set(number v) {
    this->p_10->updateTime(this->_currentTime);
    this->p_10->eventinlet_09_out1_number_set(v);
}

void notein_01_velocity_set(number v) {
    this->p_10_in2_number_set(v);
}

void p_09_voicestatus_set(const list& v) {
    for (Index i = 0; i < 128; i++) {
        if (i + 1 == this->p_09_target || 0 == this->p_09_target) {
            this->p_09[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 128; i++) {
        if (i + 1 == this->p_09_target || 0 == this->p_09_target) {
            this->p_09[i]->voice_02_mutein_list_set(v);
        }
    }
}

void p_09_activevoices_set(number v) {
    for (Index i = 0; i < 128; i++) {
        if (i + 1 == this->p_09_target || 0 == this->p_09_target) {
            this->p_09[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 128; i++) {
        this->p_09[i]->voice_02_activevoices_set(v);
    }
}

void p_09_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 128; i++) {
            this->p_09[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 128) {
            this->p_09[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->p_09_voicestatus_set(tmp);
    this->p_09_activevoices_set(this->p_09_calcActiveVoices());
}

void pack_03_out_set(const list& v) {
    this->p_09_mute_set(v);
}

void pack_03_in1_set(number v) {
    this->pack_03_in1 = v;
    list array = list(0, 0);
    array[0] = trunc(this->pack_03_in1);
    array[1] = this->pack_03_in2;
    this->pack_03_out_set(array);
}

void trigger_05_out3_set(number v) {
    this->pack_03_in1_set(v);
}

void p_09_target_set(number v) {
    this->p_09_target = v;
}

void trigger_05_out2_set(number v) {
    this->p_09_target_set(v);
}

void p_09_in1_number_set(number v) {
    for (Index i = 0; i < 128; i++) {
        if (i + 1 == this->p_09_target || 0 == this->p_09_target) {
            this->p_09[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 128; i++) {
        if (i + 1 == this->p_09_target || 0 == this->p_09_target) {
            this->p_09[i]->eventinlet_07_out1_number_set(v);
        }
    }
}

void trigger_05_out1_set(number v) {
    this->p_09_in1_number_set(v);
}

void trigger_05_input_number_set(number v) {
    this->trigger_05_out3_set(trunc(v));
    this->trigger_05_out2_set(trunc(v));
    this->trigger_05_out1_set(1);
}

void p_10_out1_number_set(number v) {
    this->trigger_05_input_number_set(v);
}

void trigger_06_out2_set(number v) {
    this->p_09_target_set(v);
}

void trigger_06_out1_set(number v) {
    this->p_09_in1_number_set(v);
}

void trigger_06_input_number_set(number v) {
    this->trigger_06_out2_set(trunc(v));
    this->trigger_06_out1_set(0);
}

void p_10_out2_number_set(number v) {
    this->trigger_06_input_number_set(v);
}

void p_10_in1_number_set(number v) {
    this->p_10->updateTime(this->_currentTime);
    this->p_10->eventinlet_08_out1_number_set(v);
}

void notein_01_notenumber_set(number v) {
    this->p_10_in1_number_set(v);
}

void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
        if (status == 144 || status == 128) {
            this->notein_01_outchannel_set(channel);

            if (status == 128) {
                this->notein_01_releasevelocity_set(data[2]);
                this->notein_01_velocity_set(0);
            } else {
                this->notein_01_releasevelocity_set(0);
                this->notein_01_velocity_set(data[2]);
            }

            this->notein_01_notenumber_set(data[1]);
        }
    }
}

void p_08_voicestatus_set(const list& v) {
    for (Index i = 0; i < 2500; i++) {
        if (i + 1 == this->p_08_target || 0 == this->p_08_target) {
            this->p_08[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 2500; i++) {
        if (i + 1 == this->p_08_target || 0 == this->p_08_target) {
            this->p_08[i]->voice_01_mutein_list_set(v);
        }
    }
}

void p_08_activevoices_set(number v) {
    for (Index i = 0; i < 2500; i++) {
        if (i + 1 == this->p_08_target || 0 == this->p_08_target) {
            this->p_08[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 2500; i++) {
        this->p_08[i]->voice_01_activevoices_set(v);
    }
}

void p_08_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 2500; i++) {
            this->p_08[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 2500) {
            this->p_08[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->p_08_voicestatus_set(tmp);
    this->p_08_activevoices_set(this->p_08_calcActiveVoices());
}

void pack_02_out_set(const list& v) {
    this->p_08_mute_set(v);
}

void pack_02_in1_set(number v) {
    this->pack_02_in1 = v;
    list array = list(0, 0);
    array[0] = trunc(this->pack_02_in1);
    array[1] = this->pack_02_in2;
    this->pack_02_out_set(array);
}

void trigger_04_out3_set(number v) {
    this->pack_02_in1_set(v);
}

void p_08_target_set(number v) {
    this->p_08_target = v;
}

void trigger_04_out2_set(number v) {
    this->p_08_target_set(v);
}

void p_08_in1_number_set(number v) {
    for (Index i = 0; i < 2500; i++) {
        if (i + 1 == this->p_08_target || 0 == this->p_08_target) {
            this->p_08[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 2500; i++) {
        if (i + 1 == this->p_08_target || 0 == this->p_08_target) {
            this->p_08[i]->eventinlet_06_out1_number_set(v);
        }
    }
}

void trigger_04_out1_set(number v) {
    this->p_08_in1_number_set(v);
}

void trigger_04_input_number_set(number v) {
    this->trigger_04_out3_set(trunc(v));
    this->trigger_04_out2_set(trunc(v));
    this->trigger_04_out1_set(trunc(v));
}

void p_07_out1_number_set(number v) {
    this->trigger_04_input_number_set(v);
}

void p_07_perform(Index n) {
    // subpatcher: trigger
    this->p_07->process(nullptr, 0, nullptr, 0, n);
}

void p_08_perform(SampleValue * out1, SampleValue * out2, Index n) {
    // subpatcher: cloud
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 2500; i++)
        this->p_08[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void p_06_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: feedback
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_06->process(ins, 2, outs, 2, n);
}

void p_05_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: record
    ConstSampleArray<4> ins = {in1, in2, in3, in4};

    SampleArray<2> outs = {out1, out2};
    this->p_05->process(ins, 4, outs, 2, n);
}

void p_04_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: mixer
    ConstSampleArray<4> ins = {in1, in2, in3, in4};

    SampleArray<2> outs = {out1, out2};
    this->p_04->process(ins, 4, outs, 2, n);
}

void p_09_perform(Index n) {
    // subpatcher: envelope
    for (Index i = 0; i < 128; i++)
        this->p_09[(Index)i]->process(nullptr, 0, nullptr, 0, n);
}

void p_10_perform(Index n) {
    // subpatcher: midi_process
    this->p_10->process(nullptr, 0, nullptr, 0, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_01_srout_set(number ) {}

void data_01_chanout_set(number ) {}

void data_01_sizeout_set(number v) {
    this->data_01_sizeout = v;
}

void data_02_srout_set(number ) {}

void data_02_chanout_set(number ) {}

void data_02_sizeout_set(number v) {
    this->data_02_sizeout = v;
}

void data_03_srout_set(number ) {}

void data_03_chanout_set(number ) {}

void data_03_sizeout_set(number v) {
    this->data_03_sizeout = v;
}

void data_04_srout_set(number ) {}

void data_04_chanout_set(number ) {}

void data_04_sizeout_set(number v) {
    this->data_04_sizeout = v;
}

void data_05_srout_set(number ) {}

void data_05_chanout_set(number ) {}

void data_05_sizeout_set(number v) {
    this->data_05_sizeout = v;
}

void data_06_srout_set(number ) {}

void data_06_chanout_set(number ) {}

void data_06_sizeout_set(number v) {
    this->data_06_sizeout = v;
}

void data_07_srout_set(number ) {}

void data_07_chanout_set(number ) {}

void data_07_sizeout_set(number v) {
    this->data_07_sizeout = v;
}

void data_08_srout_set(number ) {}

void data_08_chanout_set(number ) {}

void data_08_sizeout_set(number v) {
    this->data_08_sizeout = v;
}

void data_09_srout_set(number ) {}

void data_09_chanout_set(number ) {}

void data_09_sizeout_set(number v) {
    this->data_09_sizeout = v;
}

void data_01_init() {
    this->data_01_buffer->setWantsFill(true);
}

Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_01_dspsetup(bool force) {
    if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_01_sizemode == 2) {
        this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
        updateDataRef(this, this->data_01_buffer);
    } else if (this->data_01_sizemode == 3) {
        this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_01_buffer);
    }

    this->data_01_setupDone = true;
}

void data_01_bufferUpdated() {
    this->data_01_report();
}

void data_01_report() {
    this->data_01_srout_set(this->data_01_buffer->getSampleRate());
    this->data_01_chanout_set(this->data_01_buffer->getChannels());
    this->data_01_sizeout_set(this->data_01_buffer->getSize());
}

void data_02_init() {
    {
        this->data_02_buffer->requestSize(
            this->data_02_evaluateSizeExpr(this->samplerate(), this->vectorsize()),
            this->data_02_channels
        );
    }

    this->data_02_buffer->setWantsFill(true);
}

Index data_02_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    number size = 0;

    {
        size = samplerate * 5;
    }

    return (Index)(size);
}

void data_02_dspsetup(bool force) {
    if ((bool)(this->data_02_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_02_sizemode == 2) {
        this->data_02_buffer = this->data_02_buffer->setSize((Index)(this->mstosamps(this->data_02_sizems)));
        updateDataRef(this, this->data_02_buffer);
    } else if (this->data_02_sizemode == 3) {
        this->data_02_buffer = this->data_02_buffer->setSize(this->data_02_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_02_buffer);
    }

    this->data_02_setupDone = true;
}

void data_02_bufferUpdated() {
    this->data_02_report();
}

void data_02_report() {
    this->data_02_srout_set(this->data_02_buffer->getSampleRate());
    this->data_02_chanout_set(this->data_02_buffer->getChannels());
    this->data_02_sizeout_set(this->data_02_buffer->getSize());
}

void data_03_init() {
    this->data_03_buffer->setWantsFill(true);
}

Index data_03_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_03_dspsetup(bool force) {
    if ((bool)(this->data_03_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_03_sizemode == 2) {
        this->data_03_buffer = this->data_03_buffer->setSize((Index)(this->mstosamps(this->data_03_sizems)));
        updateDataRef(this, this->data_03_buffer);
    } else if (this->data_03_sizemode == 3) {
        this->data_03_buffer = this->data_03_buffer->setSize(this->data_03_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_03_buffer);
    }

    this->data_03_setupDone = true;
}

void data_03_bufferUpdated() {
    this->data_03_report();
}

void data_03_report() {
    this->data_03_srout_set(this->data_03_buffer->getSampleRate());
    this->data_03_chanout_set(this->data_03_buffer->getChannels());
    this->data_03_sizeout_set(this->data_03_buffer->getSize());
}

void data_04_init() {
    this->data_04_buffer->setWantsFill(true);
}

Index data_04_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_04_dspsetup(bool force) {
    if ((bool)(this->data_04_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_04_sizemode == 2) {
        this->data_04_buffer = this->data_04_buffer->setSize((Index)(this->mstosamps(this->data_04_sizems)));
        updateDataRef(this, this->data_04_buffer);
    } else if (this->data_04_sizemode == 3) {
        this->data_04_buffer = this->data_04_buffer->setSize(this->data_04_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_04_buffer);
    }

    this->data_04_setupDone = true;
}

void data_04_bufferUpdated() {
    this->data_04_report();
}

void data_04_report() {
    this->data_04_srout_set(this->data_04_buffer->getSampleRate());
    this->data_04_chanout_set(this->data_04_buffer->getChannels());
    this->data_04_sizeout_set(this->data_04_buffer->getSize());
}

void data_05_init() {
    this->data_05_buffer->setWantsFill(true);
}

Index data_05_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_05_dspsetup(bool force) {
    if ((bool)(this->data_05_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_05_sizemode == 2) {
        this->data_05_buffer = this->data_05_buffer->setSize((Index)(this->mstosamps(this->data_05_sizems)));
        updateDataRef(this, this->data_05_buffer);
    } else if (this->data_05_sizemode == 3) {
        this->data_05_buffer = this->data_05_buffer->setSize(this->data_05_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_05_buffer);
    }

    this->data_05_setupDone = true;
}

void data_05_bufferUpdated() {
    this->data_05_report();
}

void data_05_report() {
    this->data_05_srout_set(this->data_05_buffer->getSampleRate());
    this->data_05_chanout_set(this->data_05_buffer->getChannels());
    this->data_05_sizeout_set(this->data_05_buffer->getSize());
}

void data_06_init() {
    this->data_06_buffer->setWantsFill(true);
}

Index data_06_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_06_dspsetup(bool force) {
    if ((bool)(this->data_06_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_06_sizemode == 2) {
        this->data_06_buffer = this->data_06_buffer->setSize((Index)(this->mstosamps(this->data_06_sizems)));
        updateDataRef(this, this->data_06_buffer);
    } else if (this->data_06_sizemode == 3) {
        this->data_06_buffer = this->data_06_buffer->setSize(this->data_06_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_06_buffer);
    }

    this->data_06_setupDone = true;
}

void data_06_bufferUpdated() {
    this->data_06_report();
}

void data_06_report() {
    this->data_06_srout_set(this->data_06_buffer->getSampleRate());
    this->data_06_chanout_set(this->data_06_buffer->getChannels());
    this->data_06_sizeout_set(this->data_06_buffer->getSize());
}

void data_07_init() {
    this->data_07_buffer->setWantsFill(true);
}

Index data_07_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_07_dspsetup(bool force) {
    if ((bool)(this->data_07_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_07_sizemode == 2) {
        this->data_07_buffer = this->data_07_buffer->setSize((Index)(this->mstosamps(this->data_07_sizems)));
        updateDataRef(this, this->data_07_buffer);
    } else if (this->data_07_sizemode == 3) {
        this->data_07_buffer = this->data_07_buffer->setSize(this->data_07_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_07_buffer);
    }

    this->data_07_setupDone = true;
}

void data_07_bufferUpdated() {
    this->data_07_report();
}

void data_07_report() {
    this->data_07_srout_set(this->data_07_buffer->getSampleRate());
    this->data_07_chanout_set(this->data_07_buffer->getChannels());
    this->data_07_sizeout_set(this->data_07_buffer->getSize());
}

void data_08_init() {
    this->data_08_buffer->setWantsFill(true);
}

Index data_08_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_08_dspsetup(bool force) {
    if ((bool)(this->data_08_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_08_sizemode == 2) {
        this->data_08_buffer = this->data_08_buffer->setSize((Index)(this->mstosamps(this->data_08_sizems)));
        updateDataRef(this, this->data_08_buffer);
    } else if (this->data_08_sizemode == 3) {
        this->data_08_buffer = this->data_08_buffer->setSize(this->data_08_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_08_buffer);
    }

    this->data_08_setupDone = true;
}

void data_08_bufferUpdated() {
    this->data_08_report();
}

void data_08_report() {
    this->data_08_srout_set(this->data_08_buffer->getSampleRate());
    this->data_08_chanout_set(this->data_08_buffer->getChannels());
    this->data_08_sizeout_set(this->data_08_buffer->getSize());
}

void data_09_init() {
    {
        this->data_09_buffer->requestSize(
            this->data_09_evaluateSizeExpr(this->samplerate(), this->vectorsize()),
            this->data_09_channels
        );
    }

    this->data_09_buffer->setWantsFill(true);
}

Index data_09_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    number size = 0;

    {
        size = samplerate * 640;
    }

    return (Index)(size);
}

void data_09_dspsetup(bool force) {
    if ((bool)(this->data_09_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_09_sizemode == 2) {
        this->data_09_buffer = this->data_09_buffer->setSize((Index)(this->mstosamps(this->data_09_sizems)));
        updateDataRef(this, this->data_09_buffer);
    } else if (this->data_09_sizemode == 3) {
        this->data_09_buffer = this->data_09_buffer->setSize(this->data_09_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_09_buffer);
    }

    this->data_09_setupDone = true;
}

void data_09_bufferUpdated() {
    this->data_09_report();
}

void data_09_report() {
    this->data_09_srout_set(this->data_09_buffer->getSampleRate());
    this->data_09_chanout_set(this->data_09_buffer->getChannels());
    this->data_09_sizeout_set(this->data_09_buffer->getSize());
}

number p_08_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 2500; i++) {
            if ((bool)(!(bool)(this->p_08[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

number p_09_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 128; i++) {
            if ((bool)(!(bool)(this->p_09[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    data_01_sizeout = 0;
    data_01_size = 1;
    data_01_sizems = 0;
    data_01_normalize = 0.995;
    data_01_channels = 1;
    data_02_sizeout = 0;
    data_02_size = 0;
    data_02_sizems = 0;
    data_02_normalize = 0.995;
    data_02_channels = 1;
    data_03_sizeout = 0;
    data_03_size = 128;
    data_03_sizems = 0;
    data_03_normalize = 0.995;
    data_03_channels = 1;
    data_04_sizeout = 0;
    data_04_size = 128;
    data_04_sizems = 0;
    data_04_normalize = 0.995;
    data_04_channels = 1;
    p_04_target = 0;
    data_05_sizeout = 0;
    data_05_size = 1;
    data_05_sizems = 0;
    data_05_normalize = 0.995;
    data_05_channels = 1;
    p_05_target = 0;
    data_06_sizeout = 0;
    data_06_size = 128;
    data_06_sizems = 0;
    data_06_normalize = 0.995;
    data_06_channels = 3;
    data_07_sizeout = 0;
    data_07_size = 1;
    data_07_sizems = 0;
    data_07_normalize = 0.995;
    data_07_channels = 1;
    data_08_sizeout = 0;
    data_08_size = 65536;
    data_08_sizems = 0;
    data_08_normalize = 0.995;
    data_08_channels = 1;
    data_09_sizeout = 0;
    data_09_size = 0;
    data_09_sizems = 0;
    data_09_normalize = 0.995;
    data_09_channels = 2;
    p_06_target = 0;
    p_07_target = 0;
    p_08_target = 0;
    pack_02_in1 = 0;
    pack_02_in2 = 0;
    p_09_target = 0;
    p_10_target = 0;
    notein_01_channel = 0;
    pack_03_in1 = 0;
    pack_03_in2 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    data_01_sizemode = 1;
    data_01_setupDone = false;
    data_02_sizemode = 3;
    data_02_setupDone = false;
    data_03_sizemode = 1;
    data_03_setupDone = false;
    data_04_sizemode = 1;
    data_04_setupDone = false;
    data_05_sizemode = 1;
    data_05_setupDone = false;
    data_06_sizemode = 1;
    data_06_setupDone = false;
    data_07_sizemode = 1;
    data_07_setupDone = false;
    data_08_sizemode = 1;
    data_08_setupDone = false;
    data_09_sizemode = 3;
    data_09_setupDone = false;
    notein_01_status = 0;
    notein_01_byte1 = -1;
    notein_01_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number data_02_sizeout;
    number data_02_size;
    number data_02_sizems;
    number data_02_normalize;
    number data_02_channels;
    number data_03_sizeout;
    number data_03_size;
    number data_03_sizems;
    number data_03_normalize;
    number data_03_channels;
    number data_04_sizeout;
    number data_04_size;
    number data_04_sizems;
    number data_04_normalize;
    number data_04_channels;
    number p_04_target;
    number data_05_sizeout;
    number data_05_size;
    number data_05_sizems;
    number data_05_normalize;
    number data_05_channels;
    number p_05_target;
    number data_06_sizeout;
    number data_06_size;
    number data_06_sizems;
    number data_06_normalize;
    number data_06_channels;
    number data_07_sizeout;
    number data_07_size;
    number data_07_sizems;
    number data_07_normalize;
    number data_07_channels;
    number data_08_sizeout;
    number data_08_size;
    number data_08_sizems;
    number data_08_normalize;
    number data_08_channels;
    number data_09_sizeout;
    number data_09_size;
    number data_09_sizems;
    number data_09_normalize;
    number data_09_channels;
    number p_06_target;
    number p_07_target;
    number p_08_target;
    number pack_02_in1;
    number pack_02_in2;
    number p_09_target;
    number p_10_target;
    number notein_01_channel;
    number pack_03_in1;
    number pack_03_in2;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[6];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    Float32BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    Float32BufferRef data_02_buffer;
    Int data_02_sizemode;
    bool data_02_setupDone;
    Float64BufferRef data_03_buffer;
    Int data_03_sizemode;
    bool data_03_setupDone;
    Float64BufferRef data_04_buffer;
    Int data_04_sizemode;
    bool data_04_setupDone;
    Float64BufferRef data_05_buffer;
    Int data_05_sizemode;
    bool data_05_setupDone;
    Float64BufferRef data_06_buffer;
    Int data_06_sizemode;
    bool data_06_setupDone;
    Float64BufferRef data_07_buffer;
    Int data_07_sizemode;
    bool data_07_setupDone;
    Float64BufferRef data_08_buffer;
    Int data_08_sizemode;
    bool data_08_setupDone;
    Float64BufferRef data_09_buffer;
    Int data_09_sizemode;
    bool data_09_setupDone;
    int notein_01_status;
    int notein_01_byte1;
    int notein_01_inchan;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef scope_index;
    DataRef scope;
    DataRef note_on_check;
    DataRef envelope;
    DataRef sample_index;
    DataRef source;
    DataRef notes_state;
    DataRef note_count;
    DataRef window;
    DataRef RNBODefaultSinus;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_24* p_04;
    RNBOSubpatcher_25* p_05;
    RNBOSubpatcher_26* p_06;
    RNBOSubpatcher_27* p_07;
    RNBOSubpatcher_28* p_08[2500];
    RNBOSubpatcher_29* p_09[128];
    RNBOSubpatcher_30* p_10;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

