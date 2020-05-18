#include "plugin.hpp"
#include "SoundMath.cpp"

bool hardTune = false;
float octave = 0;

struct VBNO : Module {
	enum ParamIds {
		OCTAVE_PARAM,
		MODE_PARAM,
		NOTE_PARAM,
		FINE_PARAM,
		FM_PARAM,
		PW_PARAM,
		PWM_PARAM,
		// SYNC_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FM_INPUT,
		OCTAVE_INPUT,
		PITCH_INPUT,
		PW_INPUT,
		SYNC_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SAW_OUTPUT,
		SINE_OUTPUT,
		SQUARE_OUTPUT,
		TRIANGLE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		MODE_LIGHT,
		NUM_LIGHTS
	};

	float phase = 0.f;

	VBNO() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
		configParam(OCTAVE_PARAM, -5.f, 5.f, 0.f, "Octave");
		configParam(MODE_PARAM, 0.f, 1.f, 0.f, "Hard Tune mode");
		configParam(NOTE_PARAM, -7.f, 7.f, 0.f, "Frequency", " Hz", dsp::FREQ_SEMITONE, dsp::FREQ_C4);
		configParam(FINE_PARAM, -3.f, 3.f, 0.f, "Fine frequency");
		configParam(FM_PARAM, 0.f, 1.f, 0.f, "Frequency modulation", "%", 0.f, 100.f);
		configParam(PW_PARAM, 0.01f, 0.99f, 0.5f, "Pulse width", "%", 0.f, 100.f);
		configParam(PWM_PARAM, 0.f, 1.f, 0.f, "Pulse width modulation", "%", 0.f, 100.f);
	}

	void process(const ProcessArgs& args) override {
		// Process Buttons
		hardTune = params[MODE_PARAM].getValue();

		//Generate Frequency
		float freqInput = params[NOTE_PARAM].getValue();	
		float freqParam = hardTune ? round(freqInput) - 12 : freqInput; // not sure why, but when using CKSS slider it adds an octave
		freqParam = freqParam / 12.f;
		octave = round(params[OCTAVE_PARAM].getValue()) + round(params[OCTAVE_INPUT].getValue());
		freqParam = freqParam + octave;
		freqParam += params[FINE_PARAM].getValue() / 12.f;
		
		
		// The default pitch is C4 = 261.6256f
		float pitch = freqParam;
		pitch += inputs[PITCH_INPUT].getVoltage();

		float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

		// Accumulate the phase
		phase += freq * args.sampleTime;
		if (phase >= 0.5f)
			phase -= 1.f;

		
		// Audio signals are typically +/-5V
		// https://vcvrack.com/manual/VoltageStandards.html
		if(outputs[SAW_OUTPUT].isConnected())
			outputs[SAW_OUTPUT].setVoltage(5.f * SoundMath::saw(phase));
		if(outputs[SINE_OUTPUT].isConnected())
			outputs[SINE_OUTPUT].setVoltage(5.f * SoundMath::sine(phase));
		if(outputs[SQUARE_OUTPUT].isConnected())
			outputs[SQUARE_OUTPUT].setVoltage(5.f * SoundMath::square(phase, 0.5f));
		if(outputs[TRIANGLE_OUTPUT].isConnected())
			outputs[TRIANGLE_OUTPUT].setVoltage(5.f * SoundMath::triangle(phase));			
	}
};


struct VBNOWidget : ModuleWidget {
	VBNOWidget(VBNO* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VCOh-2.svg")));

		//Screws
		addChild(createWidget<ScrewBlack>(Vec(15, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewBlack>(Vec(15, 365)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 30, 365)));

		// Hard Tuning
		addParam(createParam<CKSS>(Vec(60, 77), module, VBNO::MODE_PARAM));

		// Octave
		addParam(createParam<RoundBlackSnapKnob>(Vec(8, 61), module, VBNO::OCTAVE_PARAM));
		addInput(createInput<PJ301MPort>(Vec(11, 101), module, VBNO::OCTAVE_INPUT));

		// Freq
		addParam(createParam<RoundLargeBlackKnob>(Vec(91, 61), module, VBNO::NOTE_PARAM));
		addInput(createInput<PJ301MPort>(Vec(96, 101), module, VBNO::PITCH_INPUT));

		// Fine
		addParam(createParam<RoundBlackKnob>(Vec(8, 143), module, VBNO::FINE_PARAM));
		
		// Pulse Width
		addParam(createParam<RoundBlackKnob>(Vec(91, 143), module, VBNO::PW_PARAM));
		addInput(createInput<PJ301MPort>(Vec(91, 183), module, VBNO::PW_INPUT));

		// FM
		addParam(createParam<RoundBlackKnob>(Vec(8, 208), module, VBNO::FM_PARAM));
		addInput(createInput<PJ301MPort>(Vec(11, 228), module, VBNO::FM_INPUT));

		// PWM
		addParam(createParam<RoundLargeBlackKnob>(Vec(91, 208), module, VBNO::PWM_PARAM));

		// Sync
		addInput(createInput<PJ301MPort>(Vec(80, 276), module, VBNO::SYNC_INPUT));
		

		addOutput(createOutput<PJ301MPort>(Vec(11, 320), module, VBNO::SINE_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(45, 320), module, VBNO::TRIANGLE_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(80, 320), module, VBNO::SAW_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(114, 320), module, VBNO::SQUARE_OUTPUT));
	}
};


Model* modelVCOh = createModel<VBNO, VBNOWidget>("VCOh");