#pragma once
#include "CSModule.hpp"

namespace captainssounds {
    struct MIO : CSModule {
        enum inputIds {
            INPUT_1,
            INPUT_2,
            INPUT_3,
            INPUT_4,
            INPUT_5,
            INPUT_6,
            NUM_INPUTS
        };
        enum outputIds {
            OUTPUT_A,
            OUTPUT_B,
            NUM_OUTPUTS
        };

        float outputAV[16];
        float outputBV[16];
        int channelsA = 0;
        int channelsB = 0;

        MIO() {
            config(0, NUM_INPUTS, NUM_OUTPUTS);
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds