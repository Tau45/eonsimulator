#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include <cassert>
#include "constants/Constants.h"

using namespace std;

class Link {
    bool FSUs[linkCapacity];
public:
    uint64_t destinationNode;

    Link(uint64_t destinationNode);

    void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

    bool FSUIsOccupied(uint64_t FSUIndex);

    uint64_t getNumberOfFSUs();
};

#endif //EONSIMULATOR_LINK_H