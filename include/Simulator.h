#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include "network/Network.h"
#include "event/EventNewCallArrivalErlangClass.h"
#include "event/EventNewCallArrivalEngsetClass.h"
#include "event/EventNewCallArrivalPascalClass.h"
#include "tools/GlobalSettings.h"
#include "stats/SingleSimulationResults.h"
#include "stats/SimulationSetResults.h"

class Simulator {
	Network *network;
	priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;
	Generator *generator;

	void addErlangTrafficClasses();

	void addEngsetTrafficClasses();

	void addPascalTrafficClasses();

public:
	Simulator(double a, vector<int32_t> &seedsForSimulation, uint64_t simulationIndex);

	~Simulator();

	SingleSimulationResults run();
};

#endif //EONSIMULATOR_SIMULATOR_H