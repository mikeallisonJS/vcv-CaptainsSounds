#pragma once
#include <rack.hpp>
#include <regex>
#include <string>
#include "captainssounds.hpp"
#include "plugin.hpp"

using namespace captainssounds;

namespace captainssounds {
    const int DBUG_MAX_LINES = 20;
    const int DBUG_MAX_CHARS = 256;
    typedef char** DBugMessagesPtr;
    typedef char DBugMessages[DBUG_MAX_LINES][DBUG_MAX_CHARS];

    struct DBug : Module {
        enum ParamIds {
            REFRESH_PARAM,
            NUM_PARAMS
        };
        const std::string reg = R"(a-zA-Z\d\s!@#$%&*:.)";

        DBug() {
            leftExpander.consumerMessage = new DBugMessages;
            leftExpander.producerMessage = new DBugMessages;
            config(NUM_PARAMS, 0, 0);
        }
    };

    struct DBugDisplay : TransparentWidget {
        std::shared_ptr<Font> font;
        DBug* module;
        DBugMessagesPtr incomingMessage;
        const int yOffset = 10;

        DBugDisplay(DBug* dbugmodule) {
            module = dbugmodule;
            font = APP->window->loadFont(asset::plugin(pluginInstance, "res/fonts/nunito/Nunito-Bold.ttf"));
        }

        void drawScreen(const DrawArgs& args);
        void draw(const DrawArgs& args) override;

        bool isConnected();
        bool isSafe();
    };
}  // namespace captainssounds

extern Model* modelDBug;
