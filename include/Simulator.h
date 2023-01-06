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
    Generator *generator;

    void addErlangTrafficClasses();

    void addEngsetTrafficClasses();

    void addPascalTrafficClasses();

    void reset();

public:
    Simulator(Network &network, Generator &generator);

    ~Simulator();

    SingleSimulationResults run();
};

#endif //EONSIMULATOR_SIMULATOR_H