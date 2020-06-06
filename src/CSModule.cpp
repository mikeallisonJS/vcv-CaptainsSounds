#include "CSModule.hpp"
#include <algorithm>
#include <string>
#include "DBug.hpp"

using namespace captainssounds;

bool CSModule::dBugConnected() {
    return (rightExpander.module && rightExpander.module->model == modelDBug);
}

void CSModule::sendToDBug(DBugMessages msgs) {
    if (dBugConnected()) {
        DBugMessagesPtr outgoingMsg = (DBugMessagesPtr)rightExpander.module->leftExpander.producerMessage;
        for (int i = 0; i < DBUG_MAX_LINES; i++) {
            // DEBUG("sent to DBug %s", msgs[i]);
            outgoingMsg[i] = msgs[i];
        }
        rightExpander.module->leftExpander.messageFlipRequested = true;
    }
}