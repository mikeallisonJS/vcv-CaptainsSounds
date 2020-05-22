#include <math.h> 
#include "plugin.hpp"
#include "dsp.hpp"
#include "VBNO.hpp"

using namespace captainssounds;

//VBNO Oscillator
void VBNO::Oscillator::process(float modelSampleTime) {
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
void VBNO::Oscillator::sync() {
	sampleTime = 2.f; // bogus value to force offset calc
}
float VBNO::Oscillator::buildWave() {
	switch (selectedWave) {
		case 1:
			return dsp::triangle(phase);	
		case 2:
			return dsp::saw(phase);	
		case 3:
			return dsp::square(phase, 0.5f);
		default:
			return dsp::sine(phase);
	}	
}
float VBNO::Oscillator::getVoltage() {
	return 5.f * buildWave();
}

void VBNO::process(const ProcessArgs& args) {
	// Check for sync signal
	if (inputs[SYNC_INPUT].getVoltage() > 0.f)
		osc.sync();

	
	// Use Octave CV if connected
	if(inputs[OCTAVE_INPUT].isConnected()) {
		octaveInputV = inputs[OCTAVE_INPUT].getVoltage();	
		octavesFromA4 = round(octaveInputV) - 2;
	} else {
		octavesFromA4 = params[OCTAVE_PARAM].getValue() - 1; //TODO: FIND 1 off???
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

struct VBNOWidget : CSModuleWidget {
	VBNOWidget(VBNO* module) {
		hp = 3;
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VBNO.svg")));
		addScrews();

		// Octave
		addParamKnobWithInput(0, VBNO::OCTAVE_PARAM, VBNO::OCTAVE_INPUT, true);

		// Note
		addParamKnobWithInput(1, VBNO::NOTE_PARAM, VBNO::NOTE_INPUT, true);

		// Fn
		addParamKnobWithInput(2, VBNO::WAVE_PARAM, VBNO::WAVE_INPUT, true);

		// Sync
		addInputJack(VBNO::SYNC_INPUT);
		
        // Outputs
		addOutputJack(VBNO::OUTPUT);
	}
};


Model* modelVBNO = createModel<VBNO, VBNOWidget>("VBNO");