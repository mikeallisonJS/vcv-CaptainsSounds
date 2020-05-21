#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"
#include "Dip.hpp"

using namespace captainssounds;

//Dip Filter
void Dip::Filter::process(float modelSampleTime) {

	// Calculate internal sampleTime
	if (sampleTime == 2.f) {
		sampleTime = 0.f;
		sampleOffset = modelSampleTime;
	}
	sampleTime = modelSampleTime + sampleOffset;
	if (sampleTime > 1) 
		sampleTime--;
	
	// Calculate phase
	phase += frequency * sampleTime;
	if (phase >= 0.5f)
		phase--;
}


void Dip::process(const ProcessArgs& args) {
	//don't waste time if there is no input
	if(!inputs[INPUT].isConnected())
		return;

	
	// Use Low pass CV if connected
	if(inputs[LP_INPUT].isConnected()) {		
		lpInputV = inputs[LP_INPUT].getVoltage();
		// TODO: figure this shit out		
		// lpFilter.frequency = pow((lpInputV * 10), ); //10v to 100%
	} else {
		lpFilter.frequency = params[LP_PARAM].getValue();
	}

	// Use HP CV if connected
	if(inputs[HP_INPUT].isConnected()) {
		hpInputV = inputs[HP_INPUT].getVoltage();
		// hpFilter.frequency = pow((hpInputV * 10), ); //10v to 100%
	} else {
		hpFilter.frequency = params[LP_PARAM].getValue();
	}

	// Use Q CV if connected
	if(inputs[Q_INPUT].isConnected()) {
		qInputV = inputs[Q_INPUT].getVoltage();
		// hpFilter.frequency = pow((hpInputV * 10), ); //10v to 100%
	} else {
		hpFilter.q = params[Q_PARAM].getValue();
		lpFilter.q = params[Q_PARAM].getValue();
	}

	// Use Slope CV if connected
	if(inputs[SLOPE_INPUT].isConnected()) {
		qInputV = inputs[SLOPE_INPUT].getVoltage();
		// hpFilter.frequency = pow((hpInputV * 10), ); //10v to 100%
	} else {
		hpFilter.slope = params[SLOPE_PARAM].getValue();
		lpFilter.slope = params[SLOPE_PARAM].getValue();
	}
	
	// Process the current sample
	lpFilter.sampleRate = args.sampleRate;
	lpFilter.process(args.sampleTime);
	hpFilter.sampleRate = args.sampleRate;
	hpFilter.process(args.sampleRate);
	

	// Output selected wave pattern
	// outputs[OUTPUT].setVoltage(hpFilter.getVoltage());
					
}

struct DipWidget : ModuleWidget {
	DipWidget(Dip* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Dip.svg")));

		// Screws
		addChild(createWidget<ScrewBlack>(Vec(box.size.x/3, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x/3, 365)));

		// LP
		addParam(createParam<Round909Knob>(paramVec(0, 0), module, Dip::LP_PARAM));
		addInput(createInput<Round909Port>(paramInputJackVec(0, 0), module, Dip::LP_INPUT));

		// HP
		addParam(createParam<Round909Knob>(paramVec(0, 1), module, Dip::HP_PARAM));
		addInput(createInput<Round909Port>(paramInputJackVec(0, 1), module, Dip::HP_INPUT));

		// Q
		addParam(createParam<Round909Knob>(paramVec(0, 2), module, Dip::Q_PARAM));
		addInput(createInput<Round909Port>(paramInputJackVec(0, 2), module, Dip::Q_INPUT));

		// Slope
		addParam(createParam<Round909SnapKnob>(paramVec(0, 2), module, Dip::SLOPE_PARAM));
		addInput(createInput<Round909Port>(paramInputJackVec(0, 2), module, Dip::SLOPE_INPUT));

		// Input
		addInput(createInput<Round909Port>(Vec(10, 265), module, Dip::INPUT));
		
		// Output
		addOutput(createOutput<Round909Port>(Vec(11, OUTPUT_ROW_1_POS), module, Dip::OUTPUT));
	}
};


Model* modelDip = createModel<Dip, DipWidget>("Dip");