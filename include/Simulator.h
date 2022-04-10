#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "event/Event.h"
#include "tools/EventComparator.h"

using namespace std;

class Simulator {
    uint64_t clock;
    Network *network;
    priority_queue<Event *, vector<Event *>, EventComparator> eventQueue;

    uint64_t internalBlockingCount;
    uint64_t externalBlockingCount;
public:
    Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H