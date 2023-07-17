#pragma once
#ifndef EONSIMULATOR_GLOBALSETTINGS_H
#define EONSIMULATOR_GLOBALSETTINGS_H

#include <set>
#include <regex>
#include <fstream>
#include "Logger.h"
#include "definition/EngsetTrafficClassDefinition.h"
#include "definition/ErlangTrafficClassDefinition.h"
#include "definition/PascalTrafficClassDefinition.h"

class GlobalSettings {
public:
	enum PATH_SELECTION_ALGORITHM {
		POINT_TO_GROUP,
		POINT_TO_POINT
	};
private:
	enum PARAMETER_PREFIX {
		A,
		STRUCTURE,
		CALLS_TO_GENERATE,
		LINK_CAPACITY,
		ERLANG,
		ENGSET,
		PASCAL,
		RUNS,
		MODE
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
			{MODE,              "-mode"}
	};

	map<string, string> args;
	bool settingsAreValid;
	set<double> aParameters;
	string structureFileName;
	uint64_t callsToGenerate;
	uint64_t linkCapacity;
	set<ErlangTrafficClassDefinition> erlangTrafficClasses;
	set<EngsetTrafficClassDefinition> engsetTrafficClasses;
	set<PascalTrafficClassDefinition> pascalTrafficClasses;
	uint64_t runs;
	PATH_SELECTION_ALGORITHM selectedAlgorithm;

	GlobalSettings(map<string, string> args);

	GlobalSettings(const GlobalSettings &) = delete;

	void operator=(const GlobalSettings &) = delete;

	void readSettings();

	bool setA(PARAMETER_PREFIX prefix);

	bool setStructureFileName(PARAMETER_PREFIX prefix);

	bool setCallsToGenerate(PARAMETER_PREFIX prefix);

	bool setLinkCapacity(PARAMETER_PREFIX prefix);

	bool setErlangTrafficClasses(PARAMETER_PREFIX prefix);

	bool setEngsetTrafficClasses(PARAMETER_PREFIX prefix);

	bool setPascalTrafficClasses(PARAMETER_PREFIX prefix);

	bool setRuns(PARAMETER_PREFIX prefix);

	bool setSelectedAlgorithm(PARAMETER_PREFIX prefix);

	bool maxTrafficClassRequireLessFSUsThanLinkCapacity();

	vector<string> getTrafficClassDefinitionStrings(string input);

public:
	static GlobalSettings &instance(function<GlobalSettings()> *init = nullptr);

	static void initialize(const map<string, string> &args);

	bool areValid();

	set<double> getAParameters();

	string getStructureFileName();

	uint64_t getCallsToGenerate();

	uint64_t getLinkCapacity();

	uint64_t getNumberOfTrafficClasses();

	set<ErlangTrafficClassDefinition> getErlangTrafficClasses();

	set<EngsetTrafficClassDefinition> getEngsetTrafficClasses();

	set<PascalTrafficClassDefinition> getPascalTrafficClasses();

	uint64_t getRuns();

	PATH_SELECTION_ALGORITHM getSelectedAlgorithm();
};

#endif //EONSIMULATOR_GLOBALSETTINGS_H