#pragma once
#ifndef EONSIMULATOR_PATH_H
#define EONSIMULATOR_PATH_H

#include "Link.h"

class Path {
	vector<Link *> path;

public:
	Path(vector<Link *> &path);

	Link *getInputLink();

	vector<Link *> getInternalLinks();

	Link *getOutputLink();

	uint64_t getPathSize();

	vector<Link *> getPath();

	vector<uint64_t> getAvailableFirstFSUsInInternalLinks(uint64_t requiredNumberOfFSUs);
};

#endif //EONSIMULATOR_PATH_H