#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
    pluginInstance = p;

    // Add modules here
    p->addModel(modelBlank901);
    p->addModel(modelBlank902);
    p->addModel(modelBlank904);
    p->addModel(modelDBug);
    p->addModel(modelDip);
    p->addModel(modelIMO);
    p->addModel(modelMIO);
    p->addModel(modelNip);
    p->addModel(modelPow);
    p->addModel(modelVBNO);

    // Any other plugin initialization may go here.
    // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

// TODO: Make this suck less
float captainssounds::decimalToHz(float value) {
    return tclamp(MIN_FILTER_HZ * powf(FILTER_PARAM_INCREMENT, value * 100), (float)MIN_FILTER_HZ, (float)MAX_FILTER_HZ);
}

float captainssounds::hzToDecimal(float value) {
    return tclamp(powf(FILTER_PARAM_INCREMENT, value / 100.f) / (float)MIN_FILTER_HZ, 0.f, 1.f);
}

float captainssounds::EQParamQuantity::getDisplayValue() {
    float value = getValue();
    if (!module)
        return value;
    return decimalToHz(value);
}

void captainssounds::EQParamQuantity::setDisplayValue(float displayValue) {
    if (!module)
        return;

    setValue(hzToDecimal(displayValue));
}