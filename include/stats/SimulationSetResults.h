#ifndef EONSIMULATOR_SIMULATIONSETRESULTS_H
#define EONSIMULATOR_SIMULATIONSETRESULTS_H

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "TrafficClassResults.h"
#include "SingleSimulationResults.h"
#include "../tools/SimulationSettings.h"

using namespace std;

class SimulationSetResults {
	void setTrafficSourceResults(map<uint64_t, TrafficClassResults> &trafficResults,
								 const vector<map<uint64_t, TrafficClassResultRatios>> &trafficResultRatiosVector,
								 const set<uint64_t> &trafficClasses);

public:
	double a;
	map<uint64_t, TrafficClassResults> erlangTrafficResults;
	map<uint64_t, TrafficClassResults> engsetTrafficResults;
	map<uint64_t, TrafficClassResults> pascalTrafficResults;

	SimulationSetResults(double a, const vector<SingleSimulationResults> &);
};

#endif //EONSIMULATOR_SIMULATIONSETRESULTS_H