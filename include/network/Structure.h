#ifndef EONSIMULATOR_STRUCTURE_H
#define EONSIMULATOR_STRUCTURE_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include "../Connection.h"
#include "../tools/Logger.h"
#include "../tools/SimulationSettings.h"

class Structure {
    void createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity, bool isInput, bool isOutput);

    void createStructure();

    void printStructureDetails(vector<vector<int>> &nodes);

    Logger logger;
public:
    SimulationSettings *settings;

    map<uint64_t, vector<Link *>> links;
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;

    list<Connection *> activeConnections;

    Structure(SimulationSettings &settings);

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_STRUCTURE_H