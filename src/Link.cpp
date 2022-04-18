#include "../include/Link.h"

Link::Link(int sourceNode, int destinationNode) {
    this->sourceNode = sourceNode;
    this->destinationNode = destinationNode;
    for (bool &FSU: FSUs) {
        FSU = false;
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

bool Link::FSUIsBusy(uint64_t FSUIndex) {
    return FSUs[FSUIndex];
}