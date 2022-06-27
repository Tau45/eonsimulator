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

    virtual vector<Event *> execute(Network &network, uint64_t clock) = 0;
};

#endif //EONSIMULATOR_EVENT_H