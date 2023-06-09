#pragma once
#ifndef EONSIMULATOR_TRAFFICCLASSRESULTS_H
#define EONSIMULATOR_TRAFFICCLASSRESULTS_H

class TrafficClassResults {
public:
	double avgInternalBlocksRatio;
	double avgExternalBlocksRatio;
	double avgTotalBlockRatio;
	double internalBlocksRatioConfidenceInterval;
	double externalBlocksRatioConfidenceInterval;
	double totalBlockConfidenceInterval;

	TrafficClassResults() {}

	TrafficClassResults(double avgInternalBlocksRatio, double internalBlocksRatioStandardDeviation,
						double avgExternalBlocksRatio, double externalBlocksRatioStandardDeviation,
						double avgTotalBlockRatio, double totalBlockConfidenceInterval);
};

#endif //EONSIMULATOR_TRAFFICCLASSRESULTS_H