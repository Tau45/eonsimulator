#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
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
    Simulator(string structureFileName, double a, uint64_t callsToGenerate);

    ~Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H