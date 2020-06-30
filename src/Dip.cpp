#include "Dip.hpp"
#include <math.h>
#include <rack.hpp>
#include "DBug.hpp"
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

void Dip::process(const ProcessArgs& args) {
    // don't waste time if there is no input
    if (!inputs[INPUT].isConnected())
        return;

    float inputV = inputs[INPUT].getVoltage();

    float lpParam = params[LP_PARAM].getValue();
    // Use Low pass CV if connected
    float lpInputV;
    if (inputs[LP_INPUT].isConnected()) {
        lpInputV = clamp10VUnipolar(inputs[LP_INPUT].getVoltage());
        lpParam = lpInputV / 10.f;
    }
    float lpFrequency = decimalToHz(lpParam);
    lpFilter.sampleRate = args.sampleRate;
    lpFilter.setCutoff(lpFrequency);
    lpFilter.process(inputV);

    float hpParam = params[HP_PARAM].getValue();
    // Use HP CV if connected
    float hpInputV;
    if (inputs[HP_INPUT].isConnected()) {
        hpInputV = clamp10VUnipolar(inputs[HP_INPUT].getVoltage());
        hpParam = hpInputV / 10.f;
    }
    float hpFrequency = decimalToHz(hpParam);
    hpFilter.sampleRate = args.sampleRate;
    hpFilter.setCutoff(hpFrequency);
    hpFilter.process(inputV);

    float outputV = clamp5VBipolar((lpFilter.output + (inputV - hpFilter.output)) / 2.f);
    outputs[OUTPUT].setVoltage(outputV);

    // Debug messages
    if (dBugConnected() && isDBugRefresh()) {
        sprintf(debugMsg[0], "LP Param: %f", lpParam);
        sprintf(debugMsg[1], "LP Freq: %f", lpFrequency);
        sprintf(debugMsg[2], "HP Param: %f", hpParam);
        sprintf(debugMsg[3], "HP Freq: %f", hpFrequency);
        sprintf(debugMsg[4], "Input Voltage: %f", inputV);
        sprintf(debugMsg[5], "Output Voltage: %f", outputV);

        sendToDBug(debugMsg);
    }
    increaseSampleCounter();
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