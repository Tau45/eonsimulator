#include "../../include/stats/TrafficClassResults.h"

TrafficClassResults::TrafficClassResults(double avgInternalBlocksRatio, double avgExternalBlocksRatio, double internalBlocksRatioStandardDeviation, double externalBlocksRatioStandardDeviation) {
    this->avgInternalBlocksRatio = avgInternalBlocksRatio;
    this->avgExternalBlocksRatio = avgExternalBlocksRatio;
    this->internalBlocksRatioStandardDeviation = internalBlocksRatioStandardDeviation;
    this->externalBlocksRatioStandardDeviation = externalBlocksRatioStandardDeviation;
}