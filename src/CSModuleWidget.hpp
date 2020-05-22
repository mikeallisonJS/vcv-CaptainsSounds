#pragma once
#include <rack.hpp>

using namespace rack;

namespace captainssounds {
    // Single column grid widget
    struct CSModuleWidget : ModuleWidget {
        const int SCREW_BOTTOM_Y_POS = 365;
        const int SCREW_TOP_Y_POS = 0;
        const int SCREW_1_POSITIONS [3] = {0, 8, 16};

        const int PARAM_ROW_POSITIONS [3] = {40, 110, 180};
        const int PARAM_COLUMN_POSITIONS [3] = {3, 6, 10};

        const int JACK_COLUMN_POSITIONS [3] = {0, 4, 12};
        const int PARAM_JACK_Y_OFFSET = 30;    
        const int PARAM_SMALL_OFFSET = 3;

        const int INPUT_ROW_1_POS = 265;
        const int OUTPUT_ROW_1_POS = 320;

        int hp = 1;

        void addParamKnob(int row, int param, bool snap = true);
        void addParamKnobWithInput(int row, int param, int input, bool snap = true);
        void addInputJack(int input);
        void addOutputJack(int output);
        void addScrews();
    };
}