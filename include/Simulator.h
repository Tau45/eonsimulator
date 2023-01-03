#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "event/EventNewCallArrivalErlangClass.h"
#include "tools/SimulationSettings.h"
#include "stats/SingleSimulationResults.h"
#include "stats/SimulationSetResults.h"

class Simulator {
    Network *network;
    priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;

    void addErlangTrafficClasses();

    void addEngsetTrafficClasses();

    void addPascalTrafficClasses();

    void reset();

    SingleSimulationResults runSingleSimulation();

    SimulationSetResults runSimulationSet();

public:
    Simulator(Network &network);

    ~Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H