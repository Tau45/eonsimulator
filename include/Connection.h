#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include <vector>
#include "network/Link.h"
#include "tools/Generator.h"

class Connection {
	uint64_t sourceLinkIndex;
	uint64_t destinationLinkIndex;
	vector<Link *> path;
	uint64_t firstFSUOfInputLink;
	uint64_t firstFSUOfInternalLinks;
	uint64_t firstFSUOfOutputLink;
	uint64_t requiredNumberOfFSUs;
	double serviceTime;
public:
	Connection(uint64_t sourceLinkIndex, uint64_t destinationLinkIndex, uint64_t requiredNumberOfFSUs, double serviceTime);

	void reserveResources();

	void close();

	uint64_t getSourceLinkIndex();

	uint64_t getDestinationLinkIndex();

	uint64_t getPathSize();

	void setPath(vector<Link *> &path);

	uint64_t getFirstFSUOfInputLink();

	uint64_t getFirstFSUOfInternalLinks();

	uint64_t getFirstFSUOfOutputLink();

	void setFirstFSUOfInputLink(uint64_t firstFSUOfInputLink);

	void setFirstFSUOfInternalLinks(uint64_t firstFSUOfInternalLinks);

	void setFirstFSUOfOutputLink(uint64_t firstFSUOfOutputLink);

	uint64_t getRequiredNumberOfFSUs();

	double getServiceTime();
};

#endif //EONSIMULATOR_CONNECTION_H