#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>
#include "GlobalSettings.h"
#include "../../include/network/Link.h"
#include "../network/Path.h"

class Generator {
	double a;
	uint64_t simulationIndex;

	int32_t x1;
	int32_t x2;
	int32_t x3;

	double rown_v1(int &x);

	double rown_v2(int &x);

	double rown_v3(int &x);

	double getLambda(uint32_t requiredNumberOfFSUs, uint64_t numberOfInputLinks);

	uint64_t getRandomNaturalNumber(uint64_t numberOfNumbers);

public:
	Generator(double a, int32_t x1, int32_t x2, int32_t x3, uint64_t simulationIndex);

	double getA();

	uint64_t getSimulationIndex();

	double getRandomServiceTime();

	double getRandomOccurrenceTime(uint32_t requiredNumberOfFSUs, uint64_t numberOfInputLinks);

	Link *getRandomLink(vector<Link *> &links);

	vector<Link *> &getRandomOutputDirection(vector<vector<Link *>> &outputDirections);

	uint64_t getRandomFirstFSU(vector<uint64_t> availableFirstFSUs);

	vector<Link *> shuffleVector(vector<Link *> inputVector);

	vector<Path *> shuffleVector(vector<Path *> inputVector);
};

#endif //EONSIMULATOR_GENERATOR_H