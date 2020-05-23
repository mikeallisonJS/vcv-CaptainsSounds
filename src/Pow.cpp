#include "captainssounds.hpp"
#include "Pow.hpp"

using namespace captainssounds;

void Pow::process(const ProcessArgs& args) {
	// Uni-polar
	uniParam = params[UNI_PARAM].getValue() / 10; // 10V to decimal
	if(inputs[UNI_INPUT].isConnected()) {
		uniInputV = clamp10VUnipolar(inputs[UNI_INPUT].getVoltage()) ; 
		uniOutputV = uniInputV * uniParam;
	} else {
		uniOutputV = 10.f * uniParam;
	}
	outputs[UNI_OUTPUT].setVoltage(uniOutputV);
	if(lightDivider.process())
		lights[UNI_LIGHT].setSmoothBrightness(uniOutputV / 10, args.sampleTime * lightDivider.getDivision());
	
	// Bi-polar
	biParam = params[BI_PARAM].getValue() / 5; // 5V to decimal
	if(inputs[BI_INPUT].isConnected()) {
		biInputV = clamp5VBipolar(inputs[BI_INPUT].getVoltage());
		biOutputV = biInputV * biParam;
	} else {
		biOutputV = 5.f * biParam;
	}
	outputs[BI_OUTPUT].setVoltage(biOutputV);
	if(lightDivider.process()) {
		lights[BI_LIGHT].setSmoothBrightness(biOutputV / 5, args.sampleTime * lightDivider.getDivision());
		lights[BI_LIGHT + 1].setSmoothBrightness(-biOutputV / 5, args.sampleTime * lightDivider.getDivision());
	}
}

struct PowWidget : CSSplitModuleWidget {
	PowWidget(Pow* module) {
		hp = 2;
		setModule(module);		

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Pow.svg")));
		addScrews();

		// Uni
		addParamKnobWithInput(0, Pow::UNI_PARAM, Pow::UNI_INPUT);
		addLight<SmallLight<GreenLight>>(45, Pow::UNI_LIGHT);
		addOutputJack(0, Pow::UNI_OUTPUT);

		// BI
		addParamKnobWithInput(1, Pow::BI_PARAM, Pow::BI_INPUT);
		addLight<SmallLight<GreenRedLight>>(210, Pow::BI_LIGHT);
		addOutputJack(1, Pow::BI_OUTPUT);
	}
};


Model* modelPow = createModel<Pow, PowWidget>("Pow");