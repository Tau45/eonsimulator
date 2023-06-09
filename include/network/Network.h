#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include "../Connection.h"
#include "../stats/TrafficClassStatistics.h"

class Network {
public:
	enum ESTABLISH_CONNECTION_RESULT {
		CONNECTION_REJECTED,
		INTERNAL_BLOCK,
		EXTERNAL_BLOCK,
		CONNECTION_CAN_BE_ESTABLISHED
	};

private:
	map<Link *, map<Link *, vector<Path *>>> paths;
	vector<Link *> inputLinks;
	vector<vector<Link *>> outputDirections;

	Network::ESTABLISH_CONNECTION_RESULT checkIfConnectionCanBeEstablishedPointToGroup(Connection *connection, Generator &generator);

	Network::ESTABLISH_CONNECTION_RESULT checkIfConnectionCanBeEstablishedPointToPoint(Connection *connection, Generator &generator);

	void buildNetworkStructure();

	vector<Path *> getAllInternalPathsBetweenLinks(Link *inputLink, Link *destinationLink);

	vector<Link *> getAvailableLinksToDestination(vector<Link *> outputDirection, uint64_t requiredNumberOfFSUs);

	bool findInputLinkWithFreeResources(Connection *connection, Generator &generator);

	bool anyOutputLinkHasFreeResources(vector<Link *> outputDirection, uint64_t requiredNumberOfFSUs);

	bool structureIsOneLink();

public:
	map<uint64_t, TrafficClassStatistics> erlangTrafficClassStatistics;
	map<uint64_t, TrafficClassStatistics> engsetTrafficClassStatistics;
	map<uint64_t, TrafficClassStatistics> pascalTrafficClassStatistics;

	Network();

	~Network();

	Network::ESTABLISH_CONNECTION_RESULT checkIfConnectionCanBeEstablished(Connection *connection, Generator &generator);

	uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();

	uint64_t getNumberOfOutputDirections();

	uint64_t getNumberOfInputLinks();

	void printNetworkStructure();
};

#endif //EONSIMULATOR_NETWORK_H