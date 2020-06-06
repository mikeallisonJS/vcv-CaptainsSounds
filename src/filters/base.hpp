#pragma once

namespace captainssounds {
    namespace filters {
        enum modes {
            MODE_LOWPASS,
            MODE_HIGHPASS,
            MODE_BANDPASS,
            MODE_NOTCH,
            MODE_LOWSHELF,
            MODE_HIGHSHELF
        };
        enum oversamples {
            NO_OVERSAMPLE,
            OVERSAMPLE_2X = 2,
            OVERSAMPLE_4X = 4
        };
        class CSFilterBase {
          public:
            float sampleRate;

            int mode = MODE_LOWPASS;
            int oversample = NO_OVERSAMPLE;

            CSFilterBase() {
            }

          protected:
            float cutoff;
            float resonance;
        };
    }  // namespace filters
}  // namespace captainssounds
