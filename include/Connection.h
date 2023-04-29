#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include <vector>
#include "network/Path.h"
#include "tools/Generator.h"

class Connection {
	Link *sourceLink;
	vector<Link *> *outputDirection;
	Path *path;
	uint64_t firstFSUOfInputLink;
	uint64_t firstFSUOfInternalLinks;
	uint64_t firstFSUOfOutputLink;
	uint64_t requiredNumberOfFSUs;
public:
	Connection(Link *sourceLink, vector<Link *> *outputDirection, uint64_t requiredNumberOfFSUs);

	void reserveResources();

	void close();

	Link *getSourceLink();

	Link *getDestinationLink();

	vector<Link *> *getOutputDirection();

	uint64_t getPathSize();

	bool pathHasFreeResources(Path *path, Generator &generator);

	uint64_t getFirstFSUOfInputLink();

	uint64_t getFirstFSUOfInternalLinks();

	uint64_t getFirstFSUOfOutputLink();

	void setFirstFSUOfInputLink(uint64_t firstFSUOfInputLink);

	void setFirstFSUOfInternalLinks(uint64_t firstFSUOfInternalLinks);

	void setFirstFSUOfOutputLink(uint64_t firstFSUOfOutputLink);

	uint64_t getRequiredNumberOfFSUs();
};

#endif //EONSIMULATOR_CONNECTION_H