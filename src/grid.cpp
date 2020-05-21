#include "grid.hpp"

using namespace captainssounds;

Vec grid::paramInputJackVec (int column, int row) {
    return Vec(
        (column * INPUT_COLUMN_OFFSET + INPUT_JACK_X_OFFSET) + INPUT_COLUMN_1_POS,
        (row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS + INPUT_JACK_Y_OFFSET
    );
}

Vec grid::paramVec (int column, int row) {
    return Vec(
        (column * INPUT_COLUMN_OFFSET) + INPUT_COLUMN_1_POS,
        (row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS
    );
}