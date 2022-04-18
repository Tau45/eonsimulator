#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include <cassert>

using namespace std;

class Link {
    bool FSUs[2];
public:
    uint64_t sourceNode;
    uint64_t destinationNode;

    Link(int sourceNode, int destinationNode);

    void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    bool FSUIsBusy(uint64_t FSUIndex);
};

#endif //EONSIMULATOR_LINK_H