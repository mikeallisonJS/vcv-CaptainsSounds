#pragma once
#include <rack.hpp>

using namespace rack;

namespace captainssounds {
    namespace grid {  
        const int INPUT_ROW_OFFSET = 70;
        const int INPUT_ROW_1_POS = 40;
        const int INPUT_JACK_Y_OFFSET = 30;

        const int INPUT_COLUMN_OFFSET = 82;
        const int INPUT_COLUMN_1_POS = 9;
        const int INPUT_JACK_X_OFFSET = 2;

        const int OUTPUT_ROW_1_POS = 320;

        Vec paramInputJackVec (int column, int row);
        Vec paramVec (int column, int row);
    }
}