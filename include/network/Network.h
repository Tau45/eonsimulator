#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include "../Connection.h"
#include "../tools/Logger.h"

using namespace std;

class Network {
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;
    vector<vector<Link *> > links;

    list<Connection *> activeConnections;

    void reserveResources(Connection *connection);

    static int linkWasNotVisited(vector<Link *> &path, int node);

    bool connectionCanBeSetUp(vector<Link *> &path, uint64_t numberOfFSUs, uint64_t &resultFirstFSU);

    void printPath(vector<Link *> &path);

    bool pathIsExternallyBlocked(vector<Link *> &path, uint64_t numberOfFSUs);

protected:
    void setNumberOfNodes(uint64_t numberOfNodes);

    void createInputLink(uint64_t sourceNode, uint64_t destinationNode);

    void createLink(uint64_t sourceNode, uint64_t destinationNode);

    void createOutputLink(uint64_t sourceNode, uint64_t destinationNode);

public:
    uint64_t internalBlocksCount;
    uint64_t externalBlocksCount;

    Network();

    ~Network();

    bool establishConnection(Connection *connection, uint64_t clock);

    void closeConnection(Connection *connection, uint64_t clock);
};

#endif //EONSIMULATOR_NETWORK_H