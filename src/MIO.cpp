#include "captainssounds.hpp"
#include "MIO.hpp"
#include <math.h>

using namespace captainssounds;

void MIO::process(const ProcessArgs& args) {
    bool connectedA = outputs[OUTPUT_A].isConnected();

	// Handle input A
	if (connectedA) {
        for (int i = 0; i < numChannels; i++) {
            outputAV[i] = 0.f;
            for (int j = 0; j < 3; j++) {
                outputAV[i] = clamp10VBipolar(inputs[INPUT_1 + j].getPolyVoltage(i) + outputAV[i]);
            }
            outputs[OUTPUT_A].setVoltage(outputAV[i], i);
        }
    }

    // Handle input B
    if (outputs[OUTPUT_B].isConnected()) {
        int index = connectedA ? 3 : 0;
        for (int i = 0; i < numChannels; i++) {
            outputBV[i] = 0.f;
            for (int j = index; j < 6; j++) {
                outputBV[i] = clamp10VBipolar(inputs[INPUT_1 + j].getPolyVoltage(i) + outputBV[i]);
            }
            outputs[OUTPUT_B].setVoltage(outputBV[i], i);
        }
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