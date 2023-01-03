#ifndef EONSIMULATOR_SINGLESIMULATIONRESULTS_H
#define EONSIMULATOR_SINGLESIMULATIONRESULTS_H

#include <iostream>
#include <map>
#include "TrafficClassResultRatios.h"
#include "TrafficClassStatistics.h"

using namespace std;

class SingleSimulationResults {
    void setTrafficClassResultRatios(map<uint64_t, TrafficClassResultRatios> &trafficResultRatios, const map<uint64_t, TrafficClassStatistics> &trafficClasses);

public:
    SingleSimulationResults(const map<uint64_t, TrafficClassStatistics> &erlangTrafficClasses,
                            const map<uint64_t, TrafficClassStatistics> &engsetTrafficClasses,
                            const map<uint64_t, TrafficClassStatistics> &pascalTrafficClasses);

    map<uint64_t, TrafficClassResultRatios> erlangTrafficResultRatios;
    map<uint64_t, TrafficClassResultRatios> engsetTrafficResultRatios;
    map<uint64_t, TrafficClassResultRatios> pascalTrafficResultRatios;
};

#endif //EONSIMULATOR_SINGLESIMULATIONRESULTS_H