#pragma once
#ifndef EONSIMULATOR_EVENT_H
#define EONSIMULATOR_EVENT_H

#include <iostream>
#include "../network/Network.h"

class Event {
protected:
    double occurrenceTime;
    Connection connection;
public:
    class EventComparator {
    public:
        bool operator()(const Event *a, const Event *b) {
            return a->occurrenceTime > b->occurrenceTime;
        }
    };

    virtual void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) = 0;

    double getOccurrenceTime() { return occurrenceTime; }
};

#endif //EONSIMULATOR_EVENT_H