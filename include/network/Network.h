#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <queue>
#include "Structure.h"
#include "../TrafficClassStatistics.h"

using namespace std;

class Network : public Structure {
    bool linkWasNotVisited(vector<Link *> &path, uint64_t node);

    bool pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, uint64_t requiredNumberOfFSUs, uint64_t &resultFirstFSU);

    bool linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs);

    Logger logger;

public:
    map<uint64_t, TrafficClassStatistics> erlangTrafficClasses;
    map<uint64_t, TrafficClassStatistics> engsetTrafficClasses;
    map<uint64_t, TrafficClassStatistics> pascalTrafficClasses;

    Network(SimulationSettings &settings);

    ~Network();

    enum ESTABLISH_CONNECTION_RESULT {
        CONNECTION_REJECTED,
        INTERNAL_BLOCK,
        EXTERNAL_BLOCK,
        CONNECTION_ESTABLISHED,
    };

    ESTABLISH_CONNECTION_RESULT establishConnection(double clock, Connection *connection);

    void reserveResources(Connection *connection);

    void closeConnection(double clock, Connection *connection);

    uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();

    bool everyOutputNodeIsAvailableFromEveryInputNode();
};

#endif //EONSIMULATOR_NETWORK_H