#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>
#include "SimulationSettings.h"

class Generator {
    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;

    int32_t x1;
    int32_t x2;
    int32_t x3;

    Generator(uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks);

    Generator(const Generator &) = delete;

    void operator=(const Generator &) = delete;

    double rown_v1(int &x);

    double rown_v2(int &x);

    double rown_v3(int &x);

    double getLambda(uint32_t requiredNumberOfFSUs, double serviceTime);

public:
    static Generator &instance(function<Generator()> *init = nullptr);

    static void initialize(uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks);

    double getRandomServiceTime();

    double getRandomOccurrenceTime(uint32_t requiredNumberOfFSUs, double serviceTime);

    uint64_t getRandomInputLink();

    uint64_t getRandomOutputLink();

    uint64_t getRandomFirstFSU(vector<uint64_t> potentialFirstFSUs);
};

#endif //EONSIMULATOR_GENERATOR_H