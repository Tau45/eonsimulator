#include "../../include/network/Link.h"

Link::Link(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity) {
    this->sourceNode = sourceNode;
    this->destinationNode = destinationNode;
    for (int i = 0; i < linkCapacity; i++) {
        FSUs.push_back(false);
    }
}

void Link::reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
    for (uint64_t i = firstFSU; i < firstFSU + numberOfFSUs; i++) {
        assert(!FSUs[i]);
        FSUs[i] = true;
    }
}

void Link::freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
    for (uint64_t i = firstFSU; i < firstFSU + numberOfFSUs; i++) {
        assert(FSUs[i]);
        FSUs[i] = false;
    }
}

bool Link::FSUIsOccupied(uint64_t FSUIndex) {
    return FSUs[FSUIndex];
}

uint64_t Link::getSourceNode() {
    return sourceNode;
}

uint64_t Link::getDestinationNode() {
    return destinationNode;
}

void Link::freeAllFSUs() {
    for (auto &&FSU: FSUs) {
        FSU = false;
    }
}