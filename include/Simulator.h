#pragma once
#ifndef EONSIMULATOR_SIMULATOR_H
#define EONSIMULATOR_SIMULATOR_H

#include <chrono>
#include "event/EventNewCallArrivalErlangClass.h"
#include "event/EventNewCallArrivalEngsetClass.h"
#include "event/EventNewCallArrivalPascalClass.h"
#include "stats/SimulationSetResults.h"

class Simulator {
	Network *network;
	priority_queue<Event *, vector<Event *>, Event::EventComparator> eventQueue;
	Generator *generator;

	double getLambda(uint32_t requiredNumberOfFSUs, uint64_t numberOfInputLinks);

	void addErlangTrafficClasses();

	void addEngsetTrafficClasses();

	void addPascalTrafficClasses();

public:
	Simulator(double a, vector<int32_t> &seedsForSimulation, uint64_t simulationIndex);

	~Simulator();

	SingleSimulationResults run();
};

#endif //EONSIMULATOR_SIMULATOR_H