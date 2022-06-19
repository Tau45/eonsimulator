#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>

class Generator {
    int32_t x;      // input parameter
    double a;       // input parameter
    uint64_t V;     // number of FSUs
    uint64_t M;     // number of traffic classes
    uint64_t mi;    // service time

    double rown_v1();

    double rown_v2();

    double rown_v3();

    double getLambda(uint32_t trafficClass);

public:
    Generator(int32_t x, double a, uint64_t V, uint64_t M, uint64_t mi);

    uint64_t getServiceTime();

    uint64_t getOccurrenceTime(uint64_t currentTime, uint32_t trafficClass);

    uint64_t getRandomLink(uint64_t numberOfLinks);
};

#endif //EONSIMULATOR_GENERATOR_H