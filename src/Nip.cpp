#include "Nip.hpp"
#include "captainssounds.hpp"

using namespace captainssounds;

void Nip::process(const ProcessArgs& args) {
    // Bypass without input
    if (!inputs[INPUT].isConnected())
        return;

    float gainParam = params[GAIN_PARAM].getValue() / 100;  // 100% to decimal
    float ceilParam = params[CEIL_PARAM].getValue() / 100;  // 100% to decimal

    //Get channel count
    int numChannels = inputs[INPUT].getChannels();
    outputs[OUTPUT].setChannels(numChannels);

    // handle polyphony
    for (int i = 0; i < numChannels; i++) {
        // Use Gain CV if connected
        float gainInputV;
        float gainValue;
        if (inputs[GAIN_INPUT].isConnected()) {
            gainInputV = clamp10VUnipolar(inputs[GAIN_INPUT].getPolyVoltage(i)) * gainParam;
            gainValue = gainInputV / 10;  // 10V to decimal
        } else {
            gainValue = gainParam;
        }

        // Use Ceiling CV if connected
        float ceilInputV;
        float ceilValue;

        if (inputs[CEIL_INPUT].isConnected()) {
            ceilInputV = clamp10VUnipolar(inputs[CEIL_INPUT].getPolyVoltage(i)) / 10;  //10V to decimal
            ceilValue = ceilInputV * ceilParam * 5;                                    //decimal to 5V
        } else {
            ceilValue = ceilParam * 5;  // 100% to 5V
        }

        //Get Input
        float inputV = clamp5VBipolar(inputs[INPUT].getVoltage(i));

        // Process
        float inputBuffer[UPSAMPLES];
        float outputBuffer[UPSAMPLES];
        float clippedOutputBuffer[UPSAMPLES];

        inputUpsampler[i].process(inputV, inputBuffer);
        for (int j = 0; j < UPSAMPLES; j++) {
            outputBuffer[j] = clamp5VBipolar(inputBuffer[j] * gainValue);
            clippedOutputBuffer[j] = tclamp(outputBuffer[j], -ceilValue, ceilValue);
        }
        float output = outputDecimator[i].process(outputBuffer);
        float clippedOutput = clippedOutputDecimator[i].process(clippedOutputBuffer);

        // Lights (each light is 3 enum lights)
        if (i == 0 && lightDivider.process()) {  //only display 1st value lights
            for (float j = 0.00f; j < 5.f; j += .5f) {
                int index = j * 3 * 2;  //3 lights 2 steps per volt
                float red = output > j && ceilValue <= j;
                float green = !red && output > j ? 1.f : 0.f;
                lights[index + 0].setSmoothBrightness(red, args.sampleTime * lightDivider.getDivision());
                lights[index + 1].setSmoothBrightness(green, args.sampleTime * lightDivider.getDivision());
                lights[index + 2].setBrightness(0.f);
            }
        }
        // Output
        outputs[OUTPUT].setVoltage(clippedOutput, i);

        // DBug
        // if (dBugConnected() && isDBugRefresh())
        //     sprintf(debugMsg[i], "Channel %d Gain %f Ceiling %f In %f Out %f", i, gainValue, ceilValue, inputV, clippedOutput);
    }

    // DBug
    // if (dBugConnected() && isDBugRefresh())
    //     sendToDBug(debugMsg);

    increaseSampleCounter();
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
            addLight<SmallLight<RedGreenBlueLight>>(yPos, i * 3);
            yPos -= 10;
        }

        // Input
        addInputJack(Nip::INPUT);

        // Output
        addOutputJack(Nip::OUTPUT);
    }
};

Model* modelNip = createModel<Nip, NipWidget>("Nip");