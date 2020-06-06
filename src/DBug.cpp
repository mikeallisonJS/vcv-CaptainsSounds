#include "DBug.hpp"
#include <math.h>
#include <rack.hpp>
#include <sstream>
#include <string>
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

struct DBugWidget : CSModuleWidget {
    DBugWidget(DBug* module) {
        hp = 8;
        setModule(module);
        box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
        {
            auto panel = new SvgPanel();
            panel->box.size = box.size;
            panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/90hBlank-8.svg")));
            addChild(panel);
        }
        {
            auto inset = Vec(10, 25);
            auto size = Vec(box.size.x - 2 * inset.x, 320);
            auto display = new DBugDisplay(module);
            display->box.pos = inset;
            display->box.size = size;
            addChild(display);
        }

        addScrews();
    }
};

void DBugDisplay::drawScreen(const DrawArgs& args) {
    nvgSave(args.vg);
    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, box.size.x - 5, box.size.y);
    nvgFillColor(args.vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
    nvgFill(args.vg);
    nvgStrokeColor(args.vg, nvgRGBA(0xc0, 0xc0, 0xc0, 0xff));
    nvgStroke(args.vg);
    nvgRestore(args.vg);
}

void DBugDisplay::draw(const DrawArgs& args) {
    drawScreen(args);

    if (module && module->leftExpander.module) {
        nvgSave(args.vg);
        nvgTranslate(args.vg, 0, 0);
        nvgRotate(args.vg, (0.0F));
        nvgFontSize(args.vg, 12);
        nvgFontFaceId(args.vg, font->handle);
        nvgFillColor(args.vg, nvgRGBA(0x00, 0xFF, 0x00, 0xff));
        int yOffset = 15;
        DBugMessagesPtr incomingMessage = (DBugMessagesPtr)module->leftExpander.consumerMessage;
        for (int i = 0; i < DBUG_MAX_LINES; i++) {
            const char* msg = incomingMessage[i];
            // DEBUG("display %s", msg);

            if (strlen(msg) > 0)
                nvgText(args.vg, 5, 15 + (i * yOffset), msg, NULL);
        }

        nvgRestore(args.vg);
    }
}

Model* modelDBug = createModel<DBug, DBugWidget>("DBug");