#include <fstream>
#include "../../include/tools/GlobalSettings.h"

GlobalSettings::GlobalSettings(map<string, string> args) : args(args) {
	readSettings();
}

void GlobalSettings::initialize(const map<string, string> &args) {
	function<GlobalSettings()> init = [args]() { return GlobalSettings(args); };
	instance(&init);
}

GlobalSettings &GlobalSettings::instance(function<GlobalSettings()> *init) {
	static GlobalSettings s{(*init)()};
	return s;
}

void GlobalSettings::readSettings() {
	bool aParametersAreValid = setA(A);
	bool structureFileNameIsValid = setStructureFileName(STRUCTURE);
	bool callsToGenerateIsValid = setCallsToGenerate(CALLS_TO_GENERATE);
	bool linkCapacityIsValid = setLinkCapacity(LINK_CAPACITY);
	bool erlangTrafficClassesAreValid = setErlangTrafficClasses(ERLANG);
	bool engsetTrafficClassesAreValid = setEngsetTrafficClasses(ENGSET);
	bool pascalTrafficClassesAreValid = setPascalTrafficClasses(PASCAL);
	bool runsIsValid = setRuns(RUNS);
	bool serviceTimeIsValid = setServiceTime(SERVICE_TIME);
	bool selectedAlgorithmIsValid = setSelectedAlgorithm(MODE);

	settingsAreValid = aParametersAreValid
					   && structureFileNameIsValid
					   && callsToGenerateIsValid
					   && linkCapacityIsValid
					   && runsIsValid
					   && serviceTimeIsValid
					   && selectedAlgorithmIsValid
					   && (erlangTrafficClassesAreValid || engsetTrafficClassesAreValid || pascalTrafficClassesAreValid)
					   && maxTrafficClassRequireLessFSUsThanLinkCapacity();
}

bool GlobalSettings::setA(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (getline(ss, token, ',')) {
		double aParameter;

		try {
			aParameter = stod(token);
		} catch (...) {
			Logger::instance().log(Logger::ERROR, "Error while parsing value " + parameter + ": " + value);
			return false;
		}

		if (aParameter <= 0.0) {
			Logger::instance().log(Logger::ERROR, parameter + " must be greater than 0. Current value: " + value);
			return false;
		}

		aParameters.insert(aParameter);
	}

	return true;
}

bool GlobalSettings::setStructureFileName(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	regex rx("^.+\\.[cC][sS][vV]$");
	bool fileExtensionIsCorrect = regex_match(value, rx);

	if (!fileExtensionIsCorrect) {
		Logger::instance().log(Logger::ERROR, parameter + " must point to a .csv file");
		return false;
	}

	structureFileName = value;
	return true;
}

bool GlobalSettings::setCallsToGenerate(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	try {
		callsToGenerate = stoi(value);
	} catch (...) {
		Logger::instance().log(Logger::ERROR, "Error while parsing value " + parameter + ". Current value: " + value);
		return false;
	}

	if (callsToGenerate <= 0) {
		Logger::instance().log(Logger::ERROR, parameter + " must be greater than 0. Current value: " + value);
		return false;
	}

	return true;
}

bool GlobalSettings::setLinkCapacity(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	try {
		linkCapacity = stoi(value);
	} catch (...) {
		Logger::instance().log(Logger::ERROR, "Error while parsing value " + parameter + ". Current value: " + value);
		return false;
	}

	if (linkCapacity <= 0) {
		Logger::instance().log(Logger::ERROR, parameter + " must be greater than 0. Current value: " + value);
		return false;
	}

	return true;
}

bool GlobalSettings::setErlangTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (getline(ss, token, ',')) {
		int trafficClass;

		try {
			trafficClass = stoi(token);
		} catch (...) {
			Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: " + token);
			return false;
		}

		if (trafficClass <= 0) {
			Logger::instance().log(Logger::ERROR, parameter + " traffic class must be greater than 0. Current value: " + to_string(trafficClass));
			return false;
		}

		erlangTrafficClasses.insert(trafficClass);
	}

	return true;
}

bool GlobalSettings::setEngsetTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (getline(ss, token, ',')) {
		int trafficClass;

		try {
			trafficClass = stoi(token);
		} catch (...) {
			Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: " + token);
			return false;
		}

		if (trafficClass <= 0) {
			Logger::instance().log(Logger::ERROR, parameter + " traffic class must be greater than 0. Current value: " + to_string(trafficClass));
			return false;
		}

		engsetTrafficClasses.insert(trafficClass);
	}

	return true;
}

bool GlobalSettings::setPascalTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (getline(ss, token, ',')) {
		int trafficClass;

		try {
			trafficClass = stoi(token);
		} catch (...) {
			Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: " + token);
			return false;
		}

		if (trafficClass <= 0) {
			Logger::instance().log(Logger::ERROR, parameter + " traffic class must be greater than 0. Current value: " + to_string(trafficClass));
			return false;
		}

		pascalTrafficClasses.insert(trafficClass);
	}

	return true;
}

bool GlobalSettings::setRuns(GlobalSettings::PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	try {
		runs = stoi(value);
	} catch (...) {
		Logger::instance().log(Logger::ERROR, "Error while parsing value " + parameter + ". Current value: " + value);
		return false;
	}

	if (runs <= 0) {
		Logger::instance().log(Logger::ERROR, parameter + " must be greater than 0. Current value: " + value);
		return false;
	}

	return true;
}

bool GlobalSettings::setServiceTime(GlobalSettings::PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	try {
		serviceTime = stod(value);
	} catch (...) {
		Logger::instance().log(Logger::ERROR, "Error while parsing value " + parameter + ". Current value: " + value);
		return false;
	}

	if (serviceTime <= 0) {
		Logger::instance().log(Logger::ERROR, parameter + " must be greater than 0. Current value: " + value);
		return false;
	}

	return true;
}

bool GlobalSettings::setSelectedAlgorithm(GlobalSettings::PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	if (value == "ptg") {
		selectedAlgorithm = POINT_TO_GROUP;
	} else if (value == "ptp") {
		selectedAlgorithm = POINT_TO_POINT;
	} else {
		Logger::instance().log(Logger::ERROR, parameter + " must be either ptg or ptp, which corresponds to point-to-group and point-to-point path selection algorithms");
		return false;
	}

	return true;
}

bool GlobalSettings::areValid() {
	return settingsAreValid;
}

set<double> GlobalSettings::getAParameters() {
	return aParameters;
}

string GlobalSettings::getStructureFileName() {
	return structureFileName;
}

uint64_t GlobalSettings::getCallsToGenerate() {
	return callsToGenerate;
}

uint64_t GlobalSettings::getLinkCapacity() {
	return linkCapacity;
}

uint64_t GlobalSettings::getNumberOfTrafficClasses() {
	return erlangTrafficClasses.size() + engsetTrafficClasses.size() + pascalTrafficClasses.size();
}

set<uint64_t> GlobalSettings::getErlangTrafficClasses() {
	return erlangTrafficClasses;
}

set<uint64_t> GlobalSettings::getEngsetTrafficClasses() {
	return engsetTrafficClasses;
}

set<uint64_t> GlobalSettings::getPascalTrafficClasses() {
	return pascalTrafficClasses;
}

uint64_t GlobalSettings::getRuns() {
	return runs;
}

double GlobalSettings::getServiceTime() {
	return serviceTime;
}

GlobalSettings::PATH_SELECTION_ALGORITHM GlobalSettings::getSelectedAlgorithm() {
	return selectedAlgorithm;
}

void GlobalSettings::setNumberOfInputLinks(uint64_t numberOfInputs) {
	this->numberOfInputLinks = numberOfInputs;
}

void GlobalSettings::setNumberOfOutputDirections(uint64_t numberOfDirections) {
	this->numberOfOutputDirections = numberOfDirections;
}

uint64_t GlobalSettings::getNumberOfInputLinks() {
	return numberOfInputLinks;
}

uint64_t GlobalSettings::getNumberOfOutputDirections() {
	return numberOfOutputDirections;
}

bool GlobalSettings::maxTrafficClassRequireLessFSUsThanLinkCapacity() {
	uint64_t erlangMaxTrafficClass = *max_element(erlangTrafficClasses.begin(), erlangTrafficClasses.end());
	uint64_t engsetMaxTrafficClass = *max_element(engsetTrafficClasses.begin(), engsetTrafficClasses.end());
	uint64_t pascalMaxTrafficClass = *max_element(pascalTrafficClasses.begin(), pascalTrafficClasses.end());

	if (erlangMaxTrafficClass > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Erlang traffic class requires " + to_string(erlangMaxTrafficClass) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	if (engsetMaxTrafficClass > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Engset traffic class requires " + to_string(engsetMaxTrafficClass) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	if (pascalMaxTrafficClass > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Pascal traffic class requires " + to_string(pascalMaxTrafficClass) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	return true;
}