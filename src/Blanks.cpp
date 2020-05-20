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

	struct Blank901Widget : ModuleWidget {
		Blank901Widget(Module* module) {
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-1.svg")));

			//Screws
			addChild(createWidget<ScrewBlack>(Vec(0, SCREW_TOP_Y_POS)));
			addChild(createWidget<ScrewBlack>(Vec(0, SCREW_BOTTOM_Y_POS)));
		}
	};

	struct Blank902Widget : ModuleWidget {
		Blank902Widget(Module* module) {
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-2.svg")));

			//Screws
			addChild(createWidget<ScrewBlack>(Vec(box.size.x/4, SCREW_TOP_Y_POS)));
			addChild(createWidget<ScrewBlack>(Vec(box.size.x/4, SCREW_BOTTOM_Y_POS)));
		}
	};
	
	struct Blank904Widget : ModuleWidget {
		Blank904Widget(Module* module) {
			setModule(module);
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-4.svg")));

			//Screws
			addChild(createWidget<ScrewBlack>(Vec(1, SCREW_TOP_Y_POS)));
			addChild(createWidget<ScrewBlack>(Vec(1, SCREW_BOTTOM_Y_POS)));
			addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, SCREW_TOP_Y_POS)));
			addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, SCREW_BOTTOM_Y_POS)));
			
		}
	};
}

Model* modelBlank901 = createModel<Blank901, Blank901Widget>("Blank901");
Model* modelBlank902 = createModel<Blank904, Blank902Widget>("Blank902");
Model* modelBlank904 = createModel<Blank904, Blank904Widget>("Blank904");