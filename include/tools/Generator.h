#ifndef EONSIMULATOR_GENERATOR_H
#define EONSIMULATOR_GENERATOR_H

#include <iostream>
#include <math.h>

class Generator {
    double a;       // input parameter
    uint64_t V;     // number of FSUs
    uint64_t M;     // number of traffic classes
    uint64_t mi;    // service time

    double rown_v1() {
        int a_ = 16807, q = 127773, r = 2836, h;
        h = int(x1 / q);
        x1 = a_ * (x1 - q * h) - r * h;
        if (x1 < 0) x1 = x1 + 2147483647;
        return double(x1) / 2147483647;
    }

    double rown_v2() {
        int a_ = 48271, q = 44488, r = 3399, h;
        h = int(x2 / q);
        x2 = a_ * (x2 - q * h) - r * h;
        if (x2 < 0) x2 = x2 + 2147483647;
        return double(x2) / 2147483647;
    }

    int rown_v3() {
        int a_ = 69621, q = 30845, r = 23902, h;
        h = int(x3 / q);
        x3 = a_ * (x3 - q * h) - r * h;
        if (x3 < 0) x3 = x3 + 2147483647;
        return x3;
    }

    double getLambda(uint32_t trafficClass) {
        return (a * V) / (M * mi * trafficClass);
    }

public:
    int32_t x1;
    int32_t x2;
    int32_t x3;

    Generator(double a, uint64_t V, uint64_t M, uint64_t mi) {
        this->x1 = 869724338;
        this->x2 = 925386436;
        this->x3 = 742339657;
        this->a = a;
        this->V = V;
        this->M = M;
        this->mi = mi;
    }

    uint64_t getServiceTime() {
        return 1;
    }

    uint64_t getOccurrenceTime(uint64_t currentTime, uint32_t trafficClass) {
        double w = log(rown_v1()) * (-1 / getLambda(trafficClass));
        return currentTime + w;
    }

    uint64_t getRandomLink(uint64_t numberOfLinks) {
        return rown_v3() % numberOfLinks;
    }

    double getA() {
        return a;
    }
};

#endif //EONSIMULATOR_GENERATOR_H