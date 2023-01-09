#include "../../include/stats/TrafficClassResults.h"

TrafficClassResults::TrafficClassResults(double avgInternalBlocksRatio, double internalBlocksRatioStandardDeviation,
										 double avgExternalBlocksRatio, double externalBlocksRatioStandardDeviation,
										 double avgTotalBlockRatio, double totalBlockConfidenceInterval) {
	this->avgInternalBlocksRatio = avgInternalBlocksRatio;
	this->avgExternalBlocksRatio = avgExternalBlocksRatio;
	this->avgTotalBlockRatio = avgTotalBlockRatio;
	this->internalBlocksRatioConfidenceInterval = internalBlocksRatioStandardDeviation;
	this->externalBlocksRatioConfidenceInterval = externalBlocksRatioStandardDeviation;
	this->totalBlockConfidenceInterval = totalBlockConfidenceInterval;
}