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

	bool setFirstFSUOfInputLink(Link *link, Connection &connection, Generator &generator);

	bool setFirstFSUOfInternalLinks(vector<Link *> &path, Connection &connection, Generator &generator);

	bool setFirstFSUOfOutputLink(Link *link, Connection &connection, Generator &generator);

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

	uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();
};

#endif //EONSIMULATOR_NETWORK_H