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
	vector<Link *> outputLinks;

	void buildNetworkStructure();

	vector<uint64_t> parseLine(const string &line);

	void createLink(uint64_t sourceNode, uint64_t destinationNode);

	void setInputOutputLinks();

	bool checkInputToOutputAvailability(Link *sourceLink, Link *destinationLink);

	bool everyOutputNodeIsAvailableFromEveryInputNode();

protected:
	bool linkWasNotVisited(vector<Link *> &path, Link *linkToCheck);

	bool structureIsOneLink();

public:
	Structure();

	~Structure();

	Link *getInputLink(uint64_t inputLinkIndex);

	Link *getOutputLink(uint64_t outputLinkIndex);

	vector<Link *> getNextHops(Link *sourceLink);

	void printStructureDetails();

	bool isValid();

	uint64_t getNumberOfInputLinks();

	uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_STRUCTURE_H