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

    bool linkWasNotVisited(vector<Link *> &path, uint64_t node);

    bool pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, uint64_t requiredNumberOfFSUs, uint64_t &resultFirstFSU);

    bool linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs);

protected:
    void createLink(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput);

public:
    map<uint64_t, TrafficClassStatistics> erlangTrafficClasses;
    map<uint64_t, TrafficClassStatistics> engsetTrafficClasses;
    map<uint64_t, TrafficClassStatistics> pascalTrafficClasses;

    ~Network();

    enum ESTABLISH_CONNECTION_RESULT {
        CONNECTION_REJECTED,
        INTERNAL_BLOCK,
        EXTERNAL_BLOCK,
        CONNECTION_ESTABLISHED,
    };

    ESTABLISH_CONNECTION_RESULT tryToEstablishConnection(double clock, Connection *connection);

    void reserveResources(Connection *connection);

    void closeConnection(double clock, Connection *connection);

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();

    uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();
};

#endif //EONSIMULATOR_NETWORK_H