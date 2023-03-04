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
        PASCAL,
        RUNS,
		SERVICE_TIME
    };

    map<PARAMETER_PREFIX, string> parameterMap = {
            {A,                 "-a"},
            {STRUCTURE,         "-structure"},
            {CALLS_TO_GENERATE, "-callsToGenerate"},
            {LINK_CAPACITY,     "-linkCapacity"},
            {ERLANG,            "-erlang"},
            {ENGSET,            "-engset"},
            {PASCAL,            "-pascal"},
            {RUNS,              "-runs"},
			{SERVICE_TIME,		"-serviceTime"}
    };

	map<string, string> args;
    bool settingsAreValid;
    set<double> aParameters;
    string structureFileName;
    uint64_t callsToGenerate;
    uint64_t linkCapacity;
    set<uint64_t> erlangTrafficClasses;
    set<uint64_t> engsetTrafficClasses;
    set<uint64_t> pascalTrafficClasses;
    uint64_t runs;
	uint64_t numberOfInputLinks;
	uint64_t numberOfOutputLinks;
	double serviceTime;

    SimulationSettings(map<string, string> args);

    SimulationSettings(const SimulationSettings &) = delete;

    void operator=(const SimulationSettings &) = delete;

	void readSettings();

    bool setA(PARAMETER_PREFIX prefix);

    bool setStructureFileName(PARAMETER_PREFIX prefix);

    bool setCallsToGenerate(PARAMETER_PREFIX prefix);

    bool setLinkCapacity(PARAMETER_PREFIX prefix);

    bool setErlangTrafficClasses(PARAMETER_PREFIX prefix);

    bool setEngsetTrafficClasses(PARAMETER_PREFIX prefix);

    bool setPascalTrafficClasses(PARAMETER_PREFIX prefix);

    bool setRuns(PARAMETER_PREFIX prefix);

    bool setServiceTime(PARAMETER_PREFIX prefix);

    bool maxTrafficClassRequireLessFSUsThanLinkCapacity();

public:
    static SimulationSettings &instance(function<SimulationSettings()> *init = nullptr);

    static void initialize(const map<string, string> &args);

    bool areValid();

    set<double> getAParameters();

    string getStructureFileName();

    uint64_t getCallsToGenerate();

    uint64_t getLinkCapacity();

    uint64_t getNumberOfTrafficClasses();

    set<uint64_t> getErlangTrafficClasses();

    set<uint64_t> getEngsetTrafficClasses();

    set<uint64_t> getPascalTrafficClasses();

    uint64_t getRuns();

	double getServiceTime();

	void setNumberOfInputLinks(uint64_t numberOfInputLinks);

	void setNumberOfOutputLinks(uint64_t numberOfOutputLinks);

	uint64_t getNumberOfInputLinks();

	uint64_t getNumberOfOutputLinks();
};

#endif //EONSIMULATOR_SIMULATIONSETTINGS_H