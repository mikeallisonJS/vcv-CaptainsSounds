#pragma once
#include "plugin.hpp"

using namespace captainssounds;

namespace captainssounds{
    struct Nip : Module {
        enum ParamIds {
            GAIN_PARAM,
            CEIL_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            GAIN_INPUT,
            CEIL_INPUT,
            INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            OUTPUT,
            NUM_OUTPUTS
        };
        enum LightIds {
            GREEN_1V,
            GREEN_2V,
            GREEN_3V,
            YELLOW_4V,
            RED_5V,
            NUM_LIGHTS
        };

        float ceilInputV;
        float ceilParam;
        float ceilValue;
        float gainInputV;
        float gainParam;
        float gainValue;
        float inputV;
        float inputValue;
        float output;
    

        Nip() {
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
            configParam(GAIN_INPUT, 0.f, 200.f, 100.f, "Gain", "%");
            configParam(CEIL_PARAM, 0.f, 100.f, 100.f, "Ceiling", "%");
        }

        void process(const ProcessArgs& args) override;
    };
}

extern Model* modelNip;