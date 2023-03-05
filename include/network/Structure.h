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
	vector<uint64_t> parseLine(const string &line);

	void createLink(uint64_t sourceNode, uint64_t destinationNode);

	void setInputOutputLinks();

	bool checkInputToOutputAvailability(Link* sourceLink, Link* destinationLink);

	bool everyOutputNodeIsAvailableFromEveryInputNode();

public:
	map<uint64_t, vector<Link *>> links;
	vector<Link *> inputLinks;
	vector<Link *> outputLinks;

	Structure();

	~Structure();

	void buildNetworkStructure();

	void printStructureDetails();

	bool isValid();

	bool linkWasNotVisited(vector<Link *> &path, Link *linkToCheck);

	uint64_t getNumberOfInputLinks();

	uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_STRUCTURE_H