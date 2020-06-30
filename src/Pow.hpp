#pragma once
#include "CSModule.hpp"

using namespace captainssounds;

namespace captainssounds {
    struct Pow : CSModule {
        enum ParamIds {
            UNI_PARAM,
            BI_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            UNI_INPUT,
            BI_INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            UNI_OUTPUT,
            BI_OUTPUT,
            NUM_OUTPUTS
        };
        enum LightIds {
            UNI_LIGHT,
            ENUMS(BI_LIGHT, 2),
            NUM_LIGHTS
        };

        bool biConnected = false;
        bool uniConnected = false;

        float biInputV;
        float biOutputV;
        float biParam;
        float uniInputV;
        float uniOutputV;
        float uniParam;

        int numInputsBi;
        int numInputsUni;

        dsp::ClockDivider lightDivider;

        Pow() {
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
            configParam(UNI_PARAM, 0.00f, 10.00f, 10.f, "10V Uni-polar Voltage", "%");
            configParam(BI_PARAM, -5.00f, 5.00f, 0.f, "5V Bi-polar Voltage", "%");
            lightDivider.setDivision(16);
            outputs[UNI_OUTPUT].setChannels(NUM_POLY_CHANNELS);
            outputs[BI_OUTPUT].setChannels(NUM_POLY_CHANNELS);
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelPow;