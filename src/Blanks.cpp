#include "Blanks.hpp"

// TODO: Remove need for full svg panels, use draw methods and logo svg. Possibly resizeable

namespace captainssounds {
	// struct BlankWidget : ModuleWidget {
	// 	BlankWidget() {}
	// 	BlankWidget(Module* module) {
	// 		setModule(module);		
	// 	}
		// void draw(const DrawArgs& args) override {
		// 	nvgFillColor(args.vg, captainssounds::PANEL_BG_COLOR);
		// 	nvgFill(args.vg);
		// }
	// };

	struct Blank901Widget : CSModuleWidget {
		Blank901Widget(Module* module) {
			hp = 1;
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-1.svg")));
			addScrews();
		}
	};

	struct Blank902Widget : CSModuleWidget {
		Blank902Widget(Module* module) {
			hp = 2;
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-2.svg")));
			addScrews();
		}
	};
	
	struct Blank904Widget : CSModuleWidget {
		Blank904Widget(Module* module) {
			hp = 4;
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-4.svg")));
			addScrews();
		}
	};
}

Model* modelBlank901 = createModel<Blank901, Blank901Widget>("Blank901");
Model* modelBlank902 = createModel<Blank904, Blank902Widget>("Blank902");
Model* modelBlank904 = createModel<Blank904, Blank904Widget>("Blank904");