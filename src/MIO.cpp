#include "MIO.hpp"
#include <math.h>
#include "captainssounds.hpp"

using namespace captainssounds;

void MIO::process(const ProcessArgs& args) {
    bool connectedA = outputs[OUTPUT_A].isConnected();

    // Handle output A
    if (connectedA) {
        int numChannels = 1;
        for (int i = 0; i < NUM_POLY_CHANNELS; i++) {
            outputAV[i] = 0.f;
            for (int j = 0; j < 3; j++) {
                int inputChannels = inputs[INPUT_1 + j].getChannels();
                outputAV[i] = clamp10VBipolar(inputs[INPUT_1 + j].getVoltage(i) + outputAV[i]);
                numChannels = inputChannels > numChannels ? inputChannels : numChannels;
            }
            outputs[OUTPUT_A].setVoltage(outputAV[i], i);
        }
        outputs[OUTPUT_A].setChannels(numChannels);
    }

    // Handle output B
    if (outputs[OUTPUT_B].isConnected()) {
        int numChannels = 1;
        int index = connectedA ? 3 : 0;
        for (int i = 0; i < NUM_POLY_CHANNELS; i++) {
            outputBV[i] = 0.f;
            for (int j = index; j < 6; j++) {
                int inputChannels = inputs[INPUT_1 + j].getChannels();
                outputBV[i] = clamp10VBipolar(inputs[INPUT_1 + j].getVoltage(i) + outputBV[i]);
                numChannels = inputChannels > numChannels ? inputChannels : numChannels;
            }
            outputs[OUTPUT_B].setVoltage(outputBV[i], i);
        }
        outputs[OUTPUT_B].setChannels(numChannels);
    }
}

struct MIOWidget : CSMultplitModuleWidget {
    MIOWidget(MIO* module) {
        hp = 2;
        setModule(module);

        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MIO.svg")));
        addScrews();

        addJack(0, INPUT_JACK, MIO::INPUT_1);
        addJack(1, INPUT_JACK, MIO::INPUT_2);
        addJack(2, INPUT_JACK, MIO::INPUT_3);
        //skip 1
        addJack(4, OUTPUT_JACK, MIO::OUTPUT_A);

        addJack(5, INPUT_JACK, MIO::INPUT_4);
        addJack(6, INPUT_JACK, MIO::INPUT_5);
        addJack(7, INPUT_JACK, MIO::INPUT_6);
        //skip 1
        addJack(9, OUTPUT_JACK, MIO::OUTPUT_B);
    }
};

Model* modelMIO = createModel<MIO, MIOWidget>("MIO");