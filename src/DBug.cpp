#include "DBug.hpp"
#include <math.h>
#include <rack.hpp>
#include <regex>
#include <string>
#include "CSModule.hpp"
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

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

    // Check for module &  dbug on dbug bombs
    DEBUG("DBug: draw called, isConnected=%d", isConnected());
    if (isConnected() && isSafe()) {
        // Draw only from left module's public debug buffer (simplify path)
        CSModule* left = dynamic_cast<CSModule*>(module->leftExpander.module);
        if (!left) {
            Widget::draw(args);
            return;
        }
        nvgSave(args.vg);
        nvgFontSize(args.vg, 9);
        nvgFontFaceId(args.vg, font->handle);
        nvgFillColor(args.vg, nvgRGBA(0x00, 0xFF, 0x00, 0xff));
        int drawnCount = 0;
        for (int i = 0; i < DBUG_MAX_LINES; i++) {
            const char* line = left->debugMsg[i];
            if (!line) continue;
            char safe[DBUG_MAX_CHARS];
            int j = 0;
            for (; j < DBUG_MAX_CHARS - 1 && line[j] != '\0'; j++) {
                unsigned char c = (unsigned char) line[j];
                if (c >= 32 && c <= 126) safe[j] = (char) c; else safe[j] = ' ';
            }
            safe[j] = '\0';
            if (safe[0] == '\0') continue;
            nvgText(args.vg, 5, 15 + (i * yOffset), safe, NULL);
            drawnCount++;
        }
        if (drawnCount == 0) {
            nvgText(args.vg, 5, 15, "DBUG ONLINE - awaiting messages", NULL);
        }
        nvgRestore(args.vg);
    }
    Widget::draw(args);
}

bool DBugDisplay::isConnected() {
    return module && module->leftExpander.module;
}

bool DBugDisplay::isSafe() {
    if (!module)
        return false;
    Module* left = module->leftExpander.module;
    if (!left)
        return false;
    if (left->model == modelDBug)
        return false;
    return dynamic_cast<CSModule*>(left) != nullptr;
}

Model* modelDBug = createModel<DBug, DBugWidget>("DBug");