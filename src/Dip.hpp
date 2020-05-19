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
            float frequency;
            float phase;
            float sampleRate;
            float sampleTime;
            float sampleOffset;
            float Q;
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
        float lpInputV


        Dip() {
            lpFilter.frequency = 22000.f;
            hpFilter.frequency = 10.f;
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(LP_PARAM, 10.f, 22000.f, lpFilter.frequency, "Low pass frequency", "Hz", 1.f, dsp::FREQ_C4 / std::pow(2, 5.f)));
            configParam(HP_PARAM, 10.f, 22000.f, hpFilter.frequency, "High pass frequency", "Hz", 1.f, dsp::FREQ_C4 / std::pow(2, 5.f)));
            configParam(Q_PARAM, 0.010f, 40.f, 1.f, "Q - Bandwidth", "", 1.00f, 1.009f);
            configParam(SLOPE_PARAM, 6.f, 96.f, 18.f, "Slope", "dB/oct", 1.f);
        }

        void process(const ProcessArgs& args) override;
    };

    const int INPUT_ROW_OFFSET = 70;
    const int INPUT_ROW_1_POS = 40;
    const int INPUT_JACK_Y_OFFSET = 30;

    const int INPUT_COLUMN_OFFSET = 82;
    const int INPUT_COLUMN_1_POS = 8;
    const int INPUT_JACK_X_OFFSET = 2;

    const int OUTPUT_ROW_OFFSET = 35;
    const int OUTPUT_ROW_1_POS = 320;
    const int OUTPUT_COLUMN_OFFSET = 35;
    const int OUTPUT_COLUMN_1_POS = 10;

    Vec paramInputJackVec (int column, int row) {
        return Vec(
            (column * INPUT_COLUMN_OFFSET + INPUT_JACK_X_OFFSET) + INPUT_COLUMN_1_POS,
            (row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS + INPUT_JACK_Y_OFFSET
        );
    }

    Vec paramVec (int column, int row) {
            return Vec(
                (column * INPUT_COLUMN_OFFSET) + INPUT_COLUMN_1_POS,
                (row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS
            );
    }

    Vec outputVec(int column, int row) {
        return Vec(
            (column * OUTPUT_COLUMN_OFFSET) + OUTPUT_COLUMN_1_POS,
                (row * OUTPUT_ROW_OFFSET) + OUTPUT_ROW_1_POS
        );
    }
}

extern Model* modelDip;