#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include "../Connection.h"
#include "../tools/Logger.h"

using namespace std;

class Network {
    list<Connection *> activeConnections;

    void reserveResources(Connection *connection);

    static int linkWasNotVisited(vector<Link *> &path, uint64_t node);

    bool connectionCanBeSetUp(vector<Link *> &path, uint64_t numberOfFSUs, uint64_t &resultFirstFSU);

    void printPath(vector<Link *> &path);

    bool linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs);

protected:
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;

    void setNumberOfNodes(uint64_t numberOfNodes);

    void createInputLink(uint64_t sourceNode, uint64_t destinationNode);

    void createLink(uint64_t sourceNode, uint64_t destinationNode);

    void createOutputLink(uint64_t sourceNode, uint64_t destinationNode);

public:
    uint64_t blocksCount[5];
    uint64_t internalBlocksCountErlangTraffic[5];
    uint64_t externalBlocksCountErlangTraffic[5];

    Network();

    ~Network();

    bool establishConnection(Connection *connection, uint64_t clock, uint64_t trafficClass, uint64_t &callsGenerated);

    void closeConnection(Connection *connection, uint64_t clock);

    vector<vector<Link *> > links;

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_NETWORK_H