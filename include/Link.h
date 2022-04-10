#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include "FSU.h"

using namespace std;

class NetworkSwitch;

class Link {
public:
    int sourceNode;
    int destinationNode;
    FSU FSUs[2];

    Link(int sourceNode, int destinationNode);

    void reserveFSUs(uint16_t numberOfFSUs, uint16_t firstFSU, uint64_t connectionId);

//    void freeFSUs(uint64_t connectionId);
};

#endif //EONSIMULATOR_LINK_H