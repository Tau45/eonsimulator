#include "../../include/tools/Generator.h"

Generator::Generator(uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks) {
    this->x1 = 869724338;
    this->x2 = 925386436;
    this->x3 = 742339657;
    this->numberOfInputLinks = numberOfInputLinks;
    this->numberOfOutputLinks = numberOfOutputLinks;
}

double Generator::rown_v1(int &x) {
    int a = 16807, q = 127773, r = 2836, h;
    h = int(x / q);
    x = a * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

double Generator::rown_v2(int &x) {
    int a = 48271, q = 44488, r = 3399, h;
    h = int(x / q);
    x = a * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

double Generator::rown_v3(int &x) {
    int a = 69621, q = 30845, r = 23902, h;
    h = int(x / q);
    x = a * (x - q * h) - r * h;
    if (x < 0) x = x + 2147483647;
    return double(x) / 2147483647;
}

double Generator::getLambda(uint32_t requiredNumberOfFSUs, double serviceTime) {
    double a = SimulationSettings::instance().getA();
    uint64_t linkCapacity = SimulationSettings::instance().getLinkCapacity();
    uint64_t numberOfTrafficClasses = SimulationSettings::instance().getNumberOfTrafficClasses();

    return (a * linkCapacity) / (numberOfTrafficClasses * serviceTime * requiredNumberOfFSUs);
}

double Generator::getRandomServiceTime() {
    return 1;
}

double Generator::getRandomOccurrenceTime(uint32_t requiredNumberOfFSUs, double serviceTime) {
    return log(rown_v1(x1)) * (-1 / getLambda(requiredNumberOfFSUs, serviceTime));
}

uint64_t Generator::getRandomInputLink() {
    uint64_t randomLink = rown_v3(x3) * numberOfInputLinks;

    if (randomLink == numberOfInputLinks) {
        return randomLink - 1;
    }

    return randomLink;
}

uint64_t Generator::getRandomOutputLink() {
    uint64_t randomLink = rown_v3(x3) * numberOfOutputLinks;

    if (randomLink == numberOfOutputLinks) {
        return randomLink - 1;
    }

    return randomLink;
}

uint64_t Generator::getRandomFirstFSU(vector<uint64_t> availableFirstFSUs) {
    uint64_t randomFirstFSUIndex = rown_v2(x2) * availableFirstFSUs.size();

    if (randomFirstFSUIndex == availableFirstFSUs.size()) {
        randomFirstFSUIndex = randomFirstFSUIndex - 1;
    }

    return availableFirstFSUs[randomFirstFSUIndex];
}