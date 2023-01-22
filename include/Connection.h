#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include <vector>
#include "network/Link.h"
#include "tools/Generator.h"

class Connection {
	Link *sourceLink;
	Link *destinationLink;
	vector<Link *> path;
	uint64_t firstFSUOfInputLink;
	uint64_t firstFSUOfInternalLinks;
	uint64_t firstFSUOfOutputLink;
	uint64_t requiredNumberOfFSUs;
	double serviceTime;
public:
	Connection(Link *sourceLink, Link *destinationLink, uint64_t requiredNumberOfFSUs, double serviceTime);

	Connection(Connection &connection);

	Connection();

	void reserveResources();

	void close();

	Link *getSourceLink();

	Link *getDestinationLink();

	uint64_t getPathSize();

	void setPath(vector<Link *> path);

	uint64_t getFirstFSUOfInputLink();

	uint64_t getFirstFSUOfInternalLinks();

	uint64_t getFirstFSUOfOutputLink();

	void setFirstFSUOfInputLink(uint64_t firstFSU);

	void setFirstFSUOfInternalLinks(uint64_t firstFSU);

	void setFirstFSUOfOutputLink(uint64_t firstFSU);

	uint64_t getRequiredNumberOfFSUs();

	double getServiceTime();
};

#endif //EONSIMULATOR_CONNECTION_H