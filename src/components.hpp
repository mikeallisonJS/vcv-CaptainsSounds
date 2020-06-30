#pragma once
#include <rack.hpp>

using namespace rack;
using namespace rack::componentlibrary;

extern Plugin* pluginInstance;

namespace captainssounds {
    namespace components {
        struct Round909Knob : RoundKnob {
            Round909Knob() {
                setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Components/Round909Knob.svg")));
            }
        };
        struct Round909SnapKnob : Round909Knob {
            Round909SnapKnob() {
                snap = true;
            }
        };
        struct Round909Port : app::SvgPort {
            Round909Port() {
                setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Components/Round909Jack.svg")));
            }
        };

        struct CSLogo : app::SvgScrew {
            CSLogo() {
                setSvg(APP->window->loadSvg(asset::system("res/CSlogo.svg")));
            }
        };

        struct SmallRound909Knob : RoundKnob {
            SmallRound909Knob() {
                setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Components/SmallRound909Knob.svg")));
            }
        };
        struct SmallRound909SnapKnob : SmallRound909Knob {
            SmallRound909SnapKnob() {
                snap = true;
            }
        };
    }  // namespace components
}  // namespace captainssounds