#pragma once
#ifndef EONSIMULATOR_SIMULATIONID_H
#define EONSIMULATOR_SIMULATIONID_H

#include <iostream>

class SimulationId {
	double a;
	uint64_t simulationIndex;

public:
	SimulationId(double a, uint64_t simulationIndex);

	double getA();

	uint64_t getSimulationIndex();
};

#endif //EONSIMULATOR_SIMULATIONID_H