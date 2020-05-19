#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"
#include "Dip.hpp"

using namespace captainssounds;

//VBNO Oscillator
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
		
		lpFilter.frequency = pow((lpInputV * 10), ) //10v to 100%
	} else {
		lpFilter.frequency = params[LP_PARAM].getValue();
	}

	// Use Note CV if connected
	if(inputs[NOTE_INPUT].isConnected()) {
		noteInputV = inputs[NOTE_INPUT].getVoltage();
		float note = round(modf(noteInputV, nullptr) * 12) + 3;
		notesFromA = note <= 11 ? note : note + 9;
	} else {
		notesFromA = params[NOTE_PARAM].getValue();
	}
	
	// Generate Frequency from Oct & Note
	osc.frequency = dsp::calculateFrequencyFromFromA4(octavesFromA4, notesFromA);
	
	// Process the current sample
	osc.sampleRate = args.sampleRate;
	osc.process(args.sampleTime);
	

	// Use Wave CV if connected 0-10v
	if (inputs[WAVE_INPUT].isConnected()) {
		float waveInputV = round(inputs[WAVE_INPUT].getVoltage());
		float waveAdjustedV = clamp(floor(.4f * waveInputV), 0.f, 3.f); //4 choices, 10volts
		osc.selectedWave = waveAdjustedV;
	} else {
		osc.selectedWave = params[WAVE_PARAM].getValue();
	}

	// Output selected wave pattern
	outputs[OUTPUT].setVoltage(osc.getVoltage());
					
}

struct VBNOWidget : ModuleWidget {
	VBNOWidget(VBNO* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VBNO.svg")));

		//Screws
		addChild(createWidget<ScrewBlack>(Vec(box.size.x/3, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x/3, 365)));

		// Octave
		addParam(createParam<RoundBlackSnapKnob>(paramVec(0, 0), module, VBNO::OCTAVE_PARAM));
		addInput(createInput<PJ301MPort>(paramInputJackVec(0, 0), module, VBNO::OCTAVE_INPUT));

		// Note
		addParam(createParam<RoundBlackSnapKnob>(paramVec(0, 1), module, VBNO::NOTE_PARAM));
		addInput(createInput<PJ301MPort>(paramInputJackVec(0, 1), module, VBNO::NOTE_INPUT));

		// Fn
		addParam(createParam<RoundBlackSnapKnob>(paramVec(0, 2), module, VBNO::WAVE_PARAM));
		addInput(createInput<PJ301MPort>(paramInputJackVec(0, 2), module, VBNO::WAVE_INPUT));

		// Sync
		addInput(createInput<PJ301MPort>(Vec(10, 265), module, VBNO::SYNC_INPUT));
		
        // Outputs
		addOutput(createOutput<PJ301MPort>(outputVec(0, 0), module, VBNO::OUTPUT));
	}
};


Model* modelVBNO = createModel<VBNO, VBNOWidget>("VBNO");