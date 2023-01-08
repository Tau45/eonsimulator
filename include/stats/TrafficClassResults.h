#ifndef EONSIMULATOR_TRAFFICCLASSRESULTS_H
#define EONSIMULATOR_TRAFFICCLASSRESULTS_H

class TrafficClassResults {
public:
    double avgInternalBlocksRatio;
    double avgExternalBlocksRatio;
    double internalBlocksRatioConfidenceInterval;
    double externalBlocksRatioConfidenceInterval;

    TrafficClassResults() {}

    TrafficClassResults(double avgInternalBlocksRatio, double avgExternalBlocksRatio, double internalBlocksRatioStandardDeviation, double externalBlocksRatioStandardDeviation);
};

#endif //EONSIMULATOR_TRAFFICCLASSRESULTS_H