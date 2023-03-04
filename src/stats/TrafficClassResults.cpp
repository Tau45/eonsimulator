#include "../../include/stats/TrafficClassResults.h"

TrafficClassResults::TrafficClassResults(double avgInternalBlocksRatio, double internalBlocksRatioConfidenceInterval,
										 double avgExternalBlocksRatio, double externalBlocksRatioConfidenceInterval,
										 double avgTotalBlockRatio, double totalBlockConfidenceInterval) :
		avgInternalBlocksRatio(avgInternalBlocksRatio),
		internalBlocksRatioConfidenceInterval(internalBlocksRatioConfidenceInterval),
		avgExternalBlocksRatio(avgExternalBlocksRatio),
		externalBlocksRatioConfidenceInterval(externalBlocksRatioConfidenceInterval),
		avgTotalBlockRatio(avgTotalBlockRatio),
		totalBlockConfidenceInterval(totalBlockConfidenceInterval) {}