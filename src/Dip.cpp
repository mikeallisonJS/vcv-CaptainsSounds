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

    // Debug messages (temporary always-on test to validate DBug path)
    {
        static int logCounter = 0;
        if ((logCounter++ & 0x3FFF) == 0) {
            DEBUG("Dip: inputConnected=1 (writing debugMsg)");
        }
        DEBUG("Dip::process sending");
        snprintf(debugMsg[0], DBUG_MAX_CHARS, "%s", "TEST-DIP");
        snprintf(debugMsg[1], DBUG_MAX_CHARS, "LP Param: %.4f", lpParam);
        snprintf(debugMsg[2], DBUG_MAX_CHARS, "LP Freq: %.2f", lpFrequency);
        snprintf(debugMsg[3], DBUG_MAX_CHARS, "HP Param: %.4f", hpParam);
        snprintf(debugMsg[4], DBUG_MAX_CHARS, "HP Freq: %.2f", hpFrequency);
        snprintf(debugMsg[5], DBUG_MAX_CHARS, "In: %.3f  Out: %.3f", inputV, outputV);
        for (int i = 6; i < DBUG_MAX_LINES; i++) debugMsg[i][0] = '\0';
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