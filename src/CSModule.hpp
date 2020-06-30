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

        CSModule() {}

        bool dBugConnected();
        void increaseSampleCounter();
        bool isDBugRefresh();
        void resetSampleCounter();
        void sendToDBug(DBugMessages msgs);
    };
}  // namespace captainssounds