#include "../../include/stats/SimulationSetResults.h"

SimulationSetResults::SimulationSetResults(double a, const vector<SingleSimulationResults> &simulationResults) {
    this->a = a;

    vector<map<uint64_t, TrafficClassResultRatios>> erlangTrafficResultRatiosVector;
    vector<map<uint64_t, TrafficClassResultRatios>> engsetTrafficResultRatiosVector;
    vector<map<uint64_t, TrafficClassResultRatios>> pascalTrafficResultRatiosVector;

    for (const SingleSimulationResults &simulationResult: simulationResults) {
        erlangTrafficResultRatiosVector.push_back(simulationResult.erlangTrafficResultRatios);
        engsetTrafficResultRatiosVector.push_back(simulationResult.engsetTrafficResultRatios);
        pascalTrafficResultRatiosVector.push_back(simulationResult.pascalTrafficResultRatios);
    }

    setTrafficClassResults(erlangTrafficResults, erlangTrafficResultRatiosVector, SimulationSettings::instance().getErlangTrafficClasses());
    setTrafficClassResults(engsetTrafficResults, engsetTrafficResultRatiosVector, SimulationSettings::instance().getEngsetTrafficClasses());
    setTrafficClassResults(pascalTrafficResults, pascalTrafficResultRatiosVector, SimulationSettings::instance().getPascalTrafficClasses());
}

void SimulationSetResults::setTrafficClassResults(map<uint64_t, TrafficClassResults> &trafficResults, const vector<map<uint64_t, TrafficClassResultRatios>> &trafficResultRatiosVector, const set<uint64_t> &trafficClasses) {
    map<uint64_t, double> internalBlockRatioSums;
    map<uint64_t, double> externalBlockRatioSums;
    uint64_t numberOfRuns = trafficResultRatiosVector.size();

    for (uint64_t trafficClass: trafficClasses) {
        internalBlockRatioSums[trafficClass] = 0.0;
        externalBlockRatioSums[trafficClass] = 0.0;
    }

    for (const auto &trafficResultRatios: trafficResultRatiosVector) {
        for (const auto &trafficResultRatio: trafficResultRatios) {
            internalBlockRatioSums[trafficResultRatio.first] += trafficResultRatio.second.internalBlocksRatio;
            externalBlockRatioSums[trafficResultRatio.first] += trafficResultRatio.second.externalBlocksRatio;
        }
    }

    for (uint64_t trafficClass: trafficClasses) {
        trafficResults[trafficClass] = TrafficClassResults(internalBlockRatioSums[trafficClass] / numberOfRuns, externalBlockRatioSums[trafficClass] / numberOfRuns, 0.0, 0.0);
    }
}