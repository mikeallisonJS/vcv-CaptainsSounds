#pragma once
#include <rack.hpp>
#include "components.hpp"
#include "CSModuleWidget.hpp"

using namespace rack;
using namespace captainssounds;
using namespace captainssounds::components;

namespace captainssounds {
    const NVGcolor PANEL_BG_COLOR = nvgRGBA(0xdf, 0xdb, 0xda, 0xff);
}

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelBlank901;
extern Model* modelBlank902;
extern Model* modelBlank904;
extern Model* modelNip;
extern Model* modelPow;
extern Model* modelVBNO;