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

	setTrafficSourceResults(erlangTrafficResults, erlangTrafficResultRatiosVector, SimulationSettings::instance().getErlangTrafficClasses());
	setTrafficSourceResults(engsetTrafficResults, engsetTrafficResultRatiosVector, SimulationSettings::instance().getEngsetTrafficClasses());
	setTrafficSourceResults(pascalTrafficResults, pascalTrafficResultRatiosVector, SimulationSettings::instance().getPascalTrafficClasses());
}

void SimulationSetResults::setTrafficSourceResults(map<uint64_t, TrafficClassResults> &trafficResults, const vector<map<uint64_t, TrafficClassResultRatios>> &trafficResultRatiosVector, const set<uint64_t> &trafficClasses) {
	/// Calculate average ratios
	map<uint64_t, double> avgInternalBlockRatios;
	map<uint64_t, double> avgExternalBlockRatios;
	map<uint64_t, double> avgTotalBlockRatios;

	for (uint64_t trafficClass: trafficClasses) {
		avgInternalBlockRatios[trafficClass] = 0.0;
		avgExternalBlockRatios[trafficClass] = 0.0;
		avgTotalBlockRatios[trafficClass] = 0.0;
	}

	for (const auto &trafficResultRatios: trafficResultRatiosVector) {
		for (const auto &trafficResultRatio: trafficResultRatios) {
			avgInternalBlockRatios[trafficResultRatio.first] += trafficResultRatio.second.internalBlocksRatio;
			avgExternalBlockRatios[trafficResultRatio.first] += trafficResultRatio.second.externalBlocksRatio;
			avgTotalBlockRatios[trafficResultRatio.first] += trafficResultRatio.second.totalRatio;
		}
	}

	for (uint64_t trafficClass: trafficClasses) {
		avgInternalBlockRatios[trafficClass] = avgInternalBlockRatios[trafficClass] / SimulationSettings::instance().getRuns();
		avgExternalBlockRatios[trafficClass] = avgExternalBlockRatios[trafficClass] / SimulationSettings::instance().getRuns();
		avgTotalBlockRatios[trafficClass] = avgExternalBlockRatios[trafficClass] / SimulationSettings::instance().getRuns();
	}

	/// Calculate standard deviations
	map<uint64_t, double> internalBlockStandardDeviations;
	map<uint64_t, double> externalBlockStandardDeviations;
	map<uint64_t, double> totalBlockStandardDeviations;

	for (uint64_t trafficClass: trafficClasses) {
		internalBlockStandardDeviations[trafficClass] = 0.0;
		externalBlockStandardDeviations[trafficClass] = 0.0;
		totalBlockStandardDeviations[trafficClass] = 0.0;
	}

	for (const auto &trafficResultRatios: trafficResultRatiosVector) {
		for (const auto &trafficResultRatio: trafficResultRatios) {
			internalBlockStandardDeviations[trafficResultRatio.first] += pow(trafficResultRatio.second.internalBlocksRatio - avgInternalBlockRatios[trafficResultRatio.first], 2);
			externalBlockStandardDeviations[trafficResultRatio.first] += pow(trafficResultRatio.second.externalBlocksRatio - avgExternalBlockRatios[trafficResultRatio.first], 2);
			totalBlockStandardDeviations[trafficResultRatio.first] += pow(trafficResultRatio.second.totalRatio - avgInternalBlockRatios[trafficResultRatio.first], 2);
		}
	}

	for (uint64_t trafficClass: trafficClasses) {
		if (avgInternalBlockRatios[trafficClass] != 0) {
			internalBlockStandardDeviations[trafficClass] = sqrt(internalBlockStandardDeviations[trafficClass] / avgInternalBlockRatios[trafficClass]);
		}
		if (avgExternalBlockRatios[trafficClass] != 0) {
			externalBlockStandardDeviations[trafficClass] = sqrt(externalBlockStandardDeviations[trafficClass] / avgExternalBlockRatios[trafficClass]);
		}
		if (avgTotalBlockRatios[trafficClass] != 0) {
			totalBlockStandardDeviations[trafficClass] = sqrt(totalBlockStandardDeviations[trafficClass] / avgTotalBlockRatios[trafficClass]);
		}
	}

	/// Calculate confidence intervals
	map<uint64_t, double> internalBlockConfidenceIntervals;
	map<uint64_t, double> externalBlockConfidenceIntervals;
	map<uint64_t, double> totalBlockConfidenceIntervals;

	for (uint64_t trafficClass: trafficClasses) {
		internalBlockConfidenceIntervals[trafficClass] = 1.96 * (internalBlockStandardDeviations[trafficClass] / sqrt(SimulationSettings::instance().getRuns()));
		externalBlockConfidenceIntervals[trafficClass] = 1.96 * (externalBlockStandardDeviations[trafficClass] / sqrt(SimulationSettings::instance().getRuns()));
		totalBlockConfidenceIntervals[trafficClass] = 1.96 * (totalBlockStandardDeviations[trafficClass] / sqrt(SimulationSettings::instance().getRuns()));
	}

	/// Save results
	for (uint64_t trafficClass: trafficClasses) {
		trafficResults[trafficClass] = TrafficClassResults(avgInternalBlockRatios[trafficClass], internalBlockConfidenceIntervals[trafficClass],
														   avgExternalBlockRatios[trafficClass], externalBlockConfidenceIntervals[trafficClass],
														   avgTotalBlockRatios[trafficClass], totalBlockConfidenceIntervals[trafficClass]);
	}
}