#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <vector>
#include <queue>
#include "../Link.h"

using namespace std;

class Network {
    uint64_t connectionId;

    void setupConnection(vector<Link *> &path, int fsuIndex, int numberOfFSUs) const;

    static int isNotVisited(vector<Link *> &path, int node);

    int findAvailableBandwidth(vector<Link *> &path, int numberOfFSUs);

    void printPath(vector<Link *> &path);

    bool pathIsExternallyBlocked(vector<Link *> &path, int numberOfFSUs);

protected:
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;
    vector<vector<Link *> > links;

public:
    Network();

    void establishConnection(int srcLinkIndex, int dstLinkIndex, int numberOfFSUs);
};

#endif //EONSIMULATOR_NETWORK_H