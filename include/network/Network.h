#pragma once
#ifndef EONSIMULATOR_NETWORK_H
#define EONSIMULATOR_NETWORK_H

#include <queue>
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

	bool pathHasFreeResources(Path *path, Connection *connection);

	vector<Link *> getAvailableLinksToDestination(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs);

	bool inputLinkWithFreeResourcesWasFound(Connection *connection, Generator &generator);

	void setFirstFSUOfOutputLink(Link *outputLink, Connection *connection);

	bool anyOutputLinkHasFreeResources(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs);

	bool structureIsOneLink();

public:
	map<uint64_t, TrafficClassStatistics> trafficClassStatistics;

	Network();

	~Network();

	Network::ESTABLISH_CONNECTION_RESULT checkIfConnectionCanBeEstablished(Connection *connection, Generator &generator);

	uint64_t getNumberOfGeneratedCallsOfTheLeastActiveClass();

	uint64_t getNumberOfOutputDirections();

	uint64_t getNumberOfInputLinks();

	void printNetworkStructure();
};

#endif //EONSIMULATOR_NETWORK_H