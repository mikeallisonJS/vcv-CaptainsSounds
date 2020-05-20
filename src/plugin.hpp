#pragma once
#include <rack.hpp>
#include "components.hpp"

using namespace rack;
using namespace captainssounds;
using namespace captainssounds::components;


namespace captainssounds {
    const int LOGO_Y_POS = 345;
    const NVGcolor PANEL_BG_COLOR = nvgRGBA(0xdf, 0xdb, 0xda, 0xff);
    const int SCREW_BOTTOM_Y_POS = 365;
    const int SCREW_TOP_Y_POS = 0;
}

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelBlank901;
extern Model* modelBlank902;
extern Model* modelBlank904;
extern Model* modelVBNO;



