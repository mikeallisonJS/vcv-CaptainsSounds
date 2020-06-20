#pragma once
#include "CSModule.hpp"

namespace captainssounds {
    struct IMO : CSModule {
        enum inputIds {
            INPUT_A,
            INPUT_B,
            NUM_INPUTS
        };
        enum outputIds {
            OUTPUT_1,
            OUTPUT_2,
            OUTPUT_3,
            OUTPUT_4,
            OUTPUT_5,
            OUTPUT_6,
            NUM_OUTPUTS
        };

        int numChannels = 16;
        float outputAV[16];
        float outputBV[16];
        int channelsA = 0;
        int channelsB = 0;

        IMO() {
            config(0, NUM_INPUTS, NUM_OUTPUTS);
        }

        void process(const ProcessArgs& args) override;
    };
}  // namespace captainssounds