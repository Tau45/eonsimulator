#include "../include/Generator.h"

Generator::Generator(int32_t x, double a, uint64_t V, uint64_t M, uint64_t mi) {
    this->x = x;
    this->a = a;
    this->V = V;
    this->M = M;
    this->mi = mi;
}

double Generator::rown_v1() {
    int a_ = 16807, q = 127773, r = 2836, h;
    h = int(x / q);
    x = a_ * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

double Generator::rown_v2() {
    int a_ = 48271, q = 44488, r = 3399, h;
    h = int(x / q);
    x = a_ * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

double Generator::rown_v3() {
    int a_ = 69621, q = 30845, r = 23902, h;
    h = int(x / q);
    x = a_ * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

uint64_t Generator::getServiceTime() {
    return 1;
}

uint64_t Generator::getOccurrenceTime(uint64_t currentTime, uint32_t trafficClass) {
    double w = log(rown_v1()) * (-1 / getLambda(trafficClass));
    return currentTime + round(w);
}

double Generator::getLambda(uint32_t trafficClass) {
    return (a * V) / (M * mi * trafficClass);
}

uint64_t Generator::getRandomLink(uint64_t numberOfLinks) {
    srand(x);
    return rand() % numberOfLinks;
}
