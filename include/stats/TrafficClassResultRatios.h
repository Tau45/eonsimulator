#pragma once
#ifndef EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H
#define EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H

class TrafficClassResultRatios {
public:
	double internalBlocksRatio;
	double externalBlocksRatio;
	double totalRatio;

	TrafficClassResultRatios() {}

	TrafficClassResultRatios(double internalBlocksRatio, double externalBlocksRatio, double totalRatio);
};

#endif //EONSIMULATOR_TRAFFICCLASSRESULTRATIOS_H