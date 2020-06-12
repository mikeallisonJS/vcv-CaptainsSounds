#pragma once
#include <rack.hpp>
#include "captainssounds.hpp"
#include "plugin.hpp"

using namespace captainssounds;

namespace captainssounds {
    const int DBUG_MAX_LINES = 20;
    const int DBUG_MAX_CHARS = 256;
    // const int DBUG_MAX_REDRAW_COUNT = 2147400000;  //max int minus a few cause it went negative
    typedef char** DBugMessagesPtr;
    typedef char DBugMessages[DBUG_MAX_LINES][DBUG_MAX_CHARS];

    //TODO: Add working refresh knob
    struct DBug : Module {
        // enum ParamIds {
        //     REFRESH_PARAM,
        //     NUM_PARAMS
        // };
        // int redrawSplit = 1;

        DBug() {
            reset();
            // config(NUM_PARAMS, 0, 0);
            // configParam(REFRESH_PARAM, DBUG_MAX_REDRAW_COUNT, 1, (redrawSplit), "Refresh Time", "frame split");
        }
        ~DBug() {
            reset();
        }

        void process(const ProcessArgs& args) override;
        void reset();
    };

    struct DBugDisplay : TransparentWidget {
        std::shared_ptr<Font> font;
        DBug* module;
        const int yOffset = 10;
        // int redrawCount = DBUG_MAX_REDRAW_COUNT;  // start at max to force initial data
        DBugMessagesPtr incomingMessage;

        DBugDisplay(DBug* dbugmodule) {
            module = dbugmodule;
            font = APP->window->loadFont(asset::plugin(pluginInstance, "res/fonts/nunito/Nunito-Bold.ttf"));
        }
        void drawScreen(const DrawArgs& args);
        void draw(const DrawArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelDBug;
