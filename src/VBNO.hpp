#pragma once
#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"

using namespace captainssounds;

namespace captainssounds{
    struct VBNO : Module {
        struct Oscillator {
            float frequency;
            float phase;
            float sampleRate;
            float sampleTime;
            float sampleOffset;
            int selectedWave;
            enum waves {
                SINE,
                TRIANGLE,
                SAW,
                SQUARE,
                NUM_WAVES
            };
            Oscillator() {
                sampleTime = 2.f; // bogus value to force offset calc
                selectedWave = SINE;
            }
            void process(float modelSampleTime);
            void sync();
            float buildWave();
            float getVoltage();
        };
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
            octavesFromA4 = -1.f; // C4
            notesFromA = 3.f; // C
            config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
            configParam(OCTAVE_PARAM, -5.f, 3.f, octavesFromA4, "Octave");
            configParam(NOTE_PARAM, 0.f, 11.f, notesFromA, "Base note");
            configParam(WAVE_PARAM, 0.f, (osc.NUM_WAVES - 1), (osc.selectedWave), "Wave shape");
        }

        void process(const ProcessArgs& args) override;
    };
}

extern Model* modelVBNO;