#pragma once
#include <string>
#include "DBug.hpp"
#include "rack.hpp"

using namespace rack;

namespace captainssounds {
    struct CSModule : Module {
        CSModule() {}

        bool dBugConnected();
        void sendToDBug(DBugMessages msgs);
    };
}  // namespace captainssounds