#pragma once
#ifndef EONSIMULATOR_TRAFFICCLASSSTATISTICS_H
#define EONSIMULATOR_TRAFFICCLASSSTATISTICS_H

#include <iostream>

class TrafficClassStatistics {
public:
	uint64_t totalNumberOfCalls;
	uint64_t establishedConnections;
	uint64_t internalBlocksCount;
	uint64_t externalBlocksCount;

	TrafficClassStatistics();
};

#endif //EONSIMULATOR_TRAFFICCLASSSTATISTICS_H