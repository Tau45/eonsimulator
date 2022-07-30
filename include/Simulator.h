#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "network/structures/Benes4x4.h"
#include "network/structures/SingleLink.h"
#include "network/structures/ThreeSections4x4.h"
#include "event/Event.h"
#include "event/EventNewCallArrivalErlangClass.h"
#include "event/EventCallServiceTermination.h"
#include "tools/Generator.h"

using namespace std;

class Simulator {
    double clock;
    Network *network;
    priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;

    uint64_t callsToGenerate;

    Generator *generator;

    void addErlangTrafficClass(uint64_t requiredNumberOfFSUs);

//    void addEngsetTrafficClass(uint64_t requiredNumberOfFSUs);

//    void addPascalTrafficClass(uint64_t requiredNumberOfFSUs);

    void printResults();

public:
    Simulator(uint64_t callsTarget, double a);

    ~Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H