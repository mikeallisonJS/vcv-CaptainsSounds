#include "Dip.hpp"
#include <math.h>
#include <rack.hpp>
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

void Dip::process(const ProcessArgs& args) {
    // don't waste time if there is no input
    if (!inputs[INPUT].isConnected())
        return;

    inputV = inputs[INPUT].getVoltage();
    lpFrequency = params[LP_PARAM].getValue();
    // Use Low pass CV if connected
    // if(inputs[LP_INPUT].isConnected()) {
    // 	lpInputV = inputs[LP_INPUT].getVoltage();
    // 	// TODO: figure this shit out
    // 	// lpFilter.frequency = pow((lpInputV * 10), ); //10v to 100%
    // } else {
    // 	lpFilter.frequency = params[LP_PARAM].getValue();
    // }

    hpFrequency = params[HP_PARAM].getValue();
    // Use HP CV if connected
    // if(inputs[HP_INPUT].isConnected()) {
    // 	hpInputV = inputs[HP_INPUT].getVoltage();
    // 	// hpFilter.frequency = pow((hpInputV * 10), ); //10v to 100%
    // } else {
    // 	hpFilter.frequency = params[LP_PARAM].getValue();
    // }

    // if (hpFrequency <= lpFrequency) {
    //     outputs[OUTPUT].setVoltage(inputV);
    //     return;
    // }

    lpFilter.sampleRate = args.sampleRate;
    lpFilter.setCutoff(lpFrequency);
    lpFilter.process(inputV);

    hpFilter.sampleRate = args.sampleRate;
    hpFilter.setCutoff(hpFrequency);
    hpFilter.process(inputV);

    float lpOutputV = lpFilter.output;
    float hpOutputV = hpFilter.highpass;

    outputV = hpOutputV;  // lpOutputV + ;
    outputs[OUTPUT].setVoltage(outputV);
}

struct DipWidget : CSModuleWidget {
    DipWidget(Dip* module) {
        hp = 2;
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Dip.svg")));
        addScrews();

        addParamKnobWithInput(0, Dip::LP_PARAM, Dip::LP_INPUT);
        addParamKnobWithInput(1, Dip::HP_PARAM, Dip::HP_INPUT);

        addInputJack(Dip::INPUT);
        addOutputJack(Dip::OUTPUT);
    }
};

Model* modelDip = createModel<Dip, DipWidget>("Dip");