#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "network/structures/Benes4x4.h"
#include "event/Event.h"
#include "event/EventNewCallArrival.h"
#include "event/EventCallServiceTermination.h"
#include "tools/EventComparator.h"

using namespace std;

class Simulator {
    uint64_t clock;
    Network *network;
    priority_queue<Event *, vector<Event *>, EventComparator> eventQueue;

    uint64_t callsToGenerate;
    uint64_t callsGenerated;
public:
    Simulator();

    void run();

    uint64_t getInternalBlocksCount();

    uint64_t getExternalBlocksCount();
};

#endif //EONSIMULATOR_SIMULATOR_H