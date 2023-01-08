#ifndef EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H
#define EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H

class TrafficClassResultRatios {
public:
	double internalBlocksRatio;
	double externalBlocksRatio;

	TrafficClassResultRatios() {}

	TrafficClassResultRatios(double internalBlocksRatio, double externalBlocksRatio);
};

#endif //EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H