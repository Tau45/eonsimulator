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

    int64_t RESULT_EXTERNAL_BLOCK = -1;
    int64_t RESULT_INTERNAL_BLOCK = -2;

    void reserveResources(Connection *connection);

    static int linkWasNotVisited(vector<Link *> &path, int node);

    int64_t checkPathAvailability(vector<Link *> &path, uint64_t numberOfFSUs);

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