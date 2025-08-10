#include "CSModule.hpp"
#include "DBug.hpp"
#include <cstring>

using namespace captainssounds;

bool CSModule::dBugConnected() {
    return (rightExpander.module && rightExpander.module->model == modelDBug);
}

bool CSModule::isDBugRefresh() {
    return sampleCount >= dBugRefreshRate;
}

void CSModule::increaseSampleCounter() {
    sampleCount++;
}

void CSModule::resetSampleCounter() {
    sampleCount = 0;
}

void CSModule::sendToDBug(DBugMessages msgs) {
    if (dBugConnected() && isDBugRefresh()) {
        // Copy source lines into our stable local buffer
        for (int i = 0; i < DBUG_MAX_LINES; i++) {
            if (msgs[i][0] != '\0') {
                std::strncpy(debugMsg[i], msgs[i], DBUG_MAX_CHARS - 1);
                debugMsg[i][DBUG_MAX_CHARS - 1] = '\0';
            } else {
                debugMsg[i][0] = '\0';
            }
        }
        // Place a sentinel in the final line so the reader can validate the buffer
        std::strncpy(debugMsg[DBUG_MAX_LINES - 1], "CSDBG", DBUG_MAX_CHARS - 1);
        debugMsg[DBUG_MAX_LINES - 1][DBUG_MAX_CHARS - 1] = '\0';
        // Minimal send trace
        DEBUG("CSModule: first line -> %s", debugMsg[0]);
        rightExpander.producerMessage = &debugMsg;
        rightExpander.messageFlipRequested = true;
        resetSampleCounter();
    }
}