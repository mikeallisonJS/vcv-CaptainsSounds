// Adapted from the HuovilainenMoog.h dependency
#pragma once

#include <math.h>
#include <string.h>
#include "base.hpp"
#include "util.h"

namespace captainssounds {
    namespace filters {
        class HuovilainenMoogFilter : public CSFilterBase {
          public:
            float output;
            float highpass;

            HuovilainenMoogFilter() {
                reset();
                setCutoff(1000.0f);
                setResonance(0.10f);
            }

            void reset() {
                memset(stage, 0, sizeof(stage));
                memset(delay, 0, sizeof(delay));
                memset(stageTanh, 0, sizeof(stageTanh));
                oversample = OVERSAMPLE_2X;
            }

            void process(float sample) {
                // Oversample
                for (int j = 0; j < oversample; j++) {
                    float input = sample - resQuad * delay[5];
                    delay[0] = stage[0] = delay[0] + tune * (tanh(input * thermal) - stageTanh[0]);
                    for (int k = 1; k < 4; k++) {
                        input = stage[k - 1];
                        stage[k] = delay[k] + tune * ((stageTanh[k - 1] = tanh(input * thermal)) - (k != 3 ? stageTanh[k] : tanh(delay[k] * thermal)));
                        delay[k] = stage[k];
                    }
                    // 0.5 sample delay for phase compensation
                    output = (stage[3] + delay[4]) * 0.5;
                    delay[4] = stage[3];
                }
            }

            void setResonance(float r) {
                resonance = r;
                resQuad = 4.0 * resonance * acr;
            }

            void setCutoff(float c) {
                cutoff = c;

                double fc = cutoff / sampleRate;
                double f = fc * (1.f / oversample);  // oversampled
                double fc2 = pow(fc, 2);
                double fc3 = pow(fc, 3);

                double fcr = 1.8730 * fc3 + 0.4955 * fc2 - 0.6490 * fc + 0.9988;
                acr = -3.9364 * fc2 + 1.8409 * fc + 0.9968;

                tune = (1.0 - exp(-((2 * MOOG_PI) * f * fcr))) / thermal;

                setResonance(resonance);
            }

          private:
            double thermal = 0.000025;
            double stage[4];
            double stageTanh[3];
            double delay[6];
            double tune;
            double acr;
            double resQuad;
            int poles = 4;
        };
    }  // namespace filters
}  // namespace captainssounds
