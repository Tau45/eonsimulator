#ifndef EONSIMULATOR_SIMULATIONSETTINGS_H
#define EONSIMULATOR_SIMULATIONSETTINGS_H

#include <iostream>
#include <vector>
#include <regex>
#include "Logger.h"

using namespace std;

class SimulationSettings {
    bool aIsValid;
    bool structureFileNameIsValid;
    bool callsToGenerateIsValid;
    bool linkCapacityIsValid;
    bool anyTrafficClassIsPresent;

    void setA(const string &value);

    void setStructureFileName(const string &value);

    void setCallsToGenerate(const string &value);

    void setLinkCapacity(const string &value);

    void setTrafficClasses(const string &value, const string &trafficSource);

public:
    double a;
    string structureFileName;
    uint64_t callsToGenerate;
    uint64_t linkCapacity;
    vector<uint64_t> erlangTrafficClasses;
    vector<uint64_t> engsetTrafficClasses;
    vector<uint64_t> pascalTrafficClasses;
    bool logsEnabled;

    SimulationSettings(int numberOfParams, char **params);

    bool areValid();
};

#endif //EONSIMULATOR_SIMULATIONSETTINGS_H