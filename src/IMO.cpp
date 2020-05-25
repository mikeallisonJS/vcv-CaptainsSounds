#include "captainssounds.hpp"
#include "IMO.hpp"

using namespace captainssounds;

void IMO::process(const ProcessArgs& args) {
    bool connectedB = inputs[INPUT_B].isConnected();

	// Handle input A
	if (inputs[INPUT_A].isConnected()) {
        channelsA = inputs[INPUT_A].getChannels(); 
        for (int i = 0; i < numChannels; i++) 
            outputAV[i] = inputs[INPUT_A].getPolyVoltage(i);        
        
        int index = 3;
        //copy values to B outs if not connected
        if (!connectedB) 
            index = 6;
        
        for (int i = 0; i < index; i++) {
            outputs[OUTPUT_1 + i].setChannels(channelsA);        
            outputs[OUTPUT_1 + i].writeVoltages(outputAV);
        }
    }

    // Handle input B
    if (connectedB) {
        channelsB = inputs[INPUT_B].getChannels(); 
        for (int i = 0; i < numChannels; i++) 
            outputBV[i] = inputs[INPUT_B].getPolyVoltage(i);
        for (int i = 0; i < 3; i++) {
            outputs[OUTPUT_4 + i].setChannels(channelsB);        
            outputs[OUTPUT_4 + i].writeVoltages(outputBV);
        }
    }
}

struct IMOWidget : CSMultplitModuleWidget {
	IMOWidget(IMO* module) {
		hp = 2;
		setModule(module);		

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/IMO.svg")));
		addScrews();
        
        addJack(0, INPUT_JACK, IMO::INPUT_A);
        //skip 1
        addJack(2, OUTPUT_JACK, IMO::OUTPUT_1);
        addJack(3, OUTPUT_JACK, IMO::OUTPUT_2);
        addJack(4, OUTPUT_JACK, IMO::OUTPUT_3);
        addJack(5, INPUT_JACK, IMO::INPUT_B);
        //skip 1
        addJack(7, OUTPUT_JACK, IMO::OUTPUT_4);
        addJack(8, OUTPUT_JACK, IMO::OUTPUT_5);
        addJack(9, OUTPUT_JACK, IMO::OUTPUT_6);
	}
};


Model* modelIMO = createModel<IMO, IMOWidget>("IMO");