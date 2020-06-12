#pragma once
#include "CSModule.hpp"
#include "Oscillator.hpp"


namespace captainssounds {
    struct VBNO : CSModule {
        enum ParamIds {
            OCTAVE_PARAM,
            NOTE_PARAM,
            WAVE_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            NOTE_INPUT,
            OCTAVE_INPUT,
            SYNC_INPUT,
            WAVE_INPUT,
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
            octavesFromA4 = -1.f;  // C4
            notesFromA = 3.f;      // C
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(OCTAVE_PARAM, -5.f, 3.f, octavesFromA4, "Octave");
            configParam(NOTE_PARAM, 0.f, 11.f, notesFromA, "Base note");
            configParam(WAVE_PARAM, 0.f, (osc.NUM_WAVES - 1), (osc.wave), "Wave shape");
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelVBNO;