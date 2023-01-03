#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include <vector>
#include "network/Link.h"

class Connection {
    uint64_t sourceLink;
    uint64_t destinationLink;
    vector<Link *> path;
    uint64_t firstFSU;
    uint64_t requiredNumberOfFSUs;
    double serviceTime;
public:
    Connection(uint64_t sourceLink, uint64_t destinationLink, uint64_t requiredNumberOfFSUs, double serviceTime);

    Connection(Connection &connection);

    Connection();

    uint64_t getSourceLink();

    uint64_t getDestinationLink();

    vector<Link *> getPath();

    void setPath(vector<Link *> path);

    uint64_t getFirstFSU();

    void setFirstFSU(uint64_t firstFSU);

    uint64_t getRequiredNumberOfFSUs();

    double getServiceTime();
};

#endif //EONSIMULATOR_CONNECTION_H