#ifndef EONSIMULATOR_GLOBALSETTINGS_H
#define EONSIMULATOR_GLOBALSETTINGS_H

#include <iostream>
#include <set>
#include <regex>
#include "Logger.h"

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
		SERVICE_TIME,
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
			{SERVICE_TIME,      "-serviceTime"},
			{MODE,              "-mode"}
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
	uint64_t numberOfOutputDirections;
	double serviceTime;
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

	bool setServiceTime(PARAMETER_PREFIX prefix);

	bool setSelectedAlgorithm(PARAMETER_PREFIX prefix);

	bool maxTrafficClassRequireLessFSUsThanLinkCapacity();

public:
	static GlobalSettings &instance(function<GlobalSettings()> *init = nullptr);

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

	PATH_SELECTION_ALGORITHM getSelectedAlgorithm();

	void setNumberOfInputLinks(uint64_t numberOfInputLinks);

	void setNumberOfOutputDirections(uint64_t numberOfDirections);

	uint64_t getNumberOfInputLinks();

	uint64_t getNumberOfOutputDirections();
};

#endif //EONSIMULATOR_GLOBALSETTINGS_H