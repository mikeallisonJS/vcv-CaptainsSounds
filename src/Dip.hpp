#pragma once
#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"

using namespace captainssounds;

namespace captainssounds{
    struct Dip : Module {
        struct Filter {
            float highpassfrequency;
            float lowpassfrequency;
            float phase;
            float sampleRate;
            float sampleTime;
            float sampleOffset;
            float Q;
            float resonance;
            
            Filter() {
            }
            void process(float modelSampleTime);
        };
        enum ParamIds {
            LP_PARAM,
            HP_PARAM,
            WAVE_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            OUTPUT,
            NUM_OUTPUTS
        };

        Oscillator osc;
        float semitones;
        float octavesFromA4;
        float octaveInputV;
        float notesFromA;
        float noteInputV;
        float waveInputV;

        VBNO() {
            octavesFromA4 = -1.f; // C4
            notesFromA = 3.f; // C
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(OCTAVE_PARAM, -5.f, 3.f, octavesFromA4, "Octave");
            configParam(NOTE_PARAM, 0.f, 11.f, notesFromA, "Base note");
            configParam(WAVE_PARAM, 0.f, (osc.NUM_WAVES - 1), (osc.selectedWave), "Wave shape");
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

extern Model* modelVBNO;