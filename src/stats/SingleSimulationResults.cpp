#include "../../include/stats/SingleSimulationResults.h"

SingleSimulationResults::SingleSimulationResults(const map<uint64_t, TrafficClassStatistics> &erlangTrafficClasses,
												 const map<uint64_t, TrafficClassStatistics> &engsetTrafficClasses,
												 const map<uint64_t, TrafficClassStatistics> &pascalTrafficClasses) {
	setTrafficClassResultRatios(erlangTrafficResultRatios, erlangTrafficClasses);
	setTrafficClassResultRatios(engsetTrafficResultRatios, engsetTrafficClasses);
	setTrafficClassResultRatios(pascalTrafficResultRatios, pascalTrafficClasses);
}

void SingleSimulationResults::setTrafficClassResultRatios(map<uint64_t, TrafficClassResultRatios> &trafficResultRatios, const map<uint64_t, TrafficClassStatistics> &trafficClasses) {
	for (auto const &trafficClass: trafficClasses) {
		double internalBlocksRatio = (double) trafficClass.second.internalBlocksCount / trafficClass.second.callsGenerated;
		double externalBlocksRatio = (double) trafficClass.second.externalBlocksCount / trafficClass.second.callsGenerated;
		trafficResultRatios[trafficClass.first] = TrafficClassResultRatios(internalBlocksRatio, externalBlocksRatio);
	}
}