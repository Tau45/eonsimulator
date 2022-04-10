#include "../include/Link.h"

Link::Link(int sourceNode, int destinationNode) {
    this->sourceNode = sourceNode;
    this->destinationNode = destinationNode;
}

void Link::reserveFSUs(uint16_t numberOfFSUs, uint16_t firstFSU, uint64_t connectionId) {
    for (int i = firstFSU; i < firstFSU + numberOfFSUs; i++)
        FSUs[i].reserve(connectionId);
}
