#pragma once
#include <math.h>
#include "CSModule.hpp"
#include "DBug.hpp"
#include "dsp.hpp"
#include "filters/HuovilainenMoogFilter.hpp"
#include "filters/base.hpp"
#include "plugin.hpp"

using namespace captainssounds::filters;
using namespace rack;

namespace captainssounds {
    struct Dip : CSModule {
        enum ParamIds {
            LP_PARAM,
            HP_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            INPUT,
            LP_INPUT,
            HP_INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            OUTPUT,
            NUM_OUTPUTS
        };

        HuovilainenMoogFilter lpFilter;
        HuovilainenMoogFilter hpFilter;
        float lpFrequency;
        float lpInputV;
        float lpParam;
        float lpValue;
        float hpFrequency;
        float hpInputV;
        float hpParam;
        float hpValue;
        int inputChannels;
        float inputV;
        float outputV;

        Dip() {
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam<EQParamQuantity>(LP_PARAM, 0.f, 1.f, .4f, "Low pass frequency", "Hz");
            configParam<EQParamQuantity>(HP_PARAM, 0.f, 1.f, .6f, "High pass frequency", "Hz");
            hpFilter.mode = filters::MODE_HIGHPASS;
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelDip;