#include <fstream>
#include "../../include/tools/SimulationSettings.h"

SimulationSettings::SimulationSettings(map<string, string> args) : args(args) {
	readSettings();
}

void SimulationSettings::initialize(const map<string, string> &args) {
	function<SimulationSettings()> init = [args]() { return SimulationSettings(args); };
	instance(&init);
}

SimulationSettings &SimulationSettings::instance(function<SimulationSettings()> *init) {
	static SimulationSettings s{(*init)()};
	return s;
}

void SimulationSettings::readSettings() {
	bool aParametersAreValid = setA(A);
	bool structureFileNameIsValid = setStructureFileName(STRUCTURE);
	bool callsToGenerateIsValid = setCallsToGenerate(CALLS_TO_GENERATE);
	bool linkCapacityIsValid = setLinkCapacity(LINK_CAPACITY);
	bool erlangTrafficClassesAreValid = setErlangTrafficClasses(ERLANG);
	bool engsetTrafficClassesAreValid = setEngsetTrafficClasses(ENGSET);
	bool pascalTrafficClassesAreValid = setPascalTrafficClasses(PASCAL);
	bool runsIsValid = setRuns(RUNS);
	bool serviceTimeIsValid = setServiceTime(SERVICE_TIME);

	settingsAreValid = aParametersAreValid
					   && structureFileNameIsValid
					   && callsToGenerateIsValid
					   && linkCapacityIsValid
					   && runsIsValid
					   && serviceTimeIsValid
					   && (erlangTrafficClassesAreValid || engsetTrafficClassesAreValid || pascalTrafficClassesAreValid)
					   && maxTrafficClassRequireLessFSUsThanLinkCapacity();
}

bool SimulationSettings::setA(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::ERROR, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (std::getline(ss, token, ',')) {
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

bool SimulationSettings::setStructureFileName(PARAMETER_PREFIX prefix) {
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

bool SimulationSettings::setCallsToGenerate(PARAMETER_PREFIX prefix) {
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

bool SimulationSettings::setLinkCapacity(PARAMETER_PREFIX prefix) {
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

bool SimulationSettings::setErlangTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (std::getline(ss, token, ',')) {
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

bool SimulationSettings::setEngsetTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (std::getline(ss, token, ',')) {
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

bool SimulationSettings::setPascalTrafficClasses(PARAMETER_PREFIX prefix) {
	string parameter = parameterMap[prefix];
	if (!args.count(parameter)) {
		Logger::instance().log(Logger::WARN, "Parameter " + parameter + " was not found");
		return false;
	}
	string value = args[parameter];
	stringstream ss(value);
	string token;

	while (std::getline(ss, token, ',')) {
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

bool SimulationSettings::setRuns(SimulationSettings::PARAMETER_PREFIX prefix) {
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

bool SimulationSettings::setServiceTime(SimulationSettings::PARAMETER_PREFIX prefix) {
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

bool SimulationSettings::areValid() {
	return settingsAreValid;
}

set<double> SimulationSettings::getAParameters() {
	return aParameters;
}

string SimulationSettings::getStructureFileName() {
	return structureFileName;
}

uint64_t SimulationSettings::getCallsToGenerate() {
	return callsToGenerate;
}

uint64_t SimulationSettings::getLinkCapacity() {
	return linkCapacity;
}

uint64_t SimulationSettings::getNumberOfTrafficClasses() {
	return erlangTrafficClasses.size() + engsetTrafficClasses.size() + pascalTrafficClasses.size();
}

set<uint64_t> SimulationSettings::getErlangTrafficClasses() {
	return erlangTrafficClasses;
}

set<uint64_t> SimulationSettings::getEngsetTrafficClasses() {
	return engsetTrafficClasses;
}

set<uint64_t> SimulationSettings::getPascalTrafficClasses() {
	return pascalTrafficClasses;
}

uint64_t SimulationSettings::getRuns() {
	return runs;
}

double SimulationSettings::getServiceTime() {
	return serviceTime;
}

void SimulationSettings::setNumberOfInputLinks(uint64_t numberOfInputs) {
	this->numberOfInputLinks = numberOfInputs;
}

void SimulationSettings::setNumberOfOutputLinks(uint64_t numberOfOutputs) {
	this->numberOfOutputLinks = numberOfOutputs;
}

uint64_t SimulationSettings::getNumberOfInputLinks() {
	return numberOfInputLinks;
}

uint64_t SimulationSettings::getNumberOfOutputLinks() {
	return numberOfOutputLinks;
}

bool SimulationSettings::maxTrafficClassRequireLessFSUsThanLinkCapacity() {
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