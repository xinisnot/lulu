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

class RNBOSubpatcher_12 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_12()
    {
    }
    
    ~RNBOSubpatcher_12()
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
                    value = value * (1. - overdub) + currentValue * overdub;
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
        this->codebox_tilde_01_perform(in1, in2, this->codebox_tilde_01_freeze, out1, out2, n);
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_01_getPresetValue(getSubState(preset, "freeze"));
    }
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
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
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
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
            return this->param_01_value_constrain(value);
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
    
        if (index == 0) {
            this->codebox_tilde_01_source = new Float64Buffer(this->getPatcher()->source);
        }
    
        if (index == 1) {
            this->codebox_tilde_01_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_tilde_01_source = new Float64Buffer(this->getPatcher()->source);
        this->codebox_tilde_01_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
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
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->codebox_tilde_01_counter_init();
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
    }
    
    static number param_01_value_constrain(number v) {
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
        number freeze,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            number state = freeze == 0;
            number index = this->codebox_tilde_01_counter_next(state, 0, this->dim(this->codebox_tilde_01_source))[0];
            this->poke_default(this->codebox_tilde_01_sample_index, index, 0, 0, 0);//#map:_###_obj_###_:10
    
            if (state != 0) {
                this->codebox_tilde_01_source->setSampleSafe(0, index, in1[(Index)i]);//#map:_###_obj_###_:14
                this->codebox_tilde_01_source->setSampleSafe(1, index, in2[(Index)i]);//#map:_###_obj_###_:15
            }//#map:_###_obj_###_:12
    
            out1[(Index)i] = in1[(Index)i];//#map:_###_obj_###_:18
            out2[(Index)i] = in2[(Index)i];//#map:_###_obj_###_:19
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    array<number, 3> codebox_tilde_01_counter_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->codebox_tilde_01_counter_count = 0;
            this->codebox_tilde_01_counter_carry = 0;
        } else {
            this->codebox_tilde_01_counter_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->codebox_tilde_01_counter_count >= limit) || (a < 0 && this->codebox_tilde_01_counter_count <= limit)) {
                    this->codebox_tilde_01_counter_count = 0;
                    this->codebox_tilde_01_counter_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->codebox_tilde_01_counter_count,
            carry_flag,
            this->codebox_tilde_01_counter_carry
        };
    }
    
    void codebox_tilde_01_counter_init() {
        this->codebox_tilde_01_counter_count = -1;
    }
    
    void codebox_tilde_01_counter_reset() {
        this->codebox_tilde_01_counter_carry = 0;
        this->codebox_tilde_01_counter_count = 0;
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
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
        codebox_tilde_01_freeze = 0;
        param_01_value = 0;
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
        codebox_tilde_01_counter_carry = 0;
        codebox_tilde_01_counter_count = 0;
        param_01_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number codebox_tilde_01_in1;
        number codebox_tilde_01_in2;
        number codebox_tilde_01_freeze;
        number param_01_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        int codebox_tilde_01_counter_carry;
        number codebox_tilde_01_counter_count;
        Float64BufferRef codebox_tilde_01_source;
        Float64BufferRef codebox_tilde_01_sample_index;
        number param_01_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_13 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_09 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_13;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_09()
            {
            }
            
            ~RNBOSubpatcher_09()
            {
            }
            
            virtual RNBOSubpatcher_13* getPatcher() const {
                return static_cast<RNBOSubpatcher_13 *>(_parentPatcher);
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
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
            
                this->svf_tilde_01_perform(
                    in1,
                    this->svf_tilde_01_freq,
                    this->svf_tilde_01_q,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->dummyBuffer,
                    n
                );
            
                this->selector_01_perform(
                    this->selector_01_onoff,
                    in1,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
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
            
                this->svf_tilde_01_dspsetup(forceDSPSetup);
            
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
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
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
            
            void eventinlet_01_out1_bang_bang() {}
            
            void eventinlet_01_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->svf_tilde_01_freq_set(converted);
                }
            }
            
            void eventinlet_02_out1_bang_bang() {}
            
            void eventinlet_02_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->svf_tilde_01_q_set(converted);
                }
            }
            
            void eventinlet_03_out1_bang_bang() {
                this->expr_01_in1_bang();
            }
            
            void eventinlet_03_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_01_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_01_in1_set(converted);
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
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void svf_tilde_01_freq_set(number v) {
                this->svf_tilde_01_freq = v;
            }
            
            void eventinlet_01_out1_number_set(number v) {
                this->svf_tilde_01_freq_set(v);
            }
            
            void svf_tilde_01_q_set(number v) {
                this->svf_tilde_01_q = v;
            }
            
            void eventinlet_02_out1_number_set(number v) {
                this->svf_tilde_01_q_set(v);
            }
            
            void selector_01_onoff_set(number v) {
                this->selector_01_onoff = v;
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->selector_01_onoff_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:feedback/state_variable_filter~[1]/+_obj-2:1
            }
            
            void eventinlet_03_out1_number_set(number v) {
                this->expr_01_in1_set(v);
            }
            
            void expr_01_in1_bang() {
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:feedback/state_variable_filter~[1]/+_obj-2:1
            }
            
            void expr_01_in2_set(number v) {
                this->expr_01_in2 = v;
            }
            
            void svf_tilde_01_perform(
                const Sample * x,
                number freq,
                number q,
                SampleValue * out1,
                SampleValue * out2,
                SampleValue * out3,
                SampleValue * out4,
                Index n
            ) {
                auto __svf_tilde_01_high = this->svf_tilde_01_high;
                auto __svf_tilde_01_notch = this->svf_tilde_01_notch;
                auto __svf_tilde_01_band = this->svf_tilde_01_band;
                auto __svf_tilde_01_low = this->svf_tilde_01_low;
                auto __svf_tilde_01__q = this->svf_tilde_01__q;
                auto __svf_tilde_01__freq = this->svf_tilde_01__freq;
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (this->svf_tilde_01_dFreq_next(freq) != 0) {
                        __svf_tilde_01__freq = (freq > this->sr * 0.25 ? this->sr * 0.25 : (freq < 0.0 ? 0.0 : freq));
                        __svf_tilde_01__freq = rnbo_sin(6.28318530717958647692 * __svf_tilde_01__freq / this->sr);
                        __svf_tilde_01__freq = (__svf_tilde_01__freq > 0.99 ? 0.99 : (__svf_tilde_01__freq < 0.001 ? 0.001 : __svf_tilde_01__freq));
                    }
            
                    if (this->svf_tilde_01_dQ_next(q) != 0) {
                        __svf_tilde_01__q = (1. - q) * 1.2;
                        __svf_tilde_01__q = __svf_tilde_01__q * __svf_tilde_01__q;
                        __svf_tilde_01__q = (__svf_tilde_01__q > 0.99 ? 0.99 : (__svf_tilde_01__q < 0.001 ? 0.001 : __svf_tilde_01__q));
                    }
            
                    __svf_tilde_01_low += __svf_tilde_01__freq * __svf_tilde_01_band;
                    __svf_tilde_01_notch = x[(Index)i] - __svf_tilde_01__q * __svf_tilde_01_band;
                    __svf_tilde_01_high = __svf_tilde_01_notch - __svf_tilde_01_low;
                    __svf_tilde_01_band += __svf_tilde_01__freq * __svf_tilde_01_high - __svf_tilde_01_band * __svf_tilde_01_band * __svf_tilde_01_band * 0.0001;
                    array<number, 4> tmp = {0, 0, 0, 0};
                    tmp[0] = __svf_tilde_01_low;
                    tmp[1] = __svf_tilde_01_high;
                    tmp[2] = __svf_tilde_01_band;
                    tmp[3] = __svf_tilde_01_notch;
                    out1[(Index)i] = tmp[0];
                    out2[(Index)i] = tmp[1];
                    out3[(Index)i] = tmp[2];
                    out4[(Index)i] = tmp[3];
                }
            
                this->svf_tilde_01__freq = __svf_tilde_01__freq;
                this->svf_tilde_01__q = __svf_tilde_01__q;
                this->svf_tilde_01_low = __svf_tilde_01_low;
                this->svf_tilde_01_band = __svf_tilde_01_band;
                this->svf_tilde_01_notch = __svf_tilde_01_notch;
                this->svf_tilde_01_high = __svf_tilde_01_high;
            }
            
            void selector_01_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else if (onoff >= 3 && onoff < 4)
                        out[(Index)i] = in3[(Index)i];
                    else if (onoff >= 4 && onoff < 5)
                        out[(Index)i] = in4[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number svf_tilde_01_dFreq_next(number x) {
                number temp = (number)(x - this->svf_tilde_01_dFreq_prev);
                this->svf_tilde_01_dFreq_prev = x;
                return temp;
            }
            
            void svf_tilde_01_dFreq_dspsetup() {
                this->svf_tilde_01_dFreq_reset();
            }
            
            void svf_tilde_01_dFreq_reset() {
                this->svf_tilde_01_dFreq_prev = 0;
            }
            
            number svf_tilde_01_dQ_next(number x) {
                number temp = (number)(x - this->svf_tilde_01_dQ_prev);
                this->svf_tilde_01_dQ_prev = x;
                return temp;
            }
            
            void svf_tilde_01_dQ_dspsetup() {
                this->svf_tilde_01_dQ_reset();
            }
            
            void svf_tilde_01_dQ_reset() {
                this->svf_tilde_01_dQ_prev = 0;
            }
            
            void svf_tilde_01_reset() {
                this->svf_tilde_01_low = 0;
                this->svf_tilde_01_high = 0;
                this->svf_tilde_01_band = 0;
                this->svf_tilde_01_notch = 0;
                this->svf_tilde_01_dFreq_reset();
                this->svf_tilde_01_dQ_reset();
            }
            
            void svf_tilde_01_dspsetup(bool force) {
                if ((bool)(this->svf_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->svf_tilde_01_reset();
                this->svf_tilde_01_setupDone = true;
                this->svf_tilde_01_dFreq_dspsetup();
                this->svf_tilde_01_dQ_dspsetup();
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
                selector_01_onoff = 1;
                svf_tilde_01_x = 0;
                svf_tilde_01_freq = 0;
                svf_tilde_01_q = 0;
                expr_01_in1 = 0;
                expr_01_in2 = 1;
                expr_01_out1 = 0;
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
                svf_tilde_01_low = 0;
                svf_tilde_01_high = 0;
                svf_tilde_01_band = 0;
                svf_tilde_01_notch = 0;
                svf_tilde_01__freq = 0.001;
                svf_tilde_01__q = 0.001;
                svf_tilde_01_dFreq_prev = 0;
                svf_tilde_01_dQ_prev = 0;
                svf_tilde_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_01_onoff;
                number svf_tilde_01_x;
                number svf_tilde_01_freq;
                number svf_tilde_01_q;
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[3];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number svf_tilde_01_low;
                number svf_tilde_01_high;
                number svf_tilde_01_band;
                number svf_tilde_01_notch;
                number svf_tilde_01__freq;
                number svf_tilde_01__q;
                number svf_tilde_01_dFreq_prev;
                number svf_tilde_01_dQ_prev;
                bool svf_tilde_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_10 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_13;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_10()
            {
            }
            
            ~RNBOSubpatcher_10()
            {
            }
            
            virtual RNBOSubpatcher_13* getPatcher() const {
                return static_cast<RNBOSubpatcher_13 *>(_parentPatcher);
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
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
            
                this->svf_tilde_02_perform(
                    in1,
                    this->svf_tilde_02_freq,
                    this->svf_tilde_02_q,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->dummyBuffer,
                    n
                );
            
                this->selector_02_perform(
                    this->selector_02_onoff,
                    in1,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
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
            
                this->svf_tilde_02_dspsetup(forceDSPSetup);
            
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
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
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
            
            void eventinlet_04_out1_bang_bang() {}
            
            void eventinlet_04_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->svf_tilde_02_freq_set(converted);
                }
            }
            
            void eventinlet_05_out1_bang_bang() {}
            
            void eventinlet_05_out1_list_set(const list& v) {
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->svf_tilde_02_q_set(converted);
                }
            }
            
            void eventinlet_06_out1_bang_bang() {
                this->expr_02_in1_bang();
            }
            
            void eventinlet_06_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_02_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_02_in1_set(converted);
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
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void svf_tilde_02_freq_set(number v) {
                this->svf_tilde_02_freq = v;
            }
            
            void eventinlet_04_out1_number_set(number v) {
                this->svf_tilde_02_freq_set(v);
            }
            
            void svf_tilde_02_q_set(number v) {
                this->svf_tilde_02_q = v;
            }
            
            void eventinlet_05_out1_number_set(number v) {
                this->svf_tilde_02_q_set(v);
            }
            
            void selector_02_onoff_set(number v) {
                this->selector_02_onoff = v;
            }
            
            void expr_02_out1_set(number v) {
                this->expr_02_out1 = v;
                this->selector_02_onoff_set(this->expr_02_out1);
            }
            
            void expr_02_in1_set(number in1) {
                this->expr_02_in1 = in1;
                this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:feedback/state_variable_filter~/+_obj-2:1
            }
            
            void eventinlet_06_out1_number_set(number v) {
                this->expr_02_in1_set(v);
            }
            
            void expr_02_in1_bang() {
                this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:feedback/state_variable_filter~/+_obj-2:1
            }
            
            void expr_02_in2_set(number v) {
                this->expr_02_in2 = v;
            }
            
            void svf_tilde_02_perform(
                const Sample * x,
                number freq,
                number q,
                SampleValue * out1,
                SampleValue * out2,
                SampleValue * out3,
                SampleValue * out4,
                Index n
            ) {
                auto __svf_tilde_02_high = this->svf_tilde_02_high;
                auto __svf_tilde_02_notch = this->svf_tilde_02_notch;
                auto __svf_tilde_02_band = this->svf_tilde_02_band;
                auto __svf_tilde_02_low = this->svf_tilde_02_low;
                auto __svf_tilde_02__q = this->svf_tilde_02__q;
                auto __svf_tilde_02__freq = this->svf_tilde_02__freq;
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (this->svf_tilde_02_dFreq_next(freq) != 0) {
                        __svf_tilde_02__freq = (freq > this->sr * 0.25 ? this->sr * 0.25 : (freq < 0.0 ? 0.0 : freq));
                        __svf_tilde_02__freq = rnbo_sin(6.28318530717958647692 * __svf_tilde_02__freq / this->sr);
                        __svf_tilde_02__freq = (__svf_tilde_02__freq > 0.99 ? 0.99 : (__svf_tilde_02__freq < 0.001 ? 0.001 : __svf_tilde_02__freq));
                    }
            
                    if (this->svf_tilde_02_dQ_next(q) != 0) {
                        __svf_tilde_02__q = (1. - q) * 1.2;
                        __svf_tilde_02__q = __svf_tilde_02__q * __svf_tilde_02__q;
                        __svf_tilde_02__q = (__svf_tilde_02__q > 0.99 ? 0.99 : (__svf_tilde_02__q < 0.001 ? 0.001 : __svf_tilde_02__q));
                    }
            
                    __svf_tilde_02_low += __svf_tilde_02__freq * __svf_tilde_02_band;
                    __svf_tilde_02_notch = x[(Index)i] - __svf_tilde_02__q * __svf_tilde_02_band;
                    __svf_tilde_02_high = __svf_tilde_02_notch - __svf_tilde_02_low;
                    __svf_tilde_02_band += __svf_tilde_02__freq * __svf_tilde_02_high - __svf_tilde_02_band * __svf_tilde_02_band * __svf_tilde_02_band * 0.0001;
                    array<number, 4> tmp = {0, 0, 0, 0};
                    tmp[0] = __svf_tilde_02_low;
                    tmp[1] = __svf_tilde_02_high;
                    tmp[2] = __svf_tilde_02_band;
                    tmp[3] = __svf_tilde_02_notch;
                    out1[(Index)i] = tmp[0];
                    out2[(Index)i] = tmp[1];
                    out3[(Index)i] = tmp[2];
                    out4[(Index)i] = tmp[3];
                }
            
                this->svf_tilde_02__freq = __svf_tilde_02__freq;
                this->svf_tilde_02__q = __svf_tilde_02__q;
                this->svf_tilde_02_low = __svf_tilde_02_low;
                this->svf_tilde_02_band = __svf_tilde_02_band;
                this->svf_tilde_02_notch = __svf_tilde_02_notch;
                this->svf_tilde_02_high = __svf_tilde_02_high;
            }
            
            void selector_02_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else if (onoff >= 3 && onoff < 4)
                        out[(Index)i] = in3[(Index)i];
                    else if (onoff >= 4 && onoff < 5)
                        out[(Index)i] = in4[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number svf_tilde_02_dFreq_next(number x) {
                number temp = (number)(x - this->svf_tilde_02_dFreq_prev);
                this->svf_tilde_02_dFreq_prev = x;
                return temp;
            }
            
            void svf_tilde_02_dFreq_dspsetup() {
                this->svf_tilde_02_dFreq_reset();
            }
            
            void svf_tilde_02_dFreq_reset() {
                this->svf_tilde_02_dFreq_prev = 0;
            }
            
            number svf_tilde_02_dQ_next(number x) {
                number temp = (number)(x - this->svf_tilde_02_dQ_prev);
                this->svf_tilde_02_dQ_prev = x;
                return temp;
            }
            
            void svf_tilde_02_dQ_dspsetup() {
                this->svf_tilde_02_dQ_reset();
            }
            
            void svf_tilde_02_dQ_reset() {
                this->svf_tilde_02_dQ_prev = 0;
            }
            
            void svf_tilde_02_reset() {
                this->svf_tilde_02_low = 0;
                this->svf_tilde_02_high = 0;
                this->svf_tilde_02_band = 0;
                this->svf_tilde_02_notch = 0;
                this->svf_tilde_02_dFreq_reset();
                this->svf_tilde_02_dQ_reset();
            }
            
            void svf_tilde_02_dspsetup(bool force) {
                if ((bool)(this->svf_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->svf_tilde_02_reset();
                this->svf_tilde_02_setupDone = true;
                this->svf_tilde_02_dFreq_dspsetup();
                this->svf_tilde_02_dQ_dspsetup();
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
                selector_02_onoff = 1;
                svf_tilde_02_x = 0;
                svf_tilde_02_freq = 0;
                svf_tilde_02_q = 0;
                expr_02_in1 = 0;
                expr_02_in2 = 1;
                expr_02_out1 = 0;
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
                svf_tilde_02_low = 0;
                svf_tilde_02_high = 0;
                svf_tilde_02_band = 0;
                svf_tilde_02_notch = 0;
                svf_tilde_02__freq = 0.001;
                svf_tilde_02__q = 0.001;
                svf_tilde_02_dFreq_prev = 0;
                svf_tilde_02_dQ_prev = 0;
                svf_tilde_02_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_02_onoff;
                number svf_tilde_02_x;
                number svf_tilde_02_freq;
                number svf_tilde_02_q;
                number expr_02_in1;
                number expr_02_in2;
                number expr_02_out1;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[3];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number svf_tilde_02_low;
                number svf_tilde_02_high;
                number svf_tilde_02_band;
                number svf_tilde_02_notch;
                number svf_tilde_02__freq;
                number svf_tilde_02__q;
                number svf_tilde_02_dFreq_prev;
                number svf_tilde_02_dQ_prev;
                bool svf_tilde_02_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_11 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_13;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_11()
            {
            }
            
            ~RNBOSubpatcher_11()
            {
            }
            
            virtual RNBOSubpatcher_13* getPatcher() const {
                return static_cast<RNBOSubpatcher_13 *>(_parentPatcher);
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
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
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
            
            void eventinlet_07_out1_bang_bang() {
                this->codebox_01_in1_bang();
            }
            
            void eventinlet_07_out1_list_set(const list& v) {
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
                this->getPatcher()->p_03_out1_number_set(v);
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
            
            void eventinlet_07_out1_number_set(number v) {
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
                SampleIndex audioProcessSampleCount;
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
    
    RNBOSubpatcher_13()
    {
    }
    
    ~RNBOSubpatcher_13()
    {
        delete this->p_01;
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
        this->p_03_perform(n);
        this->linetilde_01_perform(this->signals[0], n);
        this->feedbackreader_01_perform(this->signals[1], n);
        this->dcblock_tilde_01_perform(this->signals[1], this->dcblock_tilde_01_gain, this->signals[2], n);
        this->dspexpr_01_perform(this->signals[2], this->signals[0], this->signals[1], n);
        this->gen_01_perform(this->signals[1], this->signals[2], n);
        this->p_01_perform(this->signals[2], out1, n);
        this->feedbackreader_02_perform(this->signals[2], n);
        this->dcblock_tilde_02_perform(this->signals[2], this->dcblock_tilde_02_gain, this->signals[1], n);
        this->dspexpr_02_perform(this->signals[1], this->signals[0], this->signals[2], n);
        this->gen_02_perform(this->signals[2], this->signals[0], n);
        this->p_02_perform(this->signals[0], out2, n);
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
        this->dcblock_tilde_02_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
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
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_09();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
        this->p_02 = new RNBOSubpatcher_10();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_11();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_02_getPresetValue(getSubState(preset, "frequency"));
        this->param_03_getPresetValue(getSubState(preset, "resonance"));
        this->param_04_getPresetValue(getSubState(preset, "amount"));
        this->param_05_getPresetValue(getSubState(preset, "type"));
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "state_variable_filter~[1]"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "state_variable_filter~"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "dbtoa_with_-70inf"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_01->processTempoEvent(time, tempo);
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_01->processTransportEvent(time, state);
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_01->processBeatTimeEvent(time, beattime);
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_02_value_set(v);
            break;
            }
        case 1:
            {
            this->param_03_value_set(v);
            break;
            }
        case 2:
            {
            this->param_04_value_set(v);
            break;
            }
        case 3:
            {
            this->param_05_value_set(v);
            break;
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            index -= this->p_01->getNumParameters();
    
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
            return this->param_02_value;
            }
        case 1:
            {
            return this->param_03_value;
            }
        case 2:
            {
            return this->param_04_value;
            }
        case 3:
            {
            return this->param_05_value;
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
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
        return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "frequency";
            }
        case 1:
            {
            return "resonance";
            }
        case 2:
            {
            return "amount";
            }
        case 3:
            {
            return "type";
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            index -= this->p_01->getNumParameters();
    
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
            return "feedback/frequency";
            }
        case 1:
            {
            return "feedback/resonance";
            }
        case 2:
            {
            return "feedback/amount";
            }
        case 3:
            {
            return "feedback/type";
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            index -= this->p_01->getNumParameters();
    
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
                info->initialValue = 800;
                info->min = 0;
                info->max = 22050;
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
            case 2:
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
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 3;
                info->exponent = 1;
                info->steps = 4;
                static const char * eVal3[] = {"bypass", "lowpass", "hightpass", "bandpass"};
                info->enumValues = eVal3;
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
            default:
                {
                index -= 4;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                index -= this->p_01->getNumParameters();
    
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
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 4;
    
        if (subpatcher == this->p_02)
            return 4 + this->p_01->getNumParameters();
    
        if (subpatcher == this->p_03)
            return 4 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
    
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
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 3:
            {
            {
                value = (value < 0 ? 0 : (value > 3 ? 3 : value));
                ParameterValue normalizedValue = (value - 0) / (3 - 0);
    
                {
                    normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 4);
                }
    
                return normalizedValue;
            }
            }
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 22050 ? 22050 : value));
                ParameterValue normalizedValue = (value - 0) / (22050 - 0);
                return normalizedValue;
            }
            }
        case 2:
            {
            {
                value = (value < -70 ? -70 : (value > 30 ? 30 : value));
                ParameterValue normalizedValue = (value - -70) / (30 - -70);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
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
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 3:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    value = this->applyStepsToNormalizedParameterValue(value, 4);
                }
    
                {
                    return 0 + value * (3 - 0);
                }
            }
            }
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (22050 - 0);
                }
            }
            }
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return -70 + value * (30 - -70);
                }
            }
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
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
            return this->param_02_value_constrain(value);
            }
        case 1:
            {
            return this->param_03_value_constrain(value);
            }
        case 2:
            {
            return this->param_04_value_constrain(value);
            }
        case 3:
            {
            return this->param_05_value_constrain(value);
            }
        default:
            {
            index -= 4;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
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
        case -281953904:
            {
            this->linetilde_01_target_bang();
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
        this->p_01->processListMessage(tag, objectId, time, payload);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
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
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void param_02_value_set(number v) {
        v = this->param_02_value_constrain(v);
        this->param_02_value = v;
        this->sendParameter(0, false);
    
        if (this->param_02_value != this->param_02_lastValue) {
            this->getEngine()->presetTouched();
            this->param_02_lastValue = this->param_02_value;
        }
    
        this->p_02_in2_number_set(v);
        this->p_01_in2_number_set(v);
    }
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(1, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        this->p_02_in3_number_set(v);
        this->p_01_in3_number_set(v);
    }
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(2, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->p_03_in1_number_set(v);
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(3, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->p_02_in4_number_set(v);
        this->p_01_in4_number_set(v);
    }
    
    void linetilde_01_target_bang() {}
    
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
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->p_02->startup();
        this->p_03->startup();
    
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
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
    }
    
    static number param_02_value_constrain(number v) {
        v = (v > 22050 ? 22050 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_02_in2_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_04_out1_number_set(v);
    }
    
    void p_01_in2_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_01_out1_number_set(v);
    }
    
    static number param_03_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void p_02_in3_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_05_out1_number_set(v);
    }
    
    void p_01_in3_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_02_out1_number_set(v);
    }
    
    static number param_04_value_constrain(number v) {
        v = (v > 30 ? 30 : (v < -70 ? -70 : v));
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
    
    void pack_01_out_set(const list& v) {
        this->linetilde_01_segments_set(v);
    }
    
    void pack_01_in1_set(number v) {
        this->pack_01_in1 = v;
        list array = list(0, 0);
        array[0] = this->pack_01_in1;
        array[1] = this->pack_01_in2;
        this->pack_01_out_set(array);
    }
    
    void p_03_out1_number_set(number v) {
        this->pack_01_in1_set(v);
    }
    
    void p_03_in1_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->eventinlet_07_out1_number_set(v);
    }
    
    static number param_05_value_constrain(number v) {
        v = (v > 3 ? 3 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)3 / (number)3;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void p_02_in4_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_06_out1_number_set(v);
    }
    
    void p_01_in4_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_03_out1_number_set(v);
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
    
    void p_03_perform(Index n) {
        // subpatcher: dbtoa_with_-70inf
        this->p_03->process(nullptr, 0, nullptr, 0, n);
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
                            -281953904,
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
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
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
    
    void p_01_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        // subpatcher: state_variable_filter~
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<1> outs = {out1};
        this->p_01->process(ins, 1, outs, 1, n);
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
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
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
    
    void p_02_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        // subpatcher: state_variable_filter~
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<1> outs = {out1};
        this->p_02->process(ins, 1, outs, 1, n);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
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
    
    void param_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_02_value;
    }
    
    void param_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_02_value_set(preset["value"]);
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
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
        gen_01_in1 = 0;
        p_01_target = 0;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        dcblock_tilde_01_x = 0;
        dcblock_tilde_01_gain = 0.9997;
        gen_02_in1 = 0;
        p_02_target = 0;
        dcblock_tilde_02_x = 0;
        dcblock_tilde_02_gain = 0.9997;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        param_02_value = 800;
        param_03_value = 0;
        p_03_target = 0;
        linetilde_01_time = 0;
        linetilde_01_keepramp = 0;
        pack_01_in1 = 0;
        pack_01_in2 = 50;
        param_04_value = -70;
        param_05_value = 0;
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
        dcblock_tilde_01_xm1 = 0;
        dcblock_tilde_01_ym1 = 0;
        dcblock_tilde_01_setupDone = false;
        feedbacktilde_01_feedbackbuffer = nullptr;
        dcblock_tilde_02_xm1 = 0;
        dcblock_tilde_02_ym1 = 0;
        dcblock_tilde_02_setupDone = false;
        feedbacktilde_02_feedbackbuffer = nullptr;
        param_02_lastValue = 0;
        param_03_lastValue = 0;
        linetilde_01_currentValue = 0;
        param_04_lastValue = 0;
        param_05_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number gen_01_in1;
        number p_01_target;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dcblock_tilde_01_x;
        number dcblock_tilde_01_gain;
        number gen_02_in1;
        number p_02_target;
        number dcblock_tilde_02_x;
        number dcblock_tilde_02_gain;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number param_02_value;
        number param_03_value;
        number p_03_target;
        list linetilde_01_segments;
        number linetilde_01_time;
        number linetilde_01_keepramp;
        number pack_01_in1;
        number pack_01_in2;
        number param_04_value;
        number param_05_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[3];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number dcblock_tilde_01_xm1;
        number dcblock_tilde_01_ym1;
        bool dcblock_tilde_01_setupDone;
        signal feedbacktilde_01_feedbackbuffer;
        number dcblock_tilde_02_xm1;
        number dcblock_tilde_02_ym1;
        bool dcblock_tilde_02_setupDone;
        signal feedbacktilde_02_feedbackbuffer;
        number param_02_lastValue;
        number param_03_lastValue;
        list linetilde_01_activeRamps;
        number linetilde_01_currentValue;
        number param_04_lastValue;
        number param_05_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_09* p_01;
        RNBOSubpatcher_10* p_02;
        RNBOSubpatcher_11* p_03;
    
};

class RNBOSubpatcher_14 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_14()
    {
    }
    
    ~RNBOSubpatcher_14()
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
        getEngine()->flushClockEvents(this, 1821745152, false);
        getEngine()->flushClockEvents(this, -611950441, false);
        getEngine()->flushClockEvents(this, -1584063977, false);
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
                    value = value * (1. - overdub) + currentValue * overdub;
                }
            }
    
            buffer->setSample(channel, sampleIndex, value);
            buffer->setTouched(true);
        }
    }
    
    number random(number low, number high) {
        number range = high - low;
        return rand01() * range + low;
    }
    
    number samplerate() {
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
        this->dspexpr_03_perform(this->signals[1], this->dspexpr_03_in2, this->signals[0], n);
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_06_getPresetValue(getSubState(preset, "density"));
        this->param_07_getPresetValue(getSubState(preset, "probability"));
    }
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
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
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
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
        case 1821745152:
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
    
        if (index == 2) {
            this->codebox_02_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
        }
    
        if (index == 3) {
            this->codebox_02_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_02_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
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
        if (this->codebox_02_note_count->getSampleSafe(0, 0) != 0) {
            number arp_index = this->safemod(
                this->codebox_02_arp_count->getSampleSafe(0, 0) + 1,
                this->codebox_02_note_count->getSampleSafe(0, 0)
            );
    
            this->poke_default(this->codebox_02_arp_count, arp_index, 0, 0, 0);//#map:_###_obj_###_:12
    
            if (this->random(0, 1) <= this->codebox_02_probability) {
                this->codebox_02_out1_set(this->codebox_02_counter);//#map:_###_obj_###_:17
                this->codebox_02_counter += 1;//#map:_###_obj_###_:18
                this->codebox_02_counter = this->wrap(this->codebox_02_counter, 1, this->codebox_02_voice_num + 1);//#map:_###_obj_###_:19
            }//#map:_###_obj_###_:15
        }//#map:trigger/codebox_obj-12:8
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
        this->getEngine()->scheduleClockEvent(this, 1821745152, 0 + this->_currentTime);;
    
        {
            this->scheduleParamInit(0, 0);
        }
    
        {
            this->scheduleParamInit(1, 0);
        }
    }
    
    void allocateDataRefs() {
        this->codebox_02_arp_count = this->codebox_02_arp_count->allocateIfNeeded();
        this->codebox_02_note_count = this->codebox_02_note_count->allocateIfNeeded();
    }
    
    static number param_06_value_constrain(number v) {
        v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void phasor_01_freq_set(number v) {
        this->phasor_01_freq = v;
    }
    
    static number param_07_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number codebox_02_probability_constrain(number v) {
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
    
    void eventoutlet_03_in1_number_set(number v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_06_out2_number_set(v);
    }
    
    void trigger_01_out2_set(number v) {
        this->eventoutlet_03_in1_number_set(v);
    }
    
    void eventoutlet_02_in1_bang_bang() {
        ;
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_06_out1_bang_bang();
    }
    
    void trigger_01_out1_bang() {
        this->eventoutlet_02_in1_bang_bang();
    }
    
    void trigger_01_input_number_set(number v) {
        this->trigger_01_out2_set(trunc(v));
        this->trigger_01_out1_bang();
    }
    
    void codebox_02_out1_set(number v) {
        this->codebox_02_out1 = v;
        this->trigger_01_input_number_set(this->codebox_02_out1);
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
    
    void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
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
        codebox_02_voice_num = 1500;
        param_06_value = 1;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0;
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
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number delta_tilde_01_x;
        number phasor_01_freq;
        number param_07_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
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
        Float64BufferRef codebox_02_arp_count;
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

class RNBOSubpatcher_15 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_15()
    {
    }
    
    ~RNBOSubpatcher_15()
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
        getEngine()->flushClockEvents(this, -611950441, false);
        getEngine()->flushClockEvents(this, -1584063977, false);
        getEngine()->flushClockEvents(this, -871642103, false);
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    number random(number low, number high) {
        number range = high - low;
        return rand01() * range + low;
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
    
    number samplerate() {
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
    
                    SampleIndex index1 = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        {
                            {
                                {
                                    bufferreadsample_result = __buffer->getSample(channelIndex, index1);
                                }
                            }
                        }
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
    
                {
                    number size = __end - 1 - __start;
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
    
                    SampleIndex index1 = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        number frac = sampleIndex - index1;
                        number wrap = bufferSize - 1;
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
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
        }
    
        return out;
    }
    
    template <typename T> inline array<SampleValue, 1 + 1> peek_interp_linear(T& buffer, SampleValue sampleIndex, Index channelOffset) {
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
    
                    SampleIndex index1 = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        number frac = sampleIndex - index1;
                        number wrap = bufferSize - 1;
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
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
            return out;
        }
    }
    
    template <typename T> inline number dim(T& buffer) {
        return buffer->getSize();
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
            this->gen_03_arp_mode,
            this->gen_03_window_square_max,
            this->gen_03_window_square_min,
            this->gen_03_window_saw_max,
            this->gen_03_window_saw_min,
            this->gen_03_grain_reverse_prob,
            this->gen_03_pitch_spread_ratio,
            this->gen_03_stereo_spread,
            this->gen_03_grain_amp_spread,
            this->gen_03_grain_size_max,
            this->gen_03_grain_size_min,
            this->gen_03_position_spread_max,
            this->gen_03_position_spread_min,
            this->gen_03_voice_index,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            n
        );
    
        this->signaladder_03_perform(this->signals[1], out1, out1, n);
        this->signaladder_04_perform(this->signals[2], out2, out2, n);
        this->edge_02_perform(this->signals[3], n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& preset) {
        this->param_08_getPresetValue(getSubState(preset, "position_spread_min"));
        this->param_09_getPresetValue(getSubState(preset, "position_spread_max"));
        this->param_10_getPresetValue(getSubState(preset, "size_min"));
        this->param_11_getPresetValue(getSubState(preset, "size_max"));
        this->param_12_getPresetValue(getSubState(preset, "window_saw_min"));
        this->param_13_getPresetValue(getSubState(preset, "window_saw_max"));
        this->param_14_getPresetValue(getSubState(preset, "window_square_min"));
        this->param_15_getPresetValue(getSubState(preset, "window_square_max"));
        this->param_16_getPresetValue(getSubState(preset, "reverse_prob"));
        this->param_17_getPresetValue(getSubState(preset, "stereo_spread"));
        this->param_18_getPresetValue(getSubState(preset, "amp_spread"));
        this->param_19_getPresetValue(getSubState(preset, "arp"));
        this->param_20_getPresetValue(getSubState(preset, "pitch_spread"));
    }
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
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
        case 10:
            {
            this->param_18_value_set(v);
            break;
            }
        case 11:
            {
            this->param_19_value_set(v);
            break;
            }
        case 12:
            {
            this->param_20_value_set(v);
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
        case 10:
            {
            return this->param_18_value;
            }
        case 11:
            {
            return this->param_19_value;
            }
        case 12:
            {
            return this->param_20_value;
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
            for (Index i = 0; i < 1500; i++)
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
        return 13;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "position_spread_min";
            }
        case 1:
            {
            return "position_spread_max";
            }
        case 2:
            {
            return "size_min";
            }
        case 3:
            {
            return "size_max";
            }
        case 4:
            {
            return "window_saw_min";
            }
        case 5:
            {
            return "window_saw_max";
            }
        case 6:
            {
            return "window_square_min";
            }
        case 7:
            {
            return "window_square_max";
            }
        case 8:
            {
            return "reverse_prob";
            }
        case 9:
            {
            return "stereo_spread";
            }
        case 10:
            {
            return "amp_spread";
            }
        case 11:
            {
            return "arp";
            }
        case 12:
            {
            return "pitch_spread";
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
            return "cloud/position_spread_min";
            }
        case 1:
            {
            return "cloud/position_spread_max";
            }
        case 2:
            {
            return "cloud/size_min";
            }
        case 3:
            {
            return "cloud/size_max";
            }
        case 4:
            {
            return "cloud/window_saw_min";
            }
        case 5:
            {
            return "cloud/window_saw_max";
            }
        case 6:
            {
            return "cloud/window_square_min";
            }
        case 7:
            {
            return "cloud/window_square_max";
            }
        case 8:
            {
            return "cloud/reverse_prob";
            }
        case 9:
            {
            return "cloud/stereo_spread";
            }
        case 10:
            {
            return "cloud/amp_spread";
            }
        case 11:
            {
            return "cloud/arp";
            }
        case 12:
            {
            return "cloud/pitch_spread";
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
                info->max = 10000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "ms";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 100;
                info->min = 0;
                info->max = 10000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "ms";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 0.00001;
                info->max = 10000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "ms";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 50;
                info->min = 0.00001;
                info->max = 10000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = true;
                info->displayName = "";
                info->unit = "ms";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
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
            case 5:
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
            case 6:
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
            case 7:
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
            case 8:
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
            case 9:
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
            case 10:
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
            case 11:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 2;
                static const char * eVal11[] = {"off", "on"};
                info->enumValues = eVal11;
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
            case 12:
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
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 11:
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
        case 12:
            {
            {
                value = (value < 0 ? 0 : (value > 1200 ? 1200 : value));
                ParameterValue normalizedValue = (value - 0) / (1200 - 0);
                return normalizedValue;
            }
            }
        case 0:
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 10000 ? 10000 : value));
                ParameterValue normalizedValue = (value - 0) / (10000 - 0);
                return normalizedValue;
            }
            }
        case 2:
        case 3:
            {
            {
                value = (value < 0.00001 ? 0.00001 : (value > 10000 ? 10000 : value));
                ParameterValue normalizedValue = (value - 0.00001) / (10000 - 0.00001);
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
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 11:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    value = this->applyStepsToNormalizedParameterValue(value, 2);
                }
    
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 12:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (1200 - 0);
                }
            }
            }
        case 0:
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0 + value * (10000 - 0);
                }
            }
            }
        case 2:
        case 3:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0.00001 + value * (10000 - 0.00001);
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
        case 10:
            {
            return this->param_18_value_constrain(value);
            }
        case 11:
            {
            return this->param_19_value_constrain(value);
            }
        case 12:
            {
            return this->param_20_value_constrain(value);
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
        case -611950441:
            {
            this->edge_02_onout_bang();
            break;
            }
        case -1584063977:
            {
            this->edge_02_offout_bang();
            break;
            }
        case -871642103:
            {
            this->loadbang_01_startupbang_bang();
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
            if (TAG("cloud/loadbang_obj-4") == objectId)
                this->loadbang_01_startupbang_bang();
    
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
        case TAG("cloud/loadbang_obj-4"):
            {
            return "cloud/loadbang_obj-4";
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
    
        if (index == 2) {
            this->gen_03_buf_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
        }
    
        if (index == 1) {
            this->gen_03_buf_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        }
    
        if (index == 3) {
            this->gen_03_buf_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    
        if (index == 4) {
            this->gen_03_buf_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        }
    
        if (index == 5) {
            this->gen_03_buf_window = new Float64Buffer(this->getPatcher()->window);
        }
    
        if (index == 0) {
            this->gen_03_buf_source = new Float64Buffer(this->getPatcher()->source);
        }
    
        if (index == 6) {
            this->gen_03_cycle_19_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
            this->gen_03_cycle_21_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->gen_03_buf_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
        this->gen_03_buf_sample_index = new Float64Buffer(this->getPatcher()->sample_index);
        this->gen_03_buf_note_count = new Float64Buffer(this->getPatcher()->note_count);
        this->gen_03_buf_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        this->gen_03_buf_window = new Float64Buffer(this->getPatcher()->window);
        this->gen_03_buf_source = new Float64Buffer(this->getPatcher()->source);
        this->gen_03_cycle_19_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
        this->gen_03_cycle_21_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultSinus);
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
    
        this->mstosamps_01_ms_set(v);
    }
    
    void param_09_value_set(number v) {
        v = this->param_09_value_constrain(v);
        this->param_09_value = v;
        this->sendParameter(1, false);
    
        if (this->param_09_value != this->param_09_lastValue) {
            this->getEngine()->presetTouched();
            this->param_09_lastValue = this->param_09_value;
        }
    
        this->mstosamps_02_ms_set(v);
    }
    
    void param_10_value_set(number v) {
        v = this->param_10_value_constrain(v);
        this->param_10_value = v;
        this->sendParameter(2, false);
    
        if (this->param_10_value != this->param_10_lastValue) {
            this->getEngine()->presetTouched();
            this->param_10_lastValue = this->param_10_value;
        }
    
        this->mstosamps_03_ms_set(v);
    }
    
    void param_11_value_set(number v) {
        v = this->param_11_value_constrain(v);
        this->param_11_value = v;
        this->sendParameter(3, false);
    
        if (this->param_11_value != this->param_11_lastValue) {
            this->getEngine()->presetTouched();
            this->param_11_lastValue = this->param_11_value;
        }
    
        this->mstosamps_04_ms_set(v);
    }
    
    void param_12_value_set(number v) {
        v = this->param_12_value_constrain(v);
        this->param_12_value = v;
        this->sendParameter(4, false);
    
        if (this->param_12_value != this->param_12_lastValue) {
            this->getEngine()->presetTouched();
            this->param_12_lastValue = this->param_12_value;
        }
    
        this->gen_03_window_saw_min_set(v);
    }
    
    void param_13_value_set(number v) {
        v = this->param_13_value_constrain(v);
        this->param_13_value = v;
        this->sendParameter(5, false);
    
        if (this->param_13_value != this->param_13_lastValue) {
            this->getEngine()->presetTouched();
            this->param_13_lastValue = this->param_13_value;
        }
    
        this->gen_03_window_saw_max_set(v);
    }
    
    void param_14_value_set(number v) {
        v = this->param_14_value_constrain(v);
        this->param_14_value = v;
        this->sendParameter(6, false);
    
        if (this->param_14_value != this->param_14_lastValue) {
            this->getEngine()->presetTouched();
            this->param_14_lastValue = this->param_14_value;
        }
    
        this->gen_03_window_square_min_set(v);
    }
    
    void param_15_value_set(number v) {
        v = this->param_15_value_constrain(v);
        this->param_15_value = v;
        this->sendParameter(7, false);
    
        if (this->param_15_value != this->param_15_lastValue) {
            this->getEngine()->presetTouched();
            this->param_15_lastValue = this->param_15_value;
        }
    
        this->gen_03_window_square_max_set(v);
    }
    
    void param_16_value_set(number v) {
        v = this->param_16_value_constrain(v);
        this->param_16_value = v;
        this->sendParameter(8, false);
    
        if (this->param_16_value != this->param_16_lastValue) {
            this->getEngine()->presetTouched();
            this->param_16_lastValue = this->param_16_value;
        }
    
        this->gen_03_grain_reverse_prob_set(v);
    }
    
    void param_17_value_set(number v) {
        v = this->param_17_value_constrain(v);
        this->param_17_value = v;
        this->sendParameter(9, false);
    
        if (this->param_17_value != this->param_17_lastValue) {
            this->getEngine()->presetTouched();
            this->param_17_lastValue = this->param_17_value;
        }
    
        this->gen_03_stereo_spread_set(v);
    }
    
    void param_18_value_set(number v) {
        v = this->param_18_value_constrain(v);
        this->param_18_value = v;
        this->sendParameter(10, false);
    
        if (this->param_18_value != this->param_18_lastValue) {
            this->getEngine()->presetTouched();
            this->param_18_lastValue = this->param_18_value;
        }
    
        this->gen_03_grain_amp_spread_set(v);
    }
    
    void param_19_value_set(number v) {
        v = this->param_19_value_constrain(v);
        this->param_19_value = v;
        this->sendParameter(11, false);
    
        if (this->param_19_value != this->param_19_lastValue) {
            this->getEngine()->presetTouched();
            this->param_19_lastValue = this->param_19_value;
        }
    
        this->gen_03_arp_mode_set(v);
    }
    
    void param_20_value_set(number v) {
        v = this->param_20_value_constrain(v);
        this->param_20_value = v;
        this->sendParameter(12, false);
    
        if (this->param_20_value != this->param_20_lastValue) {
            this->getEngine()->presetTouched();
            this->param_20_lastValue = this->param_20_value;
        }
    
        this->expr_03_in1_set(v);
    }
    
    void eventinlet_08_out1_number_set(number v) {
        this->trigger_02_input_number_set(v);
    }
    
    void eventinlet_08_out1_list_set(const list& v) {
        this->trigger_02_input_list_set(v);
    }
    
    void edge_02_onout_bang() {}
    
    void edge_02_offout_bang() {
        this->voice_01_mute_bang_bang();
    }
    
    void loadbang_01_startupbang_bang() {
        this->loadbang_01_output_bang();
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
        this->gen_03_h_window_square_init();
        this->gen_03_h_window_saw_init();
        this->gen_03_h_window_delta_init();
        this->gen_03_h_window_phase_init();
        this->gen_03_h_grain_count_init();
        this->gen_03_h_grain_inc_init();
        this->gen_03_h_grain_pan_r_init();
        this->gen_03_h_grain_pan_l_init();
        this->gen_03_h_grain_size_init();
        this->gen_03_h_grain_amp_init();
        this->gen_03_h_is_scheduled_init();
        this->gen_03_noise_4_init();
        this->gen_03_noise_7_init();
        this->gen_03_noise_10_init();
        this->gen_03_noise_12_init();
        this->gen_03_noise_16_init();
        this->gen_03_noise_18_init();
        this->gen_03_noise_24_init();
        this->gen_03_noise_30_init();
        this->gen_03_noise_32_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    
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
    
        {
            this->scheduleParamInit(10, 0);
        }
    
        {
            this->scheduleParamInit(11, 0);
        }
    
        {
            this->scheduleParamInit(12, 0);
        }
    }
    
    void allocateDataRefs() {
        this->gen_03_cycle_19_buffer->requestSize(16384, 1);
        this->gen_03_cycle_19_buffer->setSampleRate(this->sr);
        this->gen_03_cycle_21_buffer->requestSize(16384, 1);
        this->gen_03_cycle_21_buffer->setSampleRate(this->sr);
        this->gen_03_buf_arp_count = this->gen_03_buf_arp_count->allocateIfNeeded();
        this->gen_03_buf_sample_index = this->gen_03_buf_sample_index->allocateIfNeeded();
        this->gen_03_buf_note_count = this->gen_03_buf_note_count->allocateIfNeeded();
        this->gen_03_buf_notes_state = this->gen_03_buf_notes_state->allocateIfNeeded();
        this->gen_03_buf_window = this->gen_03_buf_window->allocateIfNeeded();
        this->gen_03_buf_source = this->gen_03_buf_source->allocateIfNeeded();
        this->gen_03_cycle_19_buffer = this->gen_03_cycle_19_buffer->allocateIfNeeded();
        this->gen_03_cycle_21_buffer = this->gen_03_cycle_21_buffer->allocateIfNeeded();
    }
    
    void voice_01_mutestatus_set(number ) {}
    
    void voice_01_mutein_list_set(const list& v) {
        if (v[0] == this->voice() || v[0] == 0) {
            this->voice_01_mutestatus_set(v[1]);
        }
    }
    
    void voice_01_activevoices_set(number ) {}
    
    void voice_01_muteout_set(const list& v) {
        this->getPatcher()->updateTime(this->_currentTime);
        this->getPatcher()->p_07_mute_set(v);
    }
    
    void voice_01_mute_number_set(number v) {
        this->voice_01_mute_number = v;
        this->voice_01_muteout_set({this->voice(), v});
    }
    
    void trigger_02_out2_set(number v) {
        this->voice_01_mute_number_set(v);
    }
    
    void click_01_click_number_set(number v) {
        for (SampleIndex i = (SampleIndex)(this->click_01_lastclick + 1); i < this->sampleOffsetIntoNextAudioBuffer; i++) {
            this->click_01_buf[(Index)i] = 0;
        }
    
        this->click_01_lastclick = this->sampleOffsetIntoNextAudioBuffer;
        this->click_01_buf[(Index)this->click_01_lastclick] = v;
    }
    
    void click_01_click_bang_bang() {
        this->click_01_click_number_set(1);
    }
    
    void trigger_02_out1_bang() {
        this->click_01_click_bang_bang();
    }
    
    void trigger_02_input_bang_bang() {
        this->trigger_02_out2_set(0);
        this->trigger_02_out1_bang();
    }
    
    void eventinlet_08_out1_bang_bang() {
        this->trigger_02_input_bang_bang();
    }
    
    static number param_08_value_constrain(number v) {
        v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_position_spread_min_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_position_spread_min_set(number v) {
        v = this->gen_03_position_spread_min_constrain(v);
        this->gen_03_position_spread_min = v;
    }
    
    void mstosamps_01_out1_set(number v) {
        this->gen_03_position_spread_min_set(v);
    }
    
    void mstosamps_01_ms_set(number ms) {
        this->mstosamps_01_ms = ms;
    
        {
            this->mstosamps_01_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    static number param_09_value_constrain(number v) {
        v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_position_spread_max_constrain(number v) {
        if (v < 0)
            v = 0;
    
        return v;
    }
    
    void gen_03_position_spread_max_set(number v) {
        v = this->gen_03_position_spread_max_constrain(v);
        this->gen_03_position_spread_max = v;
    }
    
    void mstosamps_02_out1_set(number v) {
        this->gen_03_position_spread_max_set(v);
    }
    
    void mstosamps_02_ms_set(number ms) {
        this->mstosamps_02_ms = ms;
    
        {
            this->mstosamps_02_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    static number param_10_value_constrain(number v) {
        v = (v > 10000 ? 10000 : (v < 0.00001 ? 0.00001 : v));
        return v;
    }
    
    void gen_03_grain_size_min_set(number v) {
        this->gen_03_grain_size_min = v;
    }
    
    void mstosamps_03_out1_set(number v) {
        this->gen_03_grain_size_min_set(v);
    }
    
    void mstosamps_03_ms_set(number ms) {
        this->mstosamps_03_ms = ms;
    
        {
            this->mstosamps_03_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    static number param_11_value_constrain(number v) {
        v = (v > 10000 ? 10000 : (v < 0.00001 ? 0.00001 : v));
        return v;
    }
    
    void gen_03_grain_size_max_set(number v) {
        this->gen_03_grain_size_max = v;
    }
    
    void mstosamps_04_out1_set(number v) {
        this->gen_03_grain_size_max_set(v);
    }
    
    void mstosamps_04_ms_set(number ms) {
        this->mstosamps_04_ms = ms;
    
        {
            this->mstosamps_04_out1_set(ms * this->sr * 0.001);
            return;
        }
    }
    
    static number param_12_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_window_saw_min_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_saw_min_set(number v) {
        v = this->gen_03_window_saw_min_constrain(v);
        this->gen_03_window_saw_min = v;
    }
    
    static number param_13_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_window_saw_max_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_saw_max_set(number v) {
        v = this->gen_03_window_saw_max_constrain(v);
        this->gen_03_window_saw_max = v;
    }
    
    static number param_14_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_window_square_min_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_square_min_set(number v) {
        v = this->gen_03_window_square_min_constrain(v);
        this->gen_03_window_square_min = v;
    }
    
    static number param_15_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_window_square_max_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_window_square_max_set(number v) {
        v = this->gen_03_window_square_max_constrain(v);
        this->gen_03_window_square_max = v;
    }
    
    static number param_16_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_grain_reverse_prob_constrain(number v) {
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
    
    static number param_17_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_stereo_spread_constrain(number v) {
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
    
    static number param_18_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    static number gen_03_grain_amp_spread_constrain(number v) {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_03_grain_amp_spread_set(number v) {
        v = this->gen_03_grain_amp_spread_constrain(v);
        this->gen_03_grain_amp_spread = v;
    }
    
    static number param_19_value_constrain(number v) {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    
        {
            number oneStep = (number)1 / (number)1;
            number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
            number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
            v = numberOfSteps * oneStep;
        }
    
        return v;
    }
    
    void gen_03_arp_mode_set(number v) {
        this->gen_03_arp_mode = v;
    }
    
    static number param_20_value_constrain(number v) {
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
    
    void trigger_02_input_number_set(number v) {
        RNBO_UNUSED(v);
        this->trigger_02_out2_set(0);
        this->trigger_02_out1_bang();
    }
    
    void trigger_02_input_list_set(const list& v) {
        RNBO_UNUSED(v);
        this->trigger_02_out2_set(0);
        this->trigger_02_out1_bang();
    }
    
    void voice_01_mute_bang_bang() {
        this->voice_01_muteout_set({this->voice(), 1});
    }
    
    void voice_01_noteNumber_set(number ) {}
    
    void gen_03_voice_index_set(number v) {
        this->gen_03_voice_index = v;
    }
    
    void voice_01_voicenumber_set(number v) {
        this->gen_03_voice_index_set(v);
    }
    
    void voice_01_voicebang_bang() {
        this->voice_01_noteNumber_set(this->notenumber());
        this->voice_01_voicenumber_set(this->voice());
    }
    
    void loadbang_01_output_bang() {
        this->voice_01_mute_bang_bang();
        this->voice_01_voicebang_bang();
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
        number arp_mode,
        number window_square_max,
        number window_square_min,
        number window_saw_max,
        number window_saw_min,
        number grain_reverse_prob,
        number pitch_spread_ratio,
        number stereo_spread,
        number grain_amp_spread,
        number grain_size_max,
        number grain_size_min,
        number position_spread_max,
        number position_spread_min,
        number voice_index,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        Index n
    ) {
        RNBO_UNUSED(voice_index);
        auto __gen_03_h_window_delta_value = this->gen_03_h_window_delta_value;
        auto __gen_03_h_window_phase_value = this->gen_03_h_window_phase_value;
        auto __gen_03_h_window_square_value = this->gen_03_h_window_square_value;
        auto __gen_03_h_window_saw_value = this->gen_03_h_window_saw_value;
        auto __gen_03_h_grain_count_value = this->gen_03_h_grain_count_value;
        auto __gen_03_h_grain_inc_value = this->gen_03_h_grain_inc_value;
        auto __gen_03_h_grain_pan_r_value = this->gen_03_h_grain_pan_r_value;
        auto __gen_03_h_grain_pan_l_value = this->gen_03_h_grain_pan_l_value;
        auto __gen_03_h_grain_size_value = this->gen_03_h_grain_size_value;
        auto __gen_03_h_grain_amp_value = this->gen_03_h_grain_amp_value;
        auto __gen_03_h_is_scheduled_value = this->gen_03_h_is_scheduled_value;
        Index i;
    
        for (i = 0; i < n; i++) {
            number peek_1 = 0;
            number peek_2 = 0;
            auto result_0 = this->peek_default(this->gen_03_buf_note_count, 0, 0);
            peek_2 = result_0[1];
            peek_1 = result_0[0];
    
            if ((bool)(in1[(Index)i]) && __gen_03_h_is_scheduled_value == 0 && peek_1 > 0) {
                number peek_3 = 0;
                number peek_4 = 0;
                auto result_1 = this->peek_default(this->gen_03_buf_note_count, 0, 0);
                peek_4 = result_1[1];
                peek_3 = result_1[0];
                number peek_5 = 0;
                number peek_6 = 0;
                auto result_2 = this->peek_default(this->gen_03_buf_arp_count, 0, 0);
                peek_6 = result_2[1];
                peek_5 = result_2[0];
                number unipolarNoise_3 = 0;
    
                {
                    unipolarNoise_3 = (this->gen_03_noise_4_next() + 1) * 0.5;
                }
    
                number note_index_5 = (arp_mode == 0 ? this->intnum(peek_3 * unipolarNoise_3) : peek_5);
                number unipolarNoise_6 = 0;
    
                {
                    unipolarNoise_6 = (this->gen_03_noise_7_next() + 1) * 0.5;
                }
    
                number position_offset_8 = unipolarNoise_6 * (position_spread_max - position_spread_min) + position_spread_min;
                number unipolarNoise_9 = 0;
    
                {
                    unipolarNoise_9 = (this->gen_03_noise_10_next() + 1) * 0.5;
                }
    
                number pitch_spread_11 = unipolarNoise_9 * (pitch_spread_ratio - ((pitch_spread_ratio == 0. ? 0. : (number)1 / pitch_spread_ratio))) + ((pitch_spread_ratio == 0. ? 0. : (number)1 / pitch_spread_ratio));
                number pan_13 = stereo_spread * this->gen_03_noise_12_next() * 0.125 + 0.125;
                number peek_7 = 0;
                number peek_8 = 0;
                auto result_14 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 1);
                peek_8 = result_14[1];
                peek_7 = result_14[0];
                number unipolarNoise_15 = 0;
    
                {
                    unipolarNoise_15 = (this->gen_03_noise_16_next() + 1) * 0.5;
                }
    
                __gen_03_h_grain_amp_value = (1 - unipolarNoise_15 * grain_amp_spread) * peek_7;
                number unipolarNoise_17 = 0;
    
                {
                    unipolarNoise_17 = (this->gen_03_noise_18_next() + 1) * 0.5;
                }
    
                __gen_03_h_grain_size_value = unipolarNoise_17 * (grain_size_max - grain_size_min) + grain_size_min;
                array<number, 2> result_20 = this->gen_03_cycle_19_next(pan_13, 0);
                __gen_03_h_grain_pan_l_value = result_20[0];
                array<number, 2> result_22 = this->gen_03_cycle_21_next(pan_13 + 0.75, 0);
                __gen_03_h_grain_pan_r_value = result_22[0];
                number unipolarNoise_23 = 0;
    
                {
                    unipolarNoise_23 = (this->gen_03_noise_24_next() + 1) * 0.5;
                }
    
                if (grain_reverse_prob <= unipolarNoise_23) {
                    number peek_9 = 0;
                    number peek_10 = 0;
                    auto result_25 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 2);
                    peek_10 = result_25[1];
                    peek_9 = result_25[0];
                    __gen_03_h_grain_inc_value = peek_9 * pitch_spread_11;
                    number peek_11 = 0;
                    number peek_12 = 0;
                    auto result_26 = this->peek_default(this->gen_03_buf_sample_index, 0, 0);
                    peek_12 = result_26[1];
                    peek_11 = result_26[0];
                    __gen_03_h_grain_count_value = peek_11 - __gen_03_h_grain_size_value - position_offset_8;
                } else {
                    number peek_13 = 0;
                    number peek_14 = 0;
                    auto result_27 = this->peek_default(this->gen_03_buf_notes_state, note_index_5, 2);
                    peek_14 = result_27[1];
                    peek_13 = result_27[0];
                    __gen_03_h_grain_inc_value = -peek_13 * pitch_spread_11;
                    number peek_15 = 0;
                    number peek_16 = 0;
                    auto result_28 = this->peek_default(this->gen_03_buf_sample_index, 0, 0);
                    peek_16 = result_28[1];
                    peek_15 = result_28[0];
                    __gen_03_h_grain_count_value = peek_15 - position_offset_8;
                }
    
                number unipolarNoise_29 = 0;
    
                {
                    unipolarNoise_29 = (this->gen_03_noise_30_next() + 1) * 0.5;
                }
    
                __gen_03_h_window_saw_value = unipolarNoise_29 * (window_saw_max - window_saw_min) + window_saw_min;
                number unipolarNoise_31 = 0;
    
                {
                    unipolarNoise_31 = (this->gen_03_noise_32_next() + 1) * 0.5;
                }
    
                __gen_03_h_window_square_value = unipolarNoise_31 * (window_square_max - window_square_min) + window_square_min;
                __gen_03_h_window_phase_value = 0;
                __gen_03_h_window_delta_value = (__gen_03_h_grain_size_value == 0. ? 0. : (number)1 / __gen_03_h_grain_size_value);
                __gen_03_h_is_scheduled_value = 1;
            }
    
            number yL_33 = 0;
            number yR_34 = 0;
    
            if (__gen_03_h_is_scheduled_value == 1) {
                number phaseDistortion_35 = 0;
    
                {
                    auto square_38 = __gen_03_h_window_square_value;
                    auto saw_37 = __gen_03_h_window_saw_value;
                    auto x_36 = __gen_03_h_window_phase_value;
                    number y_39 = x_36;
    
                    if (saw_37 != 0.5) {
                        y_39 = (y_39 < saw_37 ? this->scale(y_39, 0, saw_37, 0, 0.5, 1) : this->scale(y_39, saw_37, 1, 0.5, 1, 1));
                    }
    
                    if (square_38 != 0) {
                        number tmp_40 = (1 - square_38) * 0.5;
    
                        if (y_39 < tmp_40) {
                            y_39 = this->scale(y_39, 0, tmp_40, 0, 0.5, 1);
                        } else if (y_39 > 1 - tmp_40) {
                            y_39 = this->scale(y_39, 1 - tmp_40, 1, 0.5, 1, 1);
                        } else {
                            y_39 = 0.5;
                        }
                    }
    
                    phaseDistortion_35 = y_39;
                }
    
                number p_41 = phaseDistortion_35;
                number w = 0;
                auto result_42 = this->sample_default(this->gen_03_buf_window, p_41, 0);
                w = result_42[0];
                number peek_17 = 0;
                number peek_18 = 0;
                auto result_43 = this->peek_interp_linear(this->gen_03_buf_source, __gen_03_h_grain_count_value, 0);
                peek_18 = result_43[1];
                peek_17 = result_43[0];
                yL_33 = peek_17 * __gen_03_h_grain_amp_value * __gen_03_h_grain_pan_l_value * w;
                number peek_19 = 0;
                number peek_20 = 0;
                auto result_44 = this->peek_interp_linear(this->gen_03_buf_source, __gen_03_h_grain_count_value, 1);
                peek_20 = result_44[1];
                peek_19 = result_44[0];
                yR_34 = peek_19 * __gen_03_h_grain_amp_value * __gen_03_h_grain_pan_r_value * w;
                __gen_03_h_window_phase_value = __gen_03_h_window_phase_value + __gen_03_h_window_delta_value;
                __gen_03_h_grain_count_value = __gen_03_h_grain_count_value + __gen_03_h_grain_inc_value;
                __gen_03_h_grain_count_value = this->wrap(__gen_03_h_grain_count_value, 0, this->dim(this->gen_03_buf_source));
    
                if (__gen_03_h_window_phase_value >= 1) {
                    __gen_03_h_is_scheduled_value = 0;
                }
            }
    
            number expr_21_45 = yL_33;
            number expr_22_46 = yR_34;
            number expr_23_47 = __gen_03_h_is_scheduled_value;
            out3[(Index)i] = expr_23_47;
            out1[(Index)i] = expr_21_45;
            out2[(Index)i] = expr_22_46;
        }
    
        this->gen_03_h_is_scheduled_value = __gen_03_h_is_scheduled_value;
        this->gen_03_h_grain_amp_value = __gen_03_h_grain_amp_value;
        this->gen_03_h_grain_size_value = __gen_03_h_grain_size_value;
        this->gen_03_h_grain_pan_l_value = __gen_03_h_grain_pan_l_value;
        this->gen_03_h_grain_pan_r_value = __gen_03_h_grain_pan_r_value;
        this->gen_03_h_grain_inc_value = __gen_03_h_grain_inc_value;
        this->gen_03_h_grain_count_value = __gen_03_h_grain_count_value;
        this->gen_03_h_window_saw_value = __gen_03_h_window_saw_value;
        this->gen_03_h_window_square_value = __gen_03_h_window_square_value;
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
                    this->getEngine()->scheduleClockEvent(this, -1584063977, this->sampsToMs(i) + this->_currentTime);;
                    __edge_02_currentState = 0;
                }
            } else {
                if (input[(Index)i] != 0.) {
                    this->getEngine()->scheduleClockEvent(this, -611950441, this->sampsToMs(i) + this->_currentTime);;
                    __edge_02_currentState = 1;
                }
            }
        }
    
        this->edge_02_currentState = __edge_02_currentState;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number gen_03_h_window_square_getvalue() {
        return this->gen_03_h_window_square_value;
    }
    
    void gen_03_h_window_square_setvalue(number val) {
        this->gen_03_h_window_square_value = val;
    }
    
    void gen_03_h_window_square_reset() {
        this->gen_03_h_window_square_value = 0;
    }
    
    void gen_03_h_window_square_init() {
        this->gen_03_h_window_square_value = 0;
    }
    
    number gen_03_h_window_saw_getvalue() {
        return this->gen_03_h_window_saw_value;
    }
    
    void gen_03_h_window_saw_setvalue(number val) {
        this->gen_03_h_window_saw_value = val;
    }
    
    void gen_03_h_window_saw_reset() {
        this->gen_03_h_window_saw_value = 0;
    }
    
    void gen_03_h_window_saw_init() {
        this->gen_03_h_window_saw_value = 0;
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
    
    void gen_03_noise_7_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_7_state
        );
    }
    
    void gen_03_noise_7_init() {
        this->gen_03_noise_7_reset();
    }
    
    void gen_03_noise_7_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_7_state);
    }
    
    number gen_03_noise_7_next() {
        return xoshiro_next(this->gen_03_noise_7_state);
    }
    
    void gen_03_noise_10_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_10_state
        );
    }
    
    void gen_03_noise_10_init() {
        this->gen_03_noise_10_reset();
    }
    
    void gen_03_noise_10_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_10_state);
    }
    
    number gen_03_noise_10_next() {
        return xoshiro_next(this->gen_03_noise_10_state);
    }
    
    void gen_03_noise_12_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_12_state
        );
    }
    
    void gen_03_noise_12_init() {
        this->gen_03_noise_12_reset();
    }
    
    void gen_03_noise_12_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_12_state);
    }
    
    number gen_03_noise_12_next() {
        return xoshiro_next(this->gen_03_noise_12_state);
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
    
    void gen_03_noise_18_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_18_state
        );
    }
    
    void gen_03_noise_18_init() {
        this->gen_03_noise_18_reset();
    }
    
    void gen_03_noise_18_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_18_state);
    }
    
    number gen_03_noise_18_next() {
        return xoshiro_next(this->gen_03_noise_18_state);
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
    
    number gen_03_cycle_21_ph_next(number freq, number reset) {
        RNBO_UNUSED(reset);
    
        {
            {}
        }
    
        number pincr = freq * this->gen_03_cycle_21_ph_conv;
    
        if (this->gen_03_cycle_21_ph_currentPhase < 0.)
            this->gen_03_cycle_21_ph_currentPhase = 1. + this->gen_03_cycle_21_ph_currentPhase;
    
        if (this->gen_03_cycle_21_ph_currentPhase > 1.)
            this->gen_03_cycle_21_ph_currentPhase = this->gen_03_cycle_21_ph_currentPhase - 1.;
    
        number tmp = this->gen_03_cycle_21_ph_currentPhase;
        this->gen_03_cycle_21_ph_currentPhase += pincr;
        return tmp;
    }
    
    void gen_03_cycle_21_ph_reset() {
        this->gen_03_cycle_21_ph_currentPhase = 0;
    }
    
    void gen_03_cycle_21_ph_dspsetup() {
        this->gen_03_cycle_21_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    array<number, 2> gen_03_cycle_21_next(number frequency, number phase_offset) {
        RNBO_UNUSED(phase_offset);
    
        {
            uint32_t uint_phase;
    
            {
                uint_phase = uint32_trunc(frequency * 4294967296.0);
            }
    
            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = this->gen_03_cycle_21_buffer[(Index)idx];
            number y1 = this->gen_03_cycle_21_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);
            return {y, uint_phase * 0.232830643653869629e-9};
        }
    }
    
    void gen_03_cycle_21_dspsetup() {
        this->gen_03_cycle_21_phasei = 0;
        this->gen_03_cycle_21_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
        this->gen_03_cycle_21_wrap = (long)(this->gen_03_cycle_21_buffer->getSize()) - 1;
    }
    
    void gen_03_cycle_21_reset() {
        this->gen_03_cycle_21_phasei = 0;
    }
    
    void gen_03_cycle_21_bufferUpdated() {
        this->gen_03_cycle_21_wrap = (long)(this->gen_03_cycle_21_buffer->getSize()) - 1;
    }
    
    void gen_03_noise_24_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_24_state
        );
    }
    
    void gen_03_noise_24_init() {
        this->gen_03_noise_24_reset();
    }
    
    void gen_03_noise_24_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_24_state);
    }
    
    number gen_03_noise_24_next() {
        return xoshiro_next(this->gen_03_noise_24_state);
    }
    
    void gen_03_noise_30_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_30_state
        );
    }
    
    void gen_03_noise_30_init() {
        this->gen_03_noise_30_reset();
    }
    
    void gen_03_noise_30_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_30_state);
    }
    
    number gen_03_noise_30_next() {
        return xoshiro_next(this->gen_03_noise_30_state);
    }
    
    void gen_03_noise_32_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_03_noise_32_state
        );
    }
    
    void gen_03_noise_32_init() {
        this->gen_03_noise_32_reset();
    }
    
    void gen_03_noise_32_seed(number v) {
        xoshiro_reset(v, this->gen_03_noise_32_state);
    }
    
    number gen_03_noise_32_next() {
        return xoshiro_next(this->gen_03_noise_32_state);
    }
    
    void gen_03_dspsetup(bool force) {
        if ((bool)(this->gen_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->gen_03_setupDone = true;
        this->gen_03_cycle_19_ph_dspsetup();
        this->gen_03_cycle_19_dspsetup();
        this->gen_03_cycle_21_ph_dspsetup();
        this->gen_03_cycle_21_dspsetup();
    }
    
    void param_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_08_value;
    }
    
    void param_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_08_value_set(preset["value"]);
    }
    
    void edge_02_dspsetup(bool force) {
        if ((bool)(this->edge_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->edge_02_setupDone = true;
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
    
    void param_20_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_20_value;
    }
    
    void param_20_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_20_value_set(preset["value"]);
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
        gen_03_arp_mode = 0;
        gen_03_window_square_max = 0;
        gen_03_window_square_min = 0;
        gen_03_window_saw_max = 0.5;
        gen_03_window_saw_min = 0.5;
        gen_03_grain_reverse_prob = 0;
        gen_03_pitch_spread_ratio = 1;
        gen_03_stereo_spread = 0;
        gen_03_grain_amp_spread = 0;
        gen_03_grain_size_max = 480;
        gen_03_grain_size_min = 480;
        gen_03_position_spread_max = 0;
        gen_03_position_spread_min = 0;
        gen_03_voice_index = 0;
        mstosamps_01_ms = 0;
        param_08_value = 0;
        mstosamps_02_ms = 0;
        param_09_value = 100;
        mstosamps_03_ms = 0;
        param_10_value = 50;
        voice_01_mute_number = 0;
        mstosamps_04_ms = 0;
        param_11_value = 50;
        param_12_value = 0.5;
        param_13_value = 0.5;
        param_14_value = 0;
        param_15_value = 0;
        param_16_value = 0;
        param_17_value = 0;
        param_18_value = 0;
        param_19_value = 0;
        expr_03_in1 = 0;
        expr_03_out1 = 0;
        param_20_value = 0;
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
        click_01_lastclick = -1;
        click_01_buf = nullptr;
        gen_03_h_window_square_value = 0;
        gen_03_h_window_saw_value = 0;
        gen_03_h_window_delta_value = 0;
        gen_03_h_window_phase_value = 0;
        gen_03_h_grain_count_value = 0;
        gen_03_h_grain_inc_value = 0;
        gen_03_h_grain_pan_r_value = 0;
        gen_03_h_grain_pan_l_value = 0;
        gen_03_h_grain_size_value = 0;
        gen_03_h_grain_amp_value = 0;
        gen_03_h_is_scheduled_value = 0;
        gen_03_cycle_19_ph_currentPhase = 0;
        gen_03_cycle_19_ph_conv = 0;
        gen_03_cycle_19_wrap = 0;
        gen_03_cycle_21_ph_currentPhase = 0;
        gen_03_cycle_21_ph_conv = 0;
        gen_03_cycle_21_wrap = 0;
        gen_03_setupDone = false;
        param_08_lastValue = 0;
        edge_02_setupDone = false;
        param_09_lastValue = 0;
        param_10_lastValue = 0;
        param_11_lastValue = 0;
        param_12_lastValue = 0;
        param_13_lastValue = 0;
        param_14_lastValue = 0;
        param_15_lastValue = 0;
        param_16_lastValue = 0;
        param_17_lastValue = 0;
        param_18_lastValue = 0;
        param_19_lastValue = 0;
        param_20_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number gen_03_in1;
        number gen_03_arp_mode;
        number gen_03_window_square_max;
        number gen_03_window_square_min;
        number gen_03_window_saw_max;
        number gen_03_window_saw_min;
        number gen_03_grain_reverse_prob;
        number gen_03_pitch_spread_ratio;
        number gen_03_stereo_spread;
        number gen_03_grain_amp_spread;
        number gen_03_grain_size_max;
        number gen_03_grain_size_min;
        number gen_03_position_spread_max;
        number gen_03_position_spread_min;
        number gen_03_voice_index;
        number mstosamps_01_ms;
        number param_08_value;
        number mstosamps_02_ms;
        number param_09_value;
        number mstosamps_03_ms;
        number param_10_value;
        number voice_01_mute_number;
        number mstosamps_04_ms;
        number param_11_value;
        number param_12_value;
        number param_13_value;
        number param_14_value;
        number param_15_value;
        number param_16_value;
        number param_17_value;
        number param_18_value;
        number param_19_value;
        number expr_03_in1;
        number expr_03_out1;
        number param_20_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        SampleIndex click_01_lastclick;
        signal click_01_buf;
        number gen_03_h_window_square_value;
        number gen_03_h_window_saw_value;
        number gen_03_h_window_delta_value;
        number gen_03_h_window_phase_value;
        number gen_03_h_grain_count_value;
        number gen_03_h_grain_inc_value;
        number gen_03_h_grain_pan_r_value;
        number gen_03_h_grain_pan_l_value;
        number gen_03_h_grain_size_value;
        number gen_03_h_grain_amp_value;
        number gen_03_h_is_scheduled_value;
        Float64BufferRef gen_03_buf_arp_count;
        Float64BufferRef gen_03_buf_sample_index;
        Float64BufferRef gen_03_buf_note_count;
        Float64BufferRef gen_03_buf_notes_state;
        Float64BufferRef gen_03_buf_window;
        Float64BufferRef gen_03_buf_source;
        UInt gen_03_noise_4_state[4] = { };
        UInt gen_03_noise_7_state[4] = { };
        UInt gen_03_noise_10_state[4] = { };
        UInt gen_03_noise_12_state[4] = { };
        UInt gen_03_noise_16_state[4] = { };
        UInt gen_03_noise_18_state[4] = { };
        number gen_03_cycle_19_ph_currentPhase;
        number gen_03_cycle_19_ph_conv;
        Float64BufferRef gen_03_cycle_19_buffer;
        long gen_03_cycle_19_wrap;
        uint32_t gen_03_cycle_19_phasei;
        SampleValue gen_03_cycle_19_f2i;
        number gen_03_cycle_21_ph_currentPhase;
        number gen_03_cycle_21_ph_conv;
        Float64BufferRef gen_03_cycle_21_buffer;
        long gen_03_cycle_21_wrap;
        uint32_t gen_03_cycle_21_phasei;
        SampleValue gen_03_cycle_21_f2i;
        UInt gen_03_noise_24_state[4] = { };
        UInt gen_03_noise_30_state[4] = { };
        UInt gen_03_noise_32_state[4] = { };
        bool gen_03_setupDone;
        number param_08_lastValue;
        number edge_02_currentState;
        bool edge_02_setupDone;
        number param_09_lastValue;
        number param_10_lastValue;
        number param_11_lastValue;
        number param_12_lastValue;
        number param_13_lastValue;
        number param_14_lastValue;
        number param_15_lastValue;
        number param_16_lastValue;
        number param_17_lastValue;
        number param_18_lastValue;
        number param_19_lastValue;
        number param_20_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_16 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_16()
    {
    }
    
    ~RNBOSubpatcher_16()
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
                    value = value * (1. - overdub) + currentValue * overdub;
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
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
    
        if (index == 4) {
            this->codebox_03_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        }
    
        if (index == 3) {
            this->codebox_03_note_count = new Float64Buffer(this->getPatcher()->note_count);
        }
    
        if (index == 2) {
            this->codebox_03_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
        }
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->codebox_03_notes_state = new Float64Buffer(this->getPatcher()->notes_state);
        this->codebox_03_note_count = new Float64Buffer(this->getPatcher()->note_count);
        this->codebox_03_arp_count = new Float64Buffer(this->getPatcher()->arp_count);
    }
    
    protected:
    
    void eventinlet_09_out1_bang_bang() {
        this->codebox_03_in1_bang();
    }
    
    void eventinlet_09_out1_list_set(const list& v) {
        {
            if (v->length > 1)
                this->codebox_03_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->codebox_03_in1_set(converted);
        }
    }
    
    void eventinlet_10_out1_bang_bang() {
        this->codebox_03_in2_bang();
    }
    
    void eventinlet_10_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->codebox_03_in2_set(converted);
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
        this->codebox_03_notes_state = this->codebox_03_notes_state->allocateIfNeeded();
        this->codebox_03_note_count = this->codebox_03_note_count->allocateIfNeeded();
        this->codebox_03_arp_count = this->codebox_03_arp_count->allocateIfNeeded();
    }
    
    void codebox_03_in2_set(number v) {
        this->codebox_03_in2 = v;
    }
    
    void eventinlet_10_out1_number_set(number v) {
        this->codebox_03_in2_set(v);
    }
    
    void codebox_03_in1_set(number in1) {
        this->codebox_03_in1 = in1;
        number velocity = this->codebox_03_in2;
        number pitch = this->codebox_03_in1;
    
        if (velocity != 0) {
            number index_to_write = this->codebox_03_note_count->getSampleSafe(0, 0);
            number note_level = velocity * velocity / (number)16129;
            number freq_ratio = fixnan(rnbo_pow(2, (pitch - 60) / (number)12));
            this->poke_default(this->codebox_03_notes_state, pitch, index_to_write, 0, 0);//#map:_###_obj_###_:16
            this->poke_default(this->codebox_03_notes_state, note_level, index_to_write, 1, 0);//#map:_###_obj_###_:17
            this->poke_default(this->codebox_03_notes_state, freq_ratio, index_to_write, 2, 0);//#map:_###_obj_###_:18
            this->poke_default(this->codebox_03_note_count, index_to_write + 1, 0, 0, 0);//#map:_###_obj_###_:21
        } else {
            number index_to_erase = 0;
            number index_last_elm = this->codebox_03_note_count->getSampleSafe(0, 0) - 1;
    
            while (index_to_erase != index_last_elm) {
                number n = this->codebox_03_notes_state->getSampleSafe(0, index_to_erase);
    
                if (n == pitch)
                    break;//#map:_###_obj_###_:32;//#map:_###_obj_###_:32
    
                index_to_erase += 1;//#map:_###_obj_###_:33
            }
    
            while (index_to_erase != index_last_elm) {
                number right_index = index_to_erase + 1;
                number right_pitch = this->codebox_03_notes_state->getSampleSafe(0, right_index);
                number right_level = this->codebox_03_notes_state->getSampleSafe(1, right_index);
                number right_ratio = this->codebox_03_notes_state->getSampleSafe(2, right_index);
                this->poke_default(this->codebox_03_notes_state, right_pitch, index_to_erase, 0, 0);//#map:_###_obj_###_:44
                this->poke_default(this->codebox_03_notes_state, right_level, index_to_erase, 1, 0);//#map:_###_obj_###_:45
                this->poke_default(this->codebox_03_notes_state, right_ratio, index_to_erase, 2, 0);//#map:_###_obj_###_:46
                index_to_erase += 1;//#map:_###_obj_###_:48
            }
    
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 0, 0);//#map:_###_obj_###_:52
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 1, 0);//#map:_###_obj_###_:53
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 2, 0);//#map:_###_obj_###_:54
            this->poke_default(this->codebox_03_note_count, index_last_elm, 0, 0, 0);//#map:_###_obj_###_:58
    
            if (this->codebox_03_note_count->getSampleSafe(0, 0) == 0) {
                this->poke_default(this->codebox_03_arp_count, -1, 0, 0, 0);//#map:_###_obj_###_:63
            }//#map:_###_obj_###_:61
        }//#map:midi_process/codebox_obj-11:8
    }
    
    void eventinlet_09_out1_number_set(number v) {
        this->codebox_03_in1_set(v);
    }
    
    void codebox_03_in1_bang() {
        number velocity = this->codebox_03_in2;
        number pitch = this->codebox_03_in1;
    
        if (velocity != 0) {
            number index_to_write = this->codebox_03_note_count->getSampleSafe(0, 0);
            number note_level = velocity * velocity / (number)16129;
            number freq_ratio = fixnan(rnbo_pow(2, (pitch - 60) / (number)12));
            this->poke_default(this->codebox_03_notes_state, pitch, index_to_write, 0, 0);//#map:_###_obj_###_:16
            this->poke_default(this->codebox_03_notes_state, note_level, index_to_write, 1, 0);//#map:_###_obj_###_:17
            this->poke_default(this->codebox_03_notes_state, freq_ratio, index_to_write, 2, 0);//#map:_###_obj_###_:18
            this->poke_default(this->codebox_03_note_count, index_to_write + 1, 0, 0, 0);//#map:_###_obj_###_:21
        } else {
            number index_to_erase = 0;
            number index_last_elm = this->codebox_03_note_count->getSampleSafe(0, 0) - 1;
    
            while (index_to_erase != index_last_elm) {
                number n = this->codebox_03_notes_state->getSampleSafe(0, index_to_erase);
    
                if (n == pitch)
                    break;//#map:_###_obj_###_:32;//#map:_###_obj_###_:32
    
                index_to_erase += 1;//#map:_###_obj_###_:33
            }
    
            while (index_to_erase != index_last_elm) {
                number right_index = index_to_erase + 1;
                number right_pitch = this->codebox_03_notes_state->getSampleSafe(0, right_index);
                number right_level = this->codebox_03_notes_state->getSampleSafe(1, right_index);
                number right_ratio = this->codebox_03_notes_state->getSampleSafe(2, right_index);
                this->poke_default(this->codebox_03_notes_state, right_pitch, index_to_erase, 0, 0);//#map:_###_obj_###_:44
                this->poke_default(this->codebox_03_notes_state, right_level, index_to_erase, 1, 0);//#map:_###_obj_###_:45
                this->poke_default(this->codebox_03_notes_state, right_ratio, index_to_erase, 2, 0);//#map:_###_obj_###_:46
                index_to_erase += 1;//#map:_###_obj_###_:48
            }
    
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 0, 0);//#map:_###_obj_###_:52
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 1, 0);//#map:_###_obj_###_:53
            this->poke_default(this->codebox_03_notes_state, 0, index_to_erase, 2, 0);//#map:_###_obj_###_:54
            this->poke_default(this->codebox_03_note_count, index_last_elm, 0, 0, 0);//#map:_###_obj_###_:58
    
            if (this->codebox_03_note_count->getSampleSafe(0, 0) == 0) {
                this->poke_default(this->codebox_03_arp_count, -1, 0, 0, 0);//#map:_###_obj_###_:63
            }//#map:_###_obj_###_:61
        }//#map:midi_process/codebox_obj-11:8
    }
    
    void codebox_03_in2_bang() {}
    
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
        codebox_03_in1 = 0;
        codebox_03_in2 = 0;
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
    
        number codebox_03_in1;
        number codebox_03_in2;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float64BufferRef codebox_03_notes_state;
        Float64BufferRef codebox_03_note_count;
        Float64BufferRef codebox_03_arp_count;
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
    for (int i = 0; i < 1500; i++) {
        delete p_07[i];
    }
    delete this->p_08;
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

number samplerate() {
    return this->sr;
}

Index vectorsize() {
    return this->vs;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
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
    this->p_06_perform(n);
    this->p_07_perform(this->signals[0], this->signals[1], n);
    this->p_05_perform(this->signals[0], this->signals[1], this->signals[2], this->signals[3], n);
    this->signaladder_01_perform(this->signals[2], in1, this->signals[2], n);
    this->signaladder_02_perform(this->signals[3], in2, this->signals[3], n);
    this->p_04_perform(this->signals[2], this->signals[3], this->signals[4], this->signals[5], n);
    this->dspexpr_04_perform(this->signals[4], this->signals[0], this->dspexpr_04_in3, out1, n);
    this->dspexpr_05_perform(this->signals[5], this->signals[1], this->dspexpr_05_in3, out2, n);
    this->p_08_perform(n);
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
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    this->p_08->prepareToProcess(sampleRate, maxBlockSize, force);

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
        return addressOf(this->source);
        break;
        }
    case 1:
        {
        return addressOf(this->sample_index);
        break;
        }
    case 2:
        {
        return addressOf(this->arp_count);
        break;
        }
    case 3:
        {
        return addressOf(this->note_count);
        break;
        }
    case 4:
        {
        return addressOf(this->notes_state);
        break;
        }
    case 5:
        {
        return addressOf(this->window);
        break;
        }
    case 6:
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
    return 7;
}

void fillarp_count(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (number channel = 0; channel < buffer->getChannels(); channel++) {
        for (int index = 0; index < bufsize; index++) {
            number x = index / bufsize;
            number value = -1;
            buffer->setSample(channel, index, value);
        }
    }
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
    case 2:
        {
        this->fillarp_count(ref);
        break;
        }
    case 5:
        {
        this->fillwindow(ref);
        break;
        }
    case 6:
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
        this->data_06_buffer = new Float64Buffer(this->source);
        this->data_06_bufferUpdated();
    }

    if (index == 1) {
        this->data_02_buffer = new Float64Buffer(this->sample_index);
        this->data_02_bufferUpdated();
    }

    if (index == 2) {
        this->data_01_buffer = new Float64Buffer(this->arp_count);
        this->data_01_bufferUpdated();
    }

    if (index == 3) {
        this->data_04_buffer = new Float64Buffer(this->note_count);
        this->data_04_bufferUpdated();
    }

    if (index == 4) {
        this->data_03_buffer = new Float64Buffer(this->notes_state);
        this->data_03_bufferUpdated();
    }

    if (index == 5) {
        this->data_05_buffer = new Float64Buffer(this->window);
        this->data_05_bufferUpdated();
    }

    this->p_04->processDataViewUpdate(index, time);
    this->p_05->processDataViewUpdate(index, time);
    this->p_06->processDataViewUpdate(index, time);

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->processDataViewUpdate(index, time);
    }

    this->p_08->processDataViewUpdate(index, time);
}

void initialize() {
    this->source = initDataRef("source", true, nullptr, "data");
    this->sample_index = initDataRef("sample_index", true, nullptr, "data");
    this->arp_count = initDataRef("arp_count", true, nullptr, "data");
    this->note_count = initDataRef("note_count", true, nullptr, "data");
    this->notes_state = initDataRef("notes_state", true, nullptr, "data");
    this->window = initDataRef("window", true, nullptr, "data");
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->source->setIndex(0);
    this->data_06_buffer = new Float64Buffer(this->source);
    this->sample_index->setIndex(1);
    this->data_02_buffer = new Float64Buffer(this->sample_index);
    this->arp_count->setIndex(2);
    this->data_01_buffer = new Float64Buffer(this->arp_count);
    this->note_count->setIndex(3);
    this->data_04_buffer = new Float64Buffer(this->note_count);
    this->notes_state->setIndex(4);
    this->data_03_buffer = new Float64Buffer(this->notes_state);
    this->window->setIndex(5);
    this->data_05_buffer = new Float64Buffer(this->window);
    this->RNBODefaultSinus->setIndex(6);
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

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_04 = new RNBOSubpatcher_12();
    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    this->p_05 = new RNBOSubpatcher_13();
    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
    this->p_06 = new RNBOSubpatcher_14();
    this->p_06->setEngineAndPatcher(this->getEngine(), this);
    this->p_06->initialize();
    this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));

    for (Index i = 0; i < 1500; i++) {
        this->p_07[(Index)i] = new RNBOSubpatcher_15();
        this->p_07[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->p_07[(Index)i]->initialize();
        this->p_07[(Index)i]->setParameterOffset(this->getParameterOffset(this->p_07[0]));
        this->p_07[(Index)i]->setVoiceIndex(i + 1);
    }

    this->p_08 = new RNBOSubpatcher_16();
    this->p_08->setEngineAndPatcher(this->getEngine(), this);
    this->p_08->initialize();
    this->p_08->setParameterOffset(this->getParameterOffset(this->p_08));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_21_getPresetValue(getSubState(preset, "drywet"));
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "record"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "feedback"));
    this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "trigger"));

    for (Index i = 0; i < 1500; i++)
        this->p_07[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "cloud", i));

    this->p_08->getPreset(getSubState(getSubState(preset, "__sps"), "midi_process"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_21_setPresetValue(getSubState(preset, "drywet"));
    this->p_04->param_01_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "record"), "freeze"));

    this->p_05->param_02_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "frequency")
    );

    this->p_05->param_03_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "resonance")
    );

    this->p_05->param_04_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "amount")
    );

    this->p_05->param_05_setPresetValue(getSubState(getSubState(getSubState(preset, "__sps"), "feedback"), "type"));

    this->p_06->param_06_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "trigger"), "density")
    );

    this->p_06->param_07_setPresetValue(
        getSubState(getSubState(getSubState(preset, "__sps"), "trigger"), "probability")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_08_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "position_spread_min")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_09_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "position_spread_max")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_10_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "size_min")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_11_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "size_max")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_12_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_saw_min")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_13_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_saw_max")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_14_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_square_min")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_15_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "window_square_max")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_16_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "reverse_prob")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_17_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "stereo_spread")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_18_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "amp_spread")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_19_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "arp")
    );

    for (Index i0 = 0; i0 < 1500; i0++) this->p_07[i0]->param_20_setPresetValue(
        getSubState(getSubStateAt(getSubState(preset, "__sps"), "cloud", i0), "pitch_spread")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_04->processTempoEvent(time, tempo);
        this->p_05->processTempoEvent(time, tempo);
        this->p_06->processTempoEvent(time, tempo);

        for (Index i = 0; i < 1500; i++) {
            this->p_07[i]->processTempoEvent(time, tempo);
        }

        this->p_08->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_04->processTransportEvent(time, state);
        this->p_05->processTransportEvent(time, state);
        this->p_06->processTransportEvent(time, state);

        for (Index i = 0; i < 1500; i++) {
            this->p_07[i]->processTransportEvent(time, state);
        }

        this->p_08->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_04->processBeatTimeEvent(time, beattime);
        this->p_05->processBeatTimeEvent(time, beattime);
        this->p_06->processBeatTimeEvent(time, beattime);

        for (Index i = 0; i < 1500; i++) {
            this->p_07[i]->processBeatTimeEvent(time, beattime);
        }

        this->p_08->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_04->processTimeSignatureEvent(time, numerator, denominator);
        this->p_05->processTimeSignatureEvent(time, numerator, denominator);
        this->p_06->processTimeSignatureEvent(time, numerator, denominator);

        for (Index i = 0; i < 1500; i++) {
            this->p_07[i]->processTimeSignatureEvent(time, numerator, denominator);
        }

        this->p_08->processTimeSignatureEvent(time, numerator, denominator);
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_21_value_set(v);
        break;
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            this->p_04->setParameterValue(index, v, time);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            this->p_05->setParameterValue(index, v, time);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            this->p_06->setParameterValue(index, v, time);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters())
            this->p_07[0]->setPolyParameterValue((PatcherInterface**)this->p_07, index, v, time);

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            this->p_08->setParameterValue(index, v, time);

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
        return this->param_21_value;
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterValue(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterValue(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterValue(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters())
            return this->p_07[0]->getPolyParameterValue((PatcherInterface**)this->p_07, index);

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->getParameterValue(index);

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
    return 1 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07[0]->getNumParameters() + this->p_08->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "drywet";
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterName(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterName(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterName(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters()) {
            {
                return this->p_07[0]->getParameterName(index);
            }
        }

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "drywet";
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterId(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterId(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterId(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters()) {
            {
                return this->p_07[0]->getParameterId(index);
            }
        }

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->getParameterId(index);

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
        default:
            {
            index -= 1;

            if (index < this->p_04->getNumParameters())
                this->p_04->getParameterInfo(index, info);

            index -= this->p_04->getNumParameters();

            if (index < this->p_05->getNumParameters())
                this->p_05->getParameterInfo(index, info);

            index -= this->p_05->getNumParameters();

            if (index < this->p_06->getNumParameters())
                this->p_06->getParameterInfo(index, info);

            index -= this->p_06->getNumParameters();

            if (index < this->p_07[0]->getNumParameters()) {
                for (Index i = 0; i < 1500; i++) {
                    this->p_07[i]->getParameterInfo(index, info);
                }
            }

            index -= this->p_07[0]->getNumParameters();

            if (index < this->p_08->getNumParameters())
                this->p_08->getParameterInfo(index, info);

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
        return 1;

    if (subpatcher == this->p_05)
        return 1 + this->p_04->getNumParameters();

    if (subpatcher == this->p_06)
        return 1 + this->p_04->getNumParameters() + this->p_05->getNumParameters();

    if (subpatcher == this->p_07[0])
        return 1 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();

    if (subpatcher == this->p_08)
        return 1 + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07[0]->getNumParameters();

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
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertToNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertToNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertToNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters()) {
            {
                return this->p_07[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->convertToNormalizedParameterValue(index, value);

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
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertFromNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertFromNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertFromNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters()) {
            {
                return this->p_07[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_21_value_constrain(value);
        }
    default:
        {
        index -= 1;

        if (index < this->p_04->getNumParameters())
            return this->p_04->constrainParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->constrainParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->constrainParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07[0]->getNumParameters()) {
            {
                return this->p_07[0]->constrainParameterValue(index, value);
            }
        }

        index -= this->p_07[0]->getNumParameters();

        if (index < this->p_08->getNumParameters())
            return this->p_08->constrainParameterValue(index, value);

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

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->processNumMessage(tag, objectId, time, payload);
    }

    this->p_08->processNumMessage(tag, objectId, time, payload);
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

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->processListMessage(tag, objectId, time, payload);
    }

    this->p_08->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_04->processBangMessage(tag, objectId, time);
    this->p_05->processBangMessage(tag, objectId, time);
    this->p_06->processBangMessage(tag, objectId, time);

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->processBangMessage(tag, objectId, time);
    }

    this->p_08->processBangMessage(tag, objectId, time);
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

    auto subpatchResult_3 = this->p_07[0]->resolveTag(tag);

    if (subpatchResult_3)
        return subpatchResult_3;

    auto subpatchResult_4 = this->p_08->resolveTag(tag);

    if (subpatchResult_4)
        return subpatchResult_4;

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

void param_21_value_set(number v) {
    v = this->param_21_value_constrain(v);
    this->param_21_value = v;
    this->sendParameter(0, false);

    if (this->param_21_value != this->param_21_lastValue) {
        this->getEngine()->presetTouched();
        this->param_21_lastValue = this->param_21_value;
    }

    this->dspexpr_05_in3_set(v);
    this->dspexpr_04_in3_set(v);
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
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_04->allocateDataRefs();
    this->p_05->allocateDataRefs();
    this->p_06->allocateDataRefs();

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->allocateDataRefs();
    }

    this->p_08->allocateDataRefs();
    this->data_02_buffer->requestSize(1, 1);
    this->data_02_buffer->setSampleRate(this->sr);
    this->data_01_buffer->requestSize(1, 1);
    this->data_01_buffer->setSampleRate(this->sr);
    this->data_04_buffer->requestSize(1, 1);
    this->data_04_buffer->setSampleRate(this->sr);
    this->data_03_buffer->requestSize(128, 3);
    this->data_03_buffer->setSampleRate(this->sr);
    this->data_05_buffer->requestSize(65536, 1);
    this->data_05_buffer->setSampleRate(this->sr);
    this->data_06_buffer = this->data_06_buffer->allocateIfNeeded();

    if (this->source->hasRequestedSize()) {
        if (this->source->wantsFill())
            this->zeroDataRef(this->source);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->data_02_buffer = this->data_02_buffer->allocateIfNeeded();

    if (this->sample_index->hasRequestedSize()) {
        if (this->sample_index->wantsFill())
            this->zeroDataRef(this->sample_index);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->arp_count->hasRequestedSize()) {
        if (this->arp_count->wantsFill())
            this->fillarp_count(this->arp_count);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->data_04_buffer = this->data_04_buffer->allocateIfNeeded();

    if (this->note_count->hasRequestedSize()) {
        if (this->note_count->wantsFill())
            this->zeroDataRef(this->note_count);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->data_03_buffer = this->data_03_buffer->allocateIfNeeded();

    if (this->notes_state->hasRequestedSize()) {
        if (this->notes_state->wantsFill())
            this->zeroDataRef(this->notes_state);

        this->getEngine()->sendDataRefUpdated(4);
    }

    this->data_05_buffer = this->data_05_buffer->allocateIfNeeded();

    if (this->window->hasRequestedSize()) {
        if (this->window->wantsFill())
            this->fillwindow(this->window);

        this->getEngine()->sendDataRefUpdated(5);
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(6);
    }
}

void initializeObjects() {
    this->data_01_init();
    this->data_02_init();
    this->data_03_init();
    this->data_04_init();
    this->data_05_init();
    this->data_06_init();
    this->p_04->initializeObjects();
    this->p_05->initializeObjects();
    this->p_06->initializeObjects();

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->initializeObjects();
    }

    this->p_08->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_04->startup();
    this->p_05->startup();
    this->p_06->startup();

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->startup();
    }

    this->p_08->startup();

    {
        this->scheduleParamInit(0, 0);
    }

    this->processParamInitEvents();
}

static number param_21_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_05_in3_set(number v) {
    this->dspexpr_05_in3 = v;
}

void dspexpr_04_in3_set(number v) {
    this->dspexpr_04_in3 = v;
}

void notein_01_outchannel_set(number ) {}

void notein_01_releasevelocity_set(number ) {}

void p_08_in2_number_set(number v) {
    this->p_08->updateTime(this->_currentTime);
    this->p_08->eventinlet_10_out1_number_set(v);
}

void notein_01_velocity_set(number v) {
    this->p_08_in2_number_set(v);
}

void p_08_in1_number_set(number v) {
    this->p_08->updateTime(this->_currentTime);
    this->p_08->eventinlet_09_out1_number_set(v);
}

void notein_01_notenumber_set(number v) {
    this->p_08_in1_number_set(v);
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

void p_07_target_set(number v) {
    this->p_07_target = v;
}

void p_06_out2_number_set(number v) {
    this->p_07_target_set(v);
}

void p_07_voicestatus_set(const list& v) {
    for (Index i = 0; i < 1500; i++) {
        if (i + 1 == this->p_07_target || 0 == this->p_07_target) {
            this->p_07[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 1500; i++) {
        if (i + 1 == this->p_07_target || 0 == this->p_07_target) {
            this->p_07[i]->voice_01_mutein_list_set(v);
        }
    }
}

void p_07_activevoices_set(number v) {
    for (Index i = 0; i < 1500; i++) {
        if (i + 1 == this->p_07_target || 0 == this->p_07_target) {
            this->p_07[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 1500; i++) {
        this->p_07[i]->voice_01_activevoices_set(v);
    }
}

void p_07_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 1500; i++) {
            this->p_07[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 1500) {
            this->p_07[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->p_07_voicestatus_set(tmp);
    this->p_07_activevoices_set(this->p_07_calcActiveVoices());
}

void p_07_in1_bang_bang() {
    for (Index i = 0; i < 1500; i++) {
        if (i + 1 == this->p_07_target || 0 == this->p_07_target) {
            this->p_07[i]->updateTime(this->_currentTime);
        }
    }

    for (Index i = 0; i < 1500; i++) {
        if (i + 1 == this->p_07_target || 0 == this->p_07_target) {
            this->p_07[i]->eventinlet_08_out1_bang_bang();
        }
    }
}

void p_06_out1_bang_bang() {
    this->p_07_in1_bang_bang();
}

void p_06_perform(Index n) {
    // subpatcher: trigger
    this->p_06->process(nullptr, 0, nullptr, 0, n);
}

void p_07_perform(SampleValue * out1, SampleValue * out2, Index n) {
    // subpatcher: cloud
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 1500; i++)
        this->p_07[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void p_05_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: feedback
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_05->process(ins, 2, outs, 2, n);
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

void p_04_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: record
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_04->process(ins, 2, outs, 2, n);
}

void dspexpr_04_perform(
    const Sample * in1,
    const Sample * in2,
    number in3,
    SampleValue * out1,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in3 * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void dspexpr_05_perform(
    const Sample * in1,
    const Sample * in2,
    number in3,
    SampleValue * out1,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in3 * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void p_08_perform(Index n) {
    // subpatcher: midi_process
    this->p_08->process(nullptr, 0, nullptr, 0, n);
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

void param_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_21_value;
}

void param_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_21_value_set(preset["value"]);
}

number p_07_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 1500; i++) {
            if ((bool)(!(bool)(this->p_07[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
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
    this->data_02_buffer->setWantsFill(true);
}

Index data_02_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
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
    {
        this->data_06_buffer->requestSize(
            this->data_06_evaluateSizeExpr(this->samplerate(), this->vectorsize()),
            this->data_06_channels
        );
    }

    this->data_06_buffer->setWantsFill(true);
}

Index data_06_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    number size = 0;

    {
        size = samplerate * 10;
    }

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

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
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
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    dspexpr_04_in3 = 0;
    p_04_target = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0;
    dspexpr_05_in3 = 0;
    param_21_value = 0;
    p_05_target = 0;
    p_06_target = 0;
    p_07_target = 0;
    data_01_sizeout = 0;
    data_01_size = 1;
    data_01_sizems = 0;
    data_01_normalize = 0.995;
    data_01_channels = 1;
    data_02_sizeout = 0;
    data_02_size = 1;
    data_02_sizems = 0;
    data_02_normalize = 0.995;
    data_02_channels = 1;
    data_03_sizeout = 0;
    data_03_size = 128;
    data_03_sizems = 0;
    data_03_normalize = 0.995;
    data_03_channels = 3;
    data_04_sizeout = 0;
    data_04_size = 1;
    data_04_sizems = 0;
    data_04_normalize = 0.995;
    data_04_channels = 1;
    data_05_sizeout = 0;
    data_05_size = 65536;
    data_05_sizems = 0;
    data_05_normalize = 0.995;
    data_05_channels = 1;
    data_06_sizeout = 0;
    data_06_size = 0;
    data_06_sizems = 0;
    data_06_normalize = 0.995;
    data_06_channels = 2;
    p_08_target = 0;
    notein_01_channel = 0;
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
    param_21_lastValue = 0;
    data_01_sizemode = 1;
    data_01_setupDone = false;
    data_02_sizemode = 1;
    data_02_setupDone = false;
    data_03_sizemode = 1;
    data_03_setupDone = false;
    data_04_sizemode = 1;
    data_04_setupDone = false;
    data_05_sizemode = 1;
    data_05_setupDone = false;
    data_06_sizemode = 3;
    data_06_setupDone = false;
    notein_01_status = 0;
    notein_01_byte1 = -1;
    notein_01_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number dspexpr_04_in3;
    number p_04_target;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number dspexpr_05_in3;
    number param_21_value;
    number p_05_target;
    number p_06_target;
    number p_07_target;
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
    number data_05_sizeout;
    number data_05_size;
    number data_05_sizems;
    number data_05_normalize;
    number data_05_channels;
    number data_06_sizeout;
    number data_06_size;
    number data_06_sizems;
    number data_06_normalize;
    number data_06_channels;
    number p_08_target;
    number notein_01_channel;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[6];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_21_lastValue;
    Float64BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    Float64BufferRef data_02_buffer;
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
    int notein_01_status;
    int notein_01_byte1;
    int notein_01_inchan;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef source;
    DataRef sample_index;
    DataRef arp_count;
    DataRef note_count;
    DataRef notes_state;
    DataRef window;
    DataRef RNBODefaultSinus;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_12* p_04;
    RNBOSubpatcher_13* p_05;
    RNBOSubpatcher_14* p_06;
    RNBOSubpatcher_15* p_07[1500];
    RNBOSubpatcher_16* p_08;

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

