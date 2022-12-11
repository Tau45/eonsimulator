#ifndef EONSIMULATOR_SIMULATIONSETTINGS_H
#define EONSIMULATOR_SIMULATIONSETTINGS_H

#include <iostream>
#include <set>
#include <regex>
#include "Logger.h"

class SimulationSettings {
    enum PARAMETER_PREFIX {
        A,
        STRUCTURE,
        CALLS_TO_GENERATE,
        LINK_CAPACITY,
        ERLANG,
        ENGSET,
        PASCAL
    };

    map<PARAMETER_PREFIX, string> parameterMap = {
            {A,                 "-a"},
            {STRUCTURE,         "-structure"},
            {CALLS_TO_GENERATE, "-callsToGenerate"},
            {LINK_CAPACITY,     "-linkCapacity"},
            {ERLANG,            "-erlang"},
            {ENGSET,            "-engset"},
            {PASCAL,            "-pascal"}
    };

    bool settingsAreValid;
    double a;
    string structureFileName;
    uint64_t callsToGenerate;
    uint64_t linkCapacity;
    set<uint64_t> erlangTrafficClasses;
    set<uint64_t> engsetTrafficClasses;
    set<uint64_t> pascalTrafficClasses;

    SimulationSettings(map<string, string> args);

    SimulationSettings(const SimulationSettings &) = delete;

    void operator=(const SimulationSettings &) = delete;

    bool setA(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setStructureFileName(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setCallsToGenerate(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setLinkCapacity(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setErlangTrafficClasses(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setEngsetTrafficClasses(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool setPascalTrafficClasses(map<string, string> &args, PARAMETER_PREFIX prefix);

    bool maxTrafficClassRequireLessFSUsThanLinkCapacity();

public:
    static SimulationSettings &instance(function<SimulationSettings()> *init = nullptr);

    static void initialize(const map<string, string> &args);

    bool areValid();

    double getA();

    string getStructureFileName();

    uint64_t getCallsToGenerate();

    uint64_t getLinkCapacity();

    uint64_t getNumberOfTrafficClasses();

    set<uint64_t> getErlangTrafficClasses();

    set<uint64_t> getEngsetTrafficClasses();

    set<uint64_t> getPascalTrafficClasses();
};

#endif //EONSIMULATOR_SIMULATIONSETTINGS_H