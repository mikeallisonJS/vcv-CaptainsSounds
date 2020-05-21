#pragma once
#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"

using namespace captainssounds;

namespace captainssounds{
    struct Dip : Module {
        struct Filter {
            const float maxFrequency = 22000.f;
            const float minFrequency = 10.f;
            //TODO: Add exponential param values const
            float frequency;
            float phase;
            float sampleRate;
            float sampleTime;
            float sampleOffset;
            float q;
            float slope;
            
            Filter() {
            }
            void process(float modelSampleTime);
        };
        enum ParamIds {
            LP_PARAM,
            HP_PARAM,
            Q_PARAM,
            SLOPE_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            INPUT,
            LP_INPUT,
            HP_INPUT,
            Q_INPUT,
            SLOPE_INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            OUTPUT,
            NUM_OUTPUTS
        };

        Filter lpFilter;
        Filter hpFilter;
        float lpInputV;
        float hpInputV;
        float qInputV;


        Dip() {
            lpFilter.frequency = 22000.f;
            hpFilter.frequency = 10.f;
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(LP_PARAM, 10.f, 22000.f, lpFilter.frequency, "Low pass frequency", "Hz", 1.f, rack::dsp::FREQ_C4 / std::pow(2, 5.f));
            configParam(HP_PARAM, 10.f, 22000.f, hpFilter.frequency, "High pass frequency", "Hz", 1.f, rack::dsp::FREQ_C4 / std::pow(2, 5.f));
            configParam(Q_PARAM, 0.010f, 40.f, 1.f, "Q - Bandwidth", "", 1.00f, 1.009f);
            configParam(SLOPE_PARAM, 6.f, 96.f, 18.f, "Slope", "dB/oct", 1.f, 1.f, 6.f); // db increments
        }

        void process(const ProcessArgs& args) override;
    };
}

extern Model* modelDip;