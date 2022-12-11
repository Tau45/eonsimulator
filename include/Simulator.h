#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "event/EventNewCallArrivalErlangClass.h"
#include "tools/SimulationSettings.h"

class Simulator {
    Network *network;
    priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;

    void printResults();

    void addErlangTrafficClasses();

    void addEngsetTrafficClasses();

    void addPascalTrafficClasses();

public:
    Simulator(Network &network);

    void run();
};

#endif //EONSIMULATOR_SIMULATOR_H