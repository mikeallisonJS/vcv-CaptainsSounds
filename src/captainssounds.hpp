#pragma once
#include <rack.hpp>
#include <sstream>

namespace captainssounds {
    const int LOGO_Y_POS = 345;
    const int DEFAULT_SAMPLERATE = 44100;
    const int MAX_FILTER_HZ = DEFAULT_SAMPLERATE / 2;
    const int MIN_FILTER_HZ = 10;
    const float FILTER_PARAM_INCREMENT = 1.081f;  // fiddly, but based on: 100th root of MAX_FILTER_HZ

    // Generic Math
    template <typename T>
    T tmax(T a, T b) {
        return a >= b ? a : b;
    }

    template <typename T>
    T tmin(T a, T b) {
        return a <= b ? a : b;
    }

    template <typename T>
    T tclamp(T x, T min, T max) {
        return tmax(tmin(x, max), min);
    }

    // Voltage clamps
    template <typename T>
    T clamp10VUnipolar(T x) {
        return tclamp(x, 0.f, 10.f);
    }

    // Voltage clamps
    template <typename T>
    T clamp10VBipolar(T x) {
        return tclamp(x, -10.f, 10.f);
    }

    template <typename T>
    T clamp5VBipolar(T x) {
        return tclamp(x, -5.f, 5.f);
    }
}  // namespace captainssounds