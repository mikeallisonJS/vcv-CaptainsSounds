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
        const int OUTPUT_ROW_BOTTOM_POS = 320;

        const int LIGHT_COLUMN_POSITIONS [3] = {5, 12, 19};

        int hp = 1;

        void addParamKnob(int row, int param, bool snap = false);
        void addParamKnobWithInput(int row, int param, int input, bool snap = false);
        void addInputJack(int input);
        void addOutputJack(int output);
        void addScrews();
        template<typename T>
        T* addLight(int yPos, int light) {
            addChild(createLight<T>(Vec(12, yPos), module, light));
            return 0; // because I have to return something
        }
    };

    struct CSSplitModuleWidget : CSModuleWidget {
        const int INPUT_ROW_POSITIONS [2]  = { 160, 265 };
        const int PARAM_ROW_POSITIONS [3] = {55, 220};
        const int PARAM_COLUMN_POSITIONS [3] = {3, 6, 10};
        const int OUTPUT_ROW_POSITIONS [2] = {147, 320 };
 
        void addParamKnob(int row, int param, bool snap = false);
        void addParamKnobWithInput(int row, int param, int input, bool snap = false);
        void addInputJack(int row, int input);
        void addOutputJack(int row, int input);
    };
}