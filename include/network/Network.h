#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <queue>
#include "Structure.h"
#include "../Connection.h"
#include "../tools/Generator.h"
#include "../stats/TrafficClassStatistics.h"

class Network : public Structure {
	bool pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, Connection &connection, Generator &generator);

	bool linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs);

public:
	enum ESTABLISH_CONNECTION_RESULT {
		CONNECTION_REJECTED,
		INTERNAL_BLOCK,
		EXTERNAL_BLOCK,
		CONNECTION_CAN_BE_ESTABLISHED,
	};

	map<uint64_t, TrafficClassStatistics> erlangTrafficClasses;
	map<uint64_t, TrafficClassStatistics> engsetTrafficClasses;
	map<uint64_t, TrafficClassStatistics> pascalTrafficClasses;

	Network::ESTABLISH_CONNECTION_RESULT checkIfConnectionCanBeEstablished(Connection &connection, Generator &generator);

	void reserveResources(Connection connection);

	void closeConnection(double clock, Connection connection, Generator &generator);

	void closeAllConnections();

	uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();
};

#endif //EONSIMULATOR_NETWORK_H