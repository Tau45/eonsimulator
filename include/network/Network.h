#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "../Connection.h"

using namespace std;

class Network {
    map<uint64_t, Connection> activeConnections;

    void setupConnection(Connection *connection);

    static int linkWasNotVisited(vector<Link *> &path, int node);

    int lookForAvailableBandwidthInPath(vector<Link *> &path, uint64_t numberOfFSUs);

    void printPath(vector<Link *> &path);

    bool pathIsExternallyBlocked(vector<Link *> &path, int numberOfFSUs);

protected:
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;
    vector<vector<Link *> > links;

public:
    Network();

    int tryToEstablishConnection(Connection *connection);

    void closeConnection(uint64_t connectionToCloseId);
};

#endif //EONSIMULATOR_NETWORK_H