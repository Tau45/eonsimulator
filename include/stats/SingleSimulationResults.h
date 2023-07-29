#pragma once
#ifndef EONSIMULATOR_SINGLESIMULATIONRESULTS_H
#define EONSIMULATOR_SINGLESIMULATIONRESULTS_H

#include <map>
#include "TrafficClassResultRatios.h"
#include "TrafficClassStatistics.h"

using namespace std;

class SingleSimulationResults {
public:
    SingleSimulationResults(const map<uint64_t, TrafficClassStatistics> &trafficClasses);

	map<uint64_t, TrafficClassResultRatios> trafficResultRatios;
};

#endif //EONSIMULATOR_SINGLESIMULATIONRESULTS_H