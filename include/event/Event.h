#pragma once
#ifndef EONSIMULATOR_EVENT_H
#define EONSIMULATOR_EVENT_H

#include <iostream>
#include "../network/Network.h"

class Event {
public:
    double occurrenceTime;
    Connection *connection;

    class EventComparator {
    public:
        bool operator()(const Event *a, const Event *b) {
            return a->occurrenceTime > b->occurrenceTime;
        }
    };

    virtual void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) = 0;
};

#endif //EONSIMULATOR_EVENT_H