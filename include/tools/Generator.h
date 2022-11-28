#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>
#include "SimulationSettings.h"

class Generator {
public:
    double a;
    uint64_t linkCapacity;
    uint64_t numberOfTrafficClasses;
    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;

    int32_t x1;
    int32_t x2;
    int32_t x3;

    Generator(SimulationSettings &settings, uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks);

    double rown_v1(int &x);

    double rown_v2(int &x);

    double rown_v3(int &x);

    double getLambda(uint32_t requiredNumberOfFSUs, double serviceTime);

    double getServiceTime();

    double getOccurrenceTime(uint32_t requiredNumberOfFSUs, double serviceTime);

    uint64_t getRandomInputLink();

    uint64_t getRandomOutputLink();
};

#endif //EONSIMULATOR_GENERATOR_H