#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include <vector>
#include "Link.h"

using namespace std;

class Connection {
public:
    uint64_t srcLink;
    uint64_t dstLink;
    vector<Link *> path;
    uint64_t firstFSU;
    uint64_t numberOfFSUs;
    uint64_t serviceTime;

    Connection(uint64_t srcLink, uint64_t dstLink, uint64_t numberOfFSUs, uint64_t serviceTime);
};

#endif //EONSIMULATOR_CONNECTION_H