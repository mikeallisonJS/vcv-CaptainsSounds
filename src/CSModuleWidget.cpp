#include "CSModuleWidget.hpp"
#include "components.hpp"
#include <rack.hpp>

using namespace captainssounds;
using namespace captainssounds::components;
using namespace rack;

//CSModuleWidget
void CSModuleWidget::addScrews() {
    if (hp < 4) {    
        int hpIndex = hp - 1;
        addChild(createWidget<ScrewBlack>(Vec(SCREW_1_POSITIONS[hpIndex], SCREW_TOP_Y_POS)));
        addChild(createWidget<ScrewBlack>(Vec(SCREW_1_POSITIONS[hpIndex], SCREW_BOTTOM_Y_POS)));
    } else {
        addChild(createWidget<ScrewBlack>(Vec(1, SCREW_TOP_Y_POS)));
        addChild(createWidget<ScrewBlack>(Vec(1, SCREW_BOTTOM_Y_POS)));
        addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, SCREW_TOP_Y_POS)));
        addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, SCREW_BOTTOM_Y_POS)));
    }        
}

void CSModuleWidget::addParamKnob(int row, int param, bool snap) {
    int hpIndex = hp - 1;
    int yPos = PARAM_ROW_POSITIONS[row];
    if (hp == 2)
        yPos += PARAM_SMALL_OFFSET;
    if (snap) {
        if (hp == 2) 
            addParam(createParam<SmallRound909SnapKnob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
        else
            addParam(createParam<Round909SnapKnob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
    } else {
        if (hp == 2)
            addParam(createParam<SmallRound909Knob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
        else
            addParam(createParam<Round909Knob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
    }
}

void CSModuleWidget::addParamKnobWithInput(int row, int param, int input, bool snap) {
    addParamKnob(row, param, snap);
    int hpIndex = hp - 1;
    const int yPos = PARAM_ROW_POSITIONS[row] + PARAM_JACK_Y_OFFSET;
    if (hp == 2)
        addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, input));
    else
        addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, input));
}

void CSModuleWidget::addInputJack(int input = 0) {
    int hpIndex = hp - 1;
    addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], INPUT_ROW_1_POS), module, input));
}

void CSModuleWidget::addOutputJack(int output = 0) {
    int hpIndex = hp - 1;
    addOutput(createOutput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], OUTPUT_ROW_BOTTOM_POS), module, output));
}

//CSSplitModuleWidget
void CSSplitModuleWidget::addParamKnob(int row, int param, bool snap) {
    int hpIndex = hp - 1;
    int yPos = PARAM_ROW_POSITIONS[row];
    if (hp == 2)
        yPos += PARAM_SMALL_OFFSET;
    if (snap) {
        if (hp == 2) 
            addParam(createParam<SmallRound909SnapKnob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
        else
            addParam(createParam<Round909SnapKnob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
    } else {
        if (hp == 2)
            addParam(createParam<SmallRound909Knob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
        else
            addParam(createParam<Round909Knob>(Vec(PARAM_COLUMN_POSITIONS[hpIndex], yPos), module, param));
    }
}

void CSSplitModuleWidget::addParamKnobWithInput(int row, int param, int input, bool snap) {
    addParamKnob(row, param, snap);
    int hpIndex = hp - 1;
    const int yPos = PARAM_ROW_POSITIONS[row] + PARAM_JACK_Y_OFFSET;
    if (hp == 2)
        addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, input));
    else
        addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, input));
}

void CSSplitModuleWidget::addInputJack(int row, int input) {
    int hpIndex = hp - 1;
    addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], INPUT_ROW_POSITIONS[row]), module, input));
}

void CSSplitModuleWidget::addOutputJack(int row, int output) {
    int hpIndex = hp - 1;
    addOutput(createOutput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], OUTPUT_ROW_POSITIONS[row]), module, output));
}

// CSMultplitModuleWidget
void CSMultplitModuleWidget::addJack(int row, int inOrOut, int jack) {
    int hpIndex = hp - 1;
    int yPos = JACK_FIRST_ROW_POSITIONS[row];
    if (row > 3) {
        yPos = JACK_FIRST_ROW_POSITIONS[row - 4]+ JACK_SECOND_ROW_OFFSET;
    }
    if (inOrOut == INPUT_JACK)
        addInput(createInput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, jack));
    else
        addOutput(createOutput<Round909Port>(Vec(JACK_COLUMN_POSITIONS[hpIndex], yPos), module, jack));
}
