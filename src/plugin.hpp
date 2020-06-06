#pragma once
#include <rack.hpp>
#include "CSModuleWidget.hpp"
#include "captainssounds.hpp"
#include "components.hpp"

using namespace rack;
using namespace captainssounds;
using namespace captainssounds::components;

namespace captainssounds {
    const NVGcolor PANEL_BG_COLOR = nvgRGBA(0xdf, 0xdb, 0xda, 0xff);

    float decimalToHz(float value);
    float hzToDecimal(float value);

    // Exponential Params
    struct EQParamQuantity : ParamQuantity {
        float getDisplayValue() override;
        void setDisplayValue(float displayValue) override;
    };
}  // namespace captainssounds

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelBlank901;
extern Model* modelBlank902;
extern Model* modelBlank904;
extern Model* modelDBug;
extern Model* modelDip;
extern Model* modelIMO;
extern Model* modelMIO;
extern Model* modelNip;
extern Model* modelPow;
extern Model* modelVBNO;
