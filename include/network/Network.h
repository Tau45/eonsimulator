#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include "../Connection.h"
#include "../TrafficClassStatistics.h"
#include "../tools/Logger.h"

using namespace std;

class Network {
    map<uint64_t, vector<Link *>> links;
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;

    list<Connection *> activeConnections;

    void reserveResources(Connection *connection);

    static int linkWasNotVisited(vector<Link *> &path, uint64_t node);

    bool connectionCanBeSetUp(vector<Link *> &path, uint64_t numberOfFSUs, uint64_t &resultFirstFSU);

    bool linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs);

protected:
    void createLink(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput);

public:
    map<uint64_t, TrafficClassStatistics> erlangTrafficClasses;
    map<uint64_t, TrafficClassStatistics> engsetTrafficClasses;
    map<uint64_t, TrafficClassStatistics> pascalTrafficClasses;

    ~Network();

    bool establishConnection(Connection *connection, TrafficClassStatistics &statistics);

    void closeConnection(Connection *connection);

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();

    uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();
};

#endif //EONSIMULATOR_NETWORK_H