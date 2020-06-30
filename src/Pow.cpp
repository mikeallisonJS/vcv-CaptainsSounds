#include "Pow.hpp"
#include "captainssounds.hpp"

using namespace captainssounds;

void Pow::process(const ProcessArgs& args) {
    // Connections
    uniConnected = inputs[UNI_INPUT].isConnected();
    biConnected = inputs[BI_INPUT].isConnected();

    //Params
    uniParam = params[UNI_PARAM].getValue() / 10;  // 10V to decimal
    biParam = params[BI_PARAM].getValue() / 5;     // 5V to decimal

    numInputsUni = uniConnected ? inputs[UNI_INPUT].getChannels() : NUM_POLY_CHANNELS;
    numInputsBi = biConnected ? inputs[BI_INPUT].getChannels() : NUM_POLY_CHANNELS;

    outputs[UNI_OUTPUT].setChannels(numInputsUni);
    outputs[BI_OUTPUT].setChannels(numInputsBi);

    for (int i = 0; i < numInputsUni; i++) {
        // Uni-polar
        if (uniConnected) {
            uniInputV = clamp10VUnipolar(inputs[UNI_INPUT].getVoltage(i));
            uniOutputV = uniInputV * uniParam;
        } else {
            uniOutputV = 10.f * uniParam;
        }
        outputs[UNI_OUTPUT].setVoltage(uniOutputV, i);
        if (i == 0 && lightDivider.process())
            lights[UNI_LIGHT].setSmoothBrightness(uniOutputV / 10, args.sampleTime * lightDivider.getDivision());
    }
    for (int i = 0; i < numInputsBi; i++) {
        // Bi-polar
        if (biConnected) {
            biInputV = clamp5VBipolar(inputs[BI_INPUT].getVoltage(i));
            biOutputV = biInputV * biParam;
        } else {
            biOutputV = 5.f * biParam;
        }
        outputs[BI_OUTPUT].setVoltage(biOutputV, i);
        if (i == 0 && lightDivider.process()) {
            lights[BI_LIGHT].setSmoothBrightness(biOutputV / 5, args.sampleTime * lightDivider.getDivision());
            lights[BI_LIGHT + 1].setSmoothBrightness(-biOutputV / 5, args.sampleTime * lightDivider.getDivision());
        }
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