#pragma once
#ifndef EONSIMULATOR_SIMULATIONSETRESULTS_H
#define EONSIMULATOR_SIMULATIONSETRESULTS_H

#include <cmath>
#include "TrafficClassResults.h"
#include "SingleSimulationResults.h"
#include "../tools/GlobalSettings.h"

class SimulationSetResults {
public:
	double a;
	map<uint64_t, TrafficClassResults> trafficResults;

	SimulationSetResults(double a, const vector<SingleSimulationResults> &);
};

#endif //EONSIMULATOR_SIMULATIONSETRESULTS_H