#pragma once
#include <rack.hpp>
#include <string>
#include "captainssounds.hpp"
#include "plugin.hpp"

using namespace captainssounds;

namespace captainssounds {
    const int DBUG_MAX_LINES = 20;
    const int DBUG_MAX_CHARS = 100;
    typedef char** DBugMessagesPtr;
    typedef char DBugMessages[DBUG_MAX_LINES][DBUG_MAX_CHARS];

    struct DBug : Module {
        // DBugMessages leftMessages[2] = {};
        DBug() {
            leftExpander.consumerMessage = new DBugMessages;
            leftExpander.producerMessage = new DBugMessages;
        }
        ~DBug() {
            leftExpander.consumerMessage = new DBugMessages;
            leftExpander.producerMessage = new DBugMessages;
        }
    };

    struct DBugDisplay : TransparentWidget {
        std::shared_ptr<Font> font;
        Module* module;
        DBugDisplay(DBug* dbugmodule) {
            module = dbugmodule;
            font = APP->window->loadFont(asset::plugin(pluginInstance, "res/fonts/nunito/Nunito-Bold.ttf"));
        }
        void drawScreen(const DrawArgs& args);
        void draw(const DrawArgs& args) override;
    };
}  // namespace captainssounds

extern Model* modelDBug;
