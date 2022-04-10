#pragma once
#ifndef EONSIMULATOR_EVENT_H
#define EONSIMULATOR_EVENT_H

#include <iostream>
#include "../network/Network.h"

class Event {
public:
    uint64_t occurrenceTime;

    virtual void init() = 0;

    virtual void execute(Network &network) = 0;
};

#endif //EONSIMULATOR_EVENT_H