#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>

class Generator {
public:
    double a;   // input parameter
    uint64_t V; // number of FSUs
    uint64_t M; // number of traffic classes
    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;

    int32_t x1;
    int32_t x2;
    int32_t x3;

    Generator(double a, uint64_t V, uint64_t M, uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks);

    double rown_v1();

    double rown_v2();

    int rown_v3();

    double getLambda(uint32_t requiredNumberOfFSUs, double serviceTime);

    double getServiceTime();

    double getOccurrenceTime(uint32_t requiredNumberOfFSUs, double serviceTime);

    uint64_t getRandomInputLink();

    uint64_t getRandomOutputLink();
};

#endif //EONSIMULATOR_GENERATOR_H