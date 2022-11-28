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
#include "tools/SimulationSettings.h"

using namespace std;

class Simulator {
    double clock;
    Network *network;
    priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;
    Generator *generator;
    SimulationSettings *settings;

    void printResults();

    void addErlangTrafficClasses();

    void addEngsetTrafficClasses();

    void addPascalTrafficClasses();

    Logger logger;
public:
    Simulator(SimulationSettings &simulationSettings);

    ~Simulator();

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H