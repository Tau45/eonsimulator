#include "../../include/stats/SimulationSetResults.h"

SimulationSetResults::SimulationSetResults(double a, const vector<SingleSimulationResults> &simulationResults) :
		a(a) {
	vector<map<uint64_t, TrafficClassResultRatios>> trafficResultRatiosVector;

	for (const SingleSimulationResults &simulationResult: simulationResults) {
		trafficResultRatiosVector.push_back(simulationResult.trafficResultRatios);
	}

	set<uint64_t> trafficClasses;
	for (auto trafficClass: GlobalSettings::instance().getErlangTrafficClasses()) {
		trafficClasses.insert(trafficClass.getRequiredNumberOfFSUs());
	}

	for (auto trafficClass: GlobalSettings::instance().getEngsetTrafficClasses()) {
		trafficClasses.insert(trafficClass.getRequiredNumberOfFSUs());
	}

	for (auto trafficClass: GlobalSettings::instance().getPascalTrafficClasses()) {
		trafficClasses.insert(trafficClass.getRequiredNumberOfFSUs());
	}

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
		avgInternalBlockRatios[trafficClass] = avgInternalBlockRatios[trafficClass] / GlobalSettings::instance().getRuns();
		avgExternalBlockRatios[trafficClass] = avgExternalBlockRatios[trafficClass] / GlobalSettings::instance().getRuns();
		avgTotalBlockRatios[trafficClass] = avgTotalBlockRatios[trafficClass] / GlobalSettings::instance().getRuns();
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
			totalBlockStandardDeviations[trafficResultRatio.first] += pow(trafficResultRatio.second.totalRatio - avgTotalBlockRatios[trafficResultRatio.first], 2);
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
		internalBlockConfidenceIntervals[trafficClass] = 1.96 * (internalBlockStandardDeviations[trafficClass] / sqrt(GlobalSettings::instance().getRuns()));
		externalBlockConfidenceIntervals[trafficClass] = 1.96 * (externalBlockStandardDeviations[trafficClass] / sqrt(GlobalSettings::instance().getRuns()));
		totalBlockConfidenceIntervals[trafficClass] = 1.96 * (totalBlockStandardDeviations[trafficClass] / sqrt(GlobalSettings::instance().getRuns()));
	}

	/// Save results
	for (uint64_t trafficClass: trafficClasses) {
		trafficResults[trafficClass] = TrafficClassResults(avgInternalBlockRatios[trafficClass], internalBlockConfidenceIntervals[trafficClass],
														   avgExternalBlockRatios[trafficClass], externalBlockConfidenceIntervals[trafficClass],
														   avgTotalBlockRatios[trafficClass], totalBlockConfidenceIntervals[trafficClass]);
	}
}