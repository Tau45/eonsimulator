#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

#include <iostream>
#include "network/Path.h"
#include "tools/Generator.h"

class Connection {
	Link *sourceLink;
	uint64_t outputDirectionIndex;
	Path *path;
	uint64_t firstFSUOfInputLink;
	uint64_t firstFSUOfInternalLinks;
	uint64_t firstFSUOfOutputLink;
	uint64_t requiredNumberOfFSUs;
public:
	Connection(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs);

	void reserveResources();

	void close();

	void setSourceLink(Link* newSourceLink);

	Link *getSourceLink();

	Link *getDestinationLink();

	uint64_t getOutputDirectionIndex();

	uint64_t getPathSize();

	bool pathHasFreeResources(Path *path, Generator &generator);

	uint64_t getFirstFSUOfInputLink();

	uint64_t getFirstFSUOfInternalLinks();

	uint64_t getFirstFSUOfOutputLink();

	uint64_t getRequiredNumberOfFSUs();
};

#endif //EONSIMULATOR_CONNECTION_H