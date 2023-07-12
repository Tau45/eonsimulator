#pragma once
#ifndef EONSIMULATOR_CONNECTION_H
#define EONSIMULATOR_CONNECTION_H

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

	void setSourceLink(Link *newSourceLink);

	Link *getSourceLink();

	Link *getDestinationLink();

	uint64_t getOutputDirectionIndex();

	uint64_t getPathSize();

	void setPath(Path *newPath);

	uint64_t getFirstFSUOfInputLink();

	uint64_t getFirstFSUOfInternalLinks();

	uint64_t getFirstFSUOfOutputLink();

	void setFirstFSUOfInputLink(uint64_t firstFSU);

	void setFirstFSUOfInternalLinks(uint64_t firstFSU);

	void setFirstFSUOfOutputLink(uint64_t firstFSU);

	uint64_t getRequiredNumberOfFSUs();
};

#endif //EONSIMULATOR_CONNECTION_H