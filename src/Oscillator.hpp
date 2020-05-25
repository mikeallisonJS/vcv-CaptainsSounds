#pragma once
#include <math.h>
#include "dsp.hpp"

using namespace captainssounds::dsp;

namespace captainssounds {
    // template <int OVERSAMPLE, int QUALITY, typename T>
    struct Oscillator {
        float frequency;
        float phase;
        float sampleRate;
        float sampleTime;
        float sampleOffset;            
        float sinc;
        float tuning;
        int wave;
        // dsp::MinBlepGenerator<QUALITY, OVERSAMPLE, T> minBlep;
        enum waves {
            SINE,
            TRIANGLE,
            SAW,
            SQUARE,
            NUM_WAVES
        };
        enum syncs {
            SOFT,
            HARD,
            NUM_SYNCS
        };

        Oscillator() {
            sampleTime = 2.f; // bogus value to force offset calc
            wave = SINE;
            tuning = DEFAULT_FREQ_A4;
            sinc = SOFT;            
        }

        void process(float modelSampleTime);
        void sync();
        float buildWave();
        float getVoltage();

        template<typename T>
        T calculateFrequencyFromA4Tuning(T octaveFromA4, T notesFromA4) {
            T semitones = (octaveFromA4 * 12) + notesFromA4;
            return tuning * pow(FREQ_SEMITONE, semitones);
        }

        template<typename T>
        T saw(T phase) {
            T x = phase + 0.5f;
            return 2 * x - 1;
        }

        template<typename T>
        T sine(T phase) {
            return sin(TWO_PI * phase);
        }

        template<typename T>
        T square(T phase, T pulseWidth) {
            float pw = tclamp(pulseWidth, .01f, .99f);
            return phase > pw - .5 ? 1.f : -1.f;
        }

        template<typename T>
        T triangle(T phase) {
            return 1 - 4 * fmin(fabs(.5 - modf(phase + .25f, nullptr)), fabs(.5 - modf(phase + 1.25f, nullptr)));
        }
    };
}