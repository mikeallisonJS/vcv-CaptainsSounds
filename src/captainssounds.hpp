#pragma once

namespace captainssounds {
    const int LOGO_Y_POS = 345;
    const int DEFAULT_SAMPLERATE = 44100;

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