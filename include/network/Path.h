#ifndef EONSIMULATOR_PATH_H
#define EONSIMULATOR_PATH_H

#include <iostream>
#include <vector>
#include "Link.h"

class Path {
	vector<Link *> path;

public:
	Path() {}

	Path(vector<Link *> &path);

	Link *getInputLink();

	vector<Link *> getInternalLinks();

	Link *getOutputLink();

	uint64_t getPathSize();

	vector<Link *> getPath();

	vector<uint64_t> getAvailableFirstFSUsInInputLink(uint64_t requiredNumberOfFSUs);

	vector<uint64_t> getAvailableFirstFSUsInInternalLinks(uint64_t requiredNumberOfFSUs);

	vector<uint64_t> getAvailableFirstFSUsInOutputLink(uint64_t requiredNumberOfFSUs);
};

#endif //EONSIMULATOR_PATH_H