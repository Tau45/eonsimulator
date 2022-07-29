#include "../../include/tools/Generator.h"

Generator::Generator(double a, uint64_t V, uint64_t M, uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks) {
    this->x1 = 869724338;
    this->x2 = 925386436;
    this->x3 = 742339657;
    this->a = a;
    this->V = V;
    this->M = M;
    this->numberOfInputLinks = numberOfInputLinks;
    this->numberOfOutputLinks = numberOfOutputLinks;
}

double Generator::rown_v1() {
    int a_ = 16807, q = 127773, r = 2836, h;
    h = int(x1 / q);
    x1 = a_ * (x1 - q * h) - r * h;
    if (x1 < 0) x1 = x1 + 2147483647;
    return double(x1) / 2147483647;
}

double Generator::rown_v2() {
    int a_ = 48271, q = 44488, r = 3399, h;
    h = int(x2 / q);
    x2 = a_ * (x2 - q * h) - r * h;
    if (x2 < 0) x2 = x2 + 2147483647;
    return double(x2) / 2147483647;
}

int Generator::rown_v3() {
    int a_ = 69621, q = 30845, r = 23902, h;
    h = int(x3 / q);
    x3 = a_ * (x3 - q * h) - r * h;
    if (x3 < 0) x3 = x3 + 2147483647;
    return x3;
}

double Generator::getLambda(uint32_t requiredNumberOfFSUs, double serviceTime) {
    return (a * V) / (M * serviceTime * requiredNumberOfFSUs);
}

double Generator::getServiceTime() {
    return 1;
}

double Generator::getOccurrenceTime(uint32_t requiredNumberOfFSUs, double serviceTime) {
    return log(rown_v1()) * (-1 / getLambda(requiredNumberOfFSUs, serviceTime));
}

uint64_t Generator::getRandomInputLink() {
    return rown_v3() % numberOfInputLinks;
}

uint64_t Generator::getRandomOutputLink() {
    return rown_v3() % numberOfOutputLinks;
}