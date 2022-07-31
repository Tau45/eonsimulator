#ifndef EONSIMULATOR_STRUCTURE_H
#define EONSIMULATOR_STRUCTURE_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include "../Connection.h"
#include "../tools/Logger.h"

class Structure {
    void createLink(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput);
public:
    map<uint64_t, vector<Link *>> links;
    vector<Link *> inputLinks;
    vector<Link *> outputLinks;

    list<Connection *> activeConnections;

    bool createStructure(string structureFileName);

    uint64_t getNumberOfInputLinks();

    uint64_t getNumberOfOutputLinks();
};


#endif //EONSIMULATOR_STRUCTURE_H
