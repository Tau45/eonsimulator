#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "../include/network/Benes4x4.h"
#include "event/Event.h"
#include "tools/EventComparator.h"

using namespace std;

class Simulator {
    uint64_t clock;
    Network *network;
    uint64_t connectionId;
    priority_queue<Event *, vector<Event *>, EventComparator> eventQueue;

    uint64_t callsToGenerate;
    uint64_t callsGenerated;

    uint64_t internalBlockingCount;
    uint64_t externalBlockingCount;
public:
    Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H