#ifndef EONSIMULATOR_SEEDSPROVIDER_H
#define EONSIMULATOR_SEEDSPROVIDER_H

#include <iostream>
#include <queue>

using namespace std;

class SeedsProvider {
	queue<int32_t> seeds;

	int32_t getSeed();

	vector<int32_t> getSeedsForSingleSimulation();

	vector<vector<int32_t>> getSeedsForSimulationSet(uint64_t numberOfSimulationsInSet);

public:
	SeedsProvider();

	uint64_t getNumberOfAvailableSeeds();

	vector<vector<vector<int32_t>>> getSeeds(uint64_t numberOfSimulationSets, uint64_t numberOfSimulationsPerSet);
};

#endif //EONSIMULATOR_SEEDSPROVIDER_H