#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Link {
    vector<bool> FSUs;
    uint64_t sourceNode;
    uint64_t destinationNode;
public:
    Link(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity);

    void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    bool FSUIsOccupied(uint64_t FSUIndex);

    uint64_t getSourceNode();

    uint64_t getDestinationNode();
};

#endif //EONSIMULATOR_LINK_H