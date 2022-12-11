#ifndef EONSIMULATOR_STRUCTURE_H
#define EONSIMULATOR_STRUCTURE_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include "../Link.h"
#include "../tools/Logger.h"
#include "../tools/SimulationSettings.h"

class Structure {
    void createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity, bool isInput, bool isOutput);

    void printStructureDetails(vector<vector<int>> &nodes);

    bool checkInputToOutputAvailability(uint64_t sourceLinkIndex, uint64_t destinationLinkIndex);

    bool everyOutputNodeIsAvailableFromEveryInputNode();

public:
    map<uint64_t, vector<Link *>> links;
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;

    void buildNetworkStructure();

    bool isValid();

    bool linkWasNotVisited(vector<Link *> &path, uint64_t node);

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_STRUCTURE_H