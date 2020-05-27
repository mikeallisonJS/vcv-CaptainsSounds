#pragma once
#include <math.h>
#include "HuovilainenMoogFilter.hpp"
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds::filters;

namespace captainssounds {
    struct Dip : Module {
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
        float hpFrequency;
        float hpInputV;
        int inputChannels;
        float inputV;
        float outputV;

        Dip() {
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(LP_PARAM, 10.f, 22000.f, 500.f, "Low pass frequency", "Hz");
            configParam(HP_PARAM, 10.f, 22000.f, 500., "High pass frequency", "Hz");
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelDip;