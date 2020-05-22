#include "plugin.hpp"
#include "Nip.hpp"

using namespace captainssounds;

void Nip::process(const ProcessArgs& args) {
	// Bypass without input
	if (!inputs[INPUT].isConnected())
		return;
	
	// Use Gain CV if connected
	gainParam = params[GAIN_PARAM].getValue() / 100; // 100% to decimal
	if(inputs[GAIN_INPUT].isConnected()) {
		gainInputV = clamp10VUnipolar(inputs[GAIN_INPUT].getVoltage()) * gainParam;
		gainValue = gainInputV / 10; // 10V to decimal
	} else {
		gainValue = gainParam; 
	}

	// Use Ceiling CV if connected
	ceilParam = params[CEIL_PARAM].getValue() / 100; // 100% to decimal
	if(inputs[CEIL_INPUT].isConnected()) {
		ceilInputV = clamp10VUnipolar(inputs[CEIL_INPUT].getVoltage()) / 10; //10V to decimal
		ceilValue = ceilInputV * ceilParam * 5;  //decimal to 5V
	} else {
		ceilValue = ceilParam * 5; // 100% to 5V
	}
	
	//Get Input
	inputV = clamp5VBipolar(inputs[INPUT].getVoltage());
	
	// Process
	output = clamp5VBipolar(inputV * gainValue);
	
	// Lights (each light is 3 enum lights)
	if(lightDivider.process()) {
		for (float i = 0.00f; i < 5.f; i += .5f) {			
			int index = i * 3 * 2; //3 lights 2 steps per volt
			float red = output > i && ceilValue <= i;
			float green = !red && output > i ? 1.f : 0.f;
			lights[index + 0].setSmoothBrightness(red, args.sampleTime * lightDivider.getDivision());
			lights[index + 1].setSmoothBrightness(green, args.sampleTime * lightDivider.getDivision());
			lights[index + 2].setBrightness(0.f);
		}
	}

	// Process ceiling
	output = clamp(output, -ceilValue, ceilValue);

	// Output 
	outputs[OUTPUT].setVoltage(output);
}

struct NipWidget : CSModuleWidget {
	NipWidget(Nip* module) {
		hp = 2;
		setModule(module);		

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Nip.svg")));
		addScrews();

		// Gain
		addParamKnobWithInput(0, Nip::GAIN_PARAM, Nip::GAIN_INPUT);

		// Ceiling
		addParamKnobWithInput(1, Nip::CEIL_PARAM, Nip::CEIL_INPUT);

		// Lights
		int yPos = 255;
		for (int i = 0; i < 10; i++) {			
			addChild(createLight<SmallLight<RedGreenBlueLight>>(Vec(12, yPos), module, i * 3));
			yPos -= 10;
		}
				
		// Input
		addInputJack(Nip::INPUT);
		
        // Output
		addOutputJack(Nip::OUTPUT);
	}
};


Model* modelNip = createModel<Nip, NipWidget>("Nip");