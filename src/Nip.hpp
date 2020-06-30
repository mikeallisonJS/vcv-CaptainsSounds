#pragma once
#include <rack.hpp>
#include "CSModule.hpp"


using namespace captainssounds;

namespace captainssounds {
    struct Nip : CSModule {
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
            ENUMS(LIGHT_1, 3),
            ENUMS(LIGHT_2, 3),
            ENUMS(LIGHT_3, 3),
            ENUMS(LIGHT_4, 3),
            ENUMS(LIGHT_5, 3),
            ENUMS(LIGHT_6, 3),
            ENUMS(LIGHT_7, 3),
            ENUMS(LIGHT_8, 3),
            ENUMS(LIGHT_9, 3),
            ENUMS(LIGHT_10, 3),
            NUM_LIGHTS
        };

        static const int UPSAMPLES = 2;

        dsp::ClockDivider lightDivider;
        dsp::Decimator<UPSAMPLES, 8> clippedOutputDecimator[NUM_POLY_CHANNELS];
        dsp::Upsampler<UPSAMPLES, 8> inputUpsampler[NUM_POLY_CHANNELS];
        dsp::Decimator<UPSAMPLES, 8> outputDecimator[NUM_POLY_CHANNELS];

        Nip() {
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
            configParam(GAIN_INPUT, 0.f, 200.f, 100.f, "Gain", "%");
            configParam(CEIL_PARAM, 0.f, 100.f, 100.f, "Ceiling", "%");
            lightDivider.setDivision(16);
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelNip;