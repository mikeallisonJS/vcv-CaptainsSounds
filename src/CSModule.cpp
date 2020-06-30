#include "CSModule.hpp"
#include "DBug.hpp"

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
        DBugMessagesPtr message = (DBugMessagesPtr)rightExpander.module->leftExpander.producerMessage;
        for (int i = 0; i < DBUG_MAX_LINES; i++) {
            message[i] = msgs[i];
        }
        rightExpander.module->leftExpander.messageFlipRequested = true;
    }
    resetSampleCounter();
}