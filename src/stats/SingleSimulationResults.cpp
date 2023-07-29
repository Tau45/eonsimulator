#include "../../include/stats/SingleSimulationResults.h"

SingleSimulationResults::SingleSimulationResults(const map<uint64_t, TrafficClassStatistics> &trafficClasses) {
	for (auto const &trafficClass: trafficClasses) {
		double internalBlocksRatio = (double) trafficClass.second.internalBlocksCount / (double) trafficClass.second.totalNumberOfCalls;
		double externalBlocksRatio = (double) trafficClass.second.externalBlocksCount / (double) trafficClass.second.totalNumberOfCalls;
		double totalRatio = internalBlocksRatio + externalBlocksRatio;
		trafficResultRatios[trafficClass.first] = TrafficClassResultRatios(internalBlocksRatio, externalBlocksRatio, totalRatio);
	}
}