#pragma once
#include <rack.hpp>
#include <string>
#include "DBug.hpp"

using namespace rack;

namespace captainssounds {
    struct CSModule : Module {
        static const int NUM_POLY_CHANNELS = 16;
        DBugMessages debugMsg;
        int dBugRefreshRate = 16;
        int sampleCount = dBugRefreshRate;

        CSModule() {
            // Initialize debug message buffer
            for (int i = 0; i < DBUG_MAX_LINES; i++) {
                debugMsg[i][0] = '\0';
            }
            // No buffers published by default; sender will set producer at send time
            rightExpander.producerMessage = nullptr;
            rightExpander.consumerMessage = nullptr;
        }

        bool dBugConnected();
        void increaseSampleCounter();
        bool isDBugRefresh();
        void resetSampleCounter();
        void sendToDBug(DBugMessages msgs);
    };
}  // namespace captainssounds