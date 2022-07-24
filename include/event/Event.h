#pragma once
#ifndef EONSIMULATOR_EVENT_H
#define EONSIMULATOR_EVENT_H

#include <iostream>
#include "../network/Network.h"
#include "../tools/Generator.h"

class Event {
public:
    Generator *generator;
    uint64_t occurrenceTime;
    uint8_t priority;
    Connection *connection;

    struct EventComparator {
        bool operator()(const Event *a, const Event *b) {
            return a->occurrenceTime == b->occurrenceTime
                   ? a->priority > b->priority
                   : a->occurrenceTime > b->occurrenceTime;
        }
    };

    virtual void execute(Network &network, uint64_t clock, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) = 0;
};

#endif //EONSIMULATOR_EVENT_H