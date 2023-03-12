#ifndef EONSIMULATOR_STRUCTURE_H
#define EONSIMULATOR_STRUCTURE_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include "Link.h"
#include "../tools/Logger.h"
#include "../tools/GlobalSettings.h"

class Structure {
	map<uint64_t, vector<Link *>> links;
	vector<Link *> inputLinks;
	map<uint64_t, vector<Link *>> outputDirections;

	void buildNetworkStructure();

	vector<uint64_t> parseLine(const string &line);

	void createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t outputDirectionIndex);

	void setInputOutputLinks();

	bool checkInputToOutputAvailability(Link *sourceLink, Link *destinationLink);

	bool everyOutputNodeIsAvailableFromEveryInputNode();

	bool atLeastOneInputExists();

	bool atLeastOneOutputDirectionExists();

protected:
	bool linkWasNotVisited(vector<Link *> &path, Link *linkToCheck);

	bool structureIsOneLink();

public:
	Structure();

	~Structure();

	Link *getInputLink(uint64_t inputLinkIndex);

	vector<Link *> getAvailableLinksInOutputDirection(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs);

	vector<Link *> getNextHops(Link *sourceLink);

	void printStructureDetails();

	bool isValid();

	uint64_t getNumberOfInputLinks();

	uint64_t getNumberOfOutputDirections();
};

#endif //EONSIMULATOR_STRUCTURE_H