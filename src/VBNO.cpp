#include <math.h> 
#include "plugin.hpp"
#include "SoundMath.cpp"

struct Oscillator {
	float frequency;
	float phase;
	float sampleRate;
	float sampleTime;
	float sampleOffset;
	int selectedWave;
	enum waves {
		SINE,
		TRIANGLE,
		SAW,
		SQUARE,
		NUM_WAVES
	};
	Oscillator() {
		sampleTime = 2.f; // bogus value to force offset calc
		selectedWave = SINE;
	}
	void process(float modelSampleTime) {
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
	void sync() {
		sampleTime = 2.f; // bogus value to force offset calc
	}
	float buildWave() {
		switch (selectedWave) {
			case 1:
				return SoundMath::triangle(phase);	
			case 2:
				return SoundMath::saw(phase);	
			case 3:
				return SoundMath::square(phase, 0.5f);
			default:
				return SoundMath::sine(phase);
		}	
	}
	float getVoltage() {
		return 5.f * buildWave();
	}
};

struct VBNO : Module {
	enum ParamIds {
		OCTAVE_PARAM,
		NOTE_PARAM,
		WAVE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		NOTE_INPUT,
		OCTAVE_INPUT,
		SYNC_INPUT,
		WAVE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT,
		NUM_OUTPUTS
	};

	Oscillator osc;
	float semitones;
	float octavesFromA4 = -1.f; // C4
	float octaveInputV;
	float notesFromA = 3.f; // C
	float noteInputV;
	

	VBNO() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
		configParam(OCTAVE_PARAM, -5.f, 3.f, octavesFromA4, "Octave");
		configParam(NOTE_PARAM, 0.f, 11.f, notesFromA, "Base note");
		configParam(WAVE_PARAM, 0.f, (osc.NUM_WAVES - 1), (osc.selectedWave), "Wave shape");
	}

	void process(const ProcessArgs& args) override {
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
		osc.frequency = SoundMath::calculateFrequencyFromFromA4(octavesFromA4, notesFromA);
		
		// Process the current sample
		osc.sampleRate = args.sampleRate;
		osc.process(args.sampleTime);
		

		// Output selected wave pattern
		osc.selectedWave = params[WAVE_PARAM].getValue();
		outputs[OUTPUT].setVoltage(osc.getVoltage());
						
	}
};

const int INPUT_ROW_OFFSET = 70;
const int INPUT_ROW_1_POS = 40;
const int INPUT_JACK_Y_OFFSET = 30;

const int INPUT_COLUMN_OFFSET = 82;
const int INPUT_COLUMN_1_POS = 8;
const int INPUT_JACK_X_OFFSET = 2;

const int OUTPUT_ROW_OFFSET = 35;
const int OUTPUT_ROW_1_POS = 320;
const int OUTPUT_COLUMN_OFFSET = 35;
const int OUTPUT_COLUMN_1_POS = 10;

Vec paramInputJackVec (int column, int row) {
	return Vec(
		(column * INPUT_COLUMN_OFFSET + INPUT_JACK_X_OFFSET) + INPUT_COLUMN_1_POS,
		(row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS + INPUT_JACK_Y_OFFSET
	);
}

Vec paramVec (int column, int row) {
		return Vec(
			(column * INPUT_COLUMN_OFFSET) + INPUT_COLUMN_1_POS,
			(row * INPUT_ROW_OFFSET) + INPUT_ROW_1_POS
		);
}

Vec outputVec(int column, int row) {
	return Vec(
		(column * OUTPUT_COLUMN_OFFSET) + OUTPUT_COLUMN_1_POS,
			(row * OUTPUT_ROW_OFFSET) + OUTPUT_ROW_1_POS
	);
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
		addInput(createInput<PJ301MPort>(Vec(10, 263), module, VBNO::SYNC_INPUT));
		
        // Outputs
		addOutput(createOutput<PJ301MPort>(outputVec(0, 0), module, VBNO::OUTPUT));
	}
};


Model* modelVBNO = createModel<VBNO, VBNOWidget>("VBNO");