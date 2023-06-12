#pragma once
#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <math.h>
#include "../../include/network/Link.h"
#include "../../include/network/Path.h"

class Generator {
	int32_t x1;
	int32_t x2;
	int32_t x3;

	double rown_v1(int &x);

	double rown_v2(int &x);

	double rown_v3(int &x);

	uint64_t getRandomNaturalNumber(uint64_t numberOfNumbers);

public:
	Generator(int32_t x1, int32_t x2, int32_t x3);

	double getRandomServiceTime();

	double getRandomOccurrenceTime(double lambda);

	Link *getRandomLink(vector<Link *> links);

	uint64_t getRandomOutputDirectionIndex(uint64_t numberOfOutputDirections);

	uint64_t getRandomFirstFSU(vector<uint64_t> availableFirstFSUs);

	vector<Link *> shuffleVector(vector<Link *> inputVector);

	vector<Path *> shuffleVector(vector<Path *> inputVector);
};

#endif //EONSIMULATOR_GENERATOR_H