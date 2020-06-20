#include "DBug.hpp"
#include <math.h>
#include <rack.hpp>
#include <sstream>
#include <string>
#include "CSModule.hpp"
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

void DBug::reset() {
    leftExpander.consumerMessage = new DBugMessages;
    leftExpander.producerMessage = new DBugMessages;
}

void DBug::process(const ProcessArgs& args) {
    // redrawSplit = params[REFRESH_PARAM].getValue();
}

struct DBugWidget : CSModuleWidget {
    const Vec offset = Vec(8, 30);
    const Vec displaySize = Vec(288, 220);
    DBugWidget(DBug* module) {
        hp = 20;
        setModule(module);
        box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

        auto panel = new SvgPanel();
        panel->box.size = box.size;
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DBug.svg")));
        addChild(panel);

        auto display = new DBugDisplay(module);
        display->box.pos = offset;
        display->box.size = displaySize;
        addChild(display);

        // addParam(createParam<Round909Knob>(Vec(10, 250), module, DBug::REFRESH_PARAM));

        addScrews();
    }
};

void DBugDisplay::drawScreen(const DrawArgs& args) {
    nvgSave(args.vg);
    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, box.size.x - 5, box.size.y);
    nvgFillColor(args.vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
    nvgFill(args.vg);
    nvgRestore(args.vg);
}

void DBugDisplay::draw(const DrawArgs& args) {
    drawScreen(args);

    if (module && module->leftExpander.module && ((CSModule*)module->leftExpander.module)->dBugConnected() && typeid(module->incomingMessage).name() == typeid(DBugMessagesPtr).name()) {
        nvgFontSize(args.vg, 9);
        nvgFontFaceId(args.vg, font->handle);
        nvgFillColor(args.vg, nvgRGBA(0x00, 0xFF, 0x00, 0xff));
        // if (redrawCount >= module->redrawSplit) {
        // redrawCount = 0;  //reset
        // }
        // redrawCount++;

        nvgSave(args.vg);
        for (int i = 0; i < (int)sizeof(module->incomingMessage); i++) {
            const char* msg = module->incomingMessage[i];
            if (msg != nullptr)
                nvgText(args.vg, 5, 15 + (i * yOffset), msg, NULL);
        }
        nvgRestore(args.vg);
        Widget::draw(args);
    }
}
Model* modelDBug = createModel<DBug, DBugWidget>("DBug");