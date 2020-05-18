#include <math.hpp>

namespace SoundMath {
    static const float FREQ_A4 = 440;
    static const float FREQ_SEMITONE = 1.0594630943592953f;
    static const float TWO_PI = 2 * M_PI;

    template<typename T>
    T calculateFrequencyFromFromA4(T octaveFromA4, T notesFromA) {
        T semitones = (octaveFromA4 * 12) + notesFromA;
        return FREQ_A4 * std::pow(FREQ_SEMITONE, semitones);
    }
    
    template<typename T>
    T saw(T phase) {
        T x = phase + 0.5f;
    return 2 * x - 1;
    }
    template<typename T>
    T sine(T phase) {
        return std::sin(TWO_PI * phase);
    }
    template<typename T>
    T square(T phase, T pulseWidth) {
        float pw = clamp(pulseWidth, .01f, .99f);
        return phase > pw - .5 ? 1.f : -1.f;
    }
    template<typename T>
    T triangle(T phase) {
        // return phase * 2;
            // 1 - 0 top phase .5 (correct)
            // 1 - 2 bottom phase -.25
        return 1 - 4 * fmin(fabs(.25 - phase), modf(phase - 1.25f, nullptr));
    }
};