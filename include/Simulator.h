#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "network/structures/Benes4x4.h"
#include "network/structures/SingleLink.h"
#include "event/Event.h"
#include "event/EventNewCallArrivalErlangClass.h"
#include "event/EventCallServiceTermination.h"
#include "tools/EventComparator.h"
#include "Generator.h"

using namespace std;

class Simulator {
    uint64_t clock;
    Network *network;
    priority_queue<Event *, vector<Event *>, EventComparator> eventQueue;

    uint64_t callsToGenerate;
    uint64_t callsGenerated;

    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;

    Generator *generator;
public:
    Simulator(uint64_t callsTarget, int32_t x, double a);

    ~Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H