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
	bool selectedAlgorithmIsValid = setSelectedAlgorithm(MODE);

	settingsAreValid = aParametersAreValid
					   && structureFileNameIsValid
					   && callsToGenerateIsValid
					   && linkCapacityIsValid
					   && runsIsValid
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
	structureFileName = args[parameter];
	regex rx("^.+\\.[cC][sS][vV]$");
	bool fileExtensionIsCorrect = regex_match(structureFileName, rx);

	if (!fileExtensionIsCorrect) {
		Logger::instance().log(Logger::ERROR, parameter + " must point to a .csv file");
		return false;
	}

	ifstream file(structureFileName);

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string inputNodeIndexString;
		string outputNodeIndexString;

		if (getline(ss, inputNodeIndexString, ';') && getline(ss, outputNodeIndexString, ';')) {
			try {
				stoull(inputNodeIndexString);
			} catch (...) {
				Logger::instance().log(Logger::ERROR, "Error while parsing " + structureFileName + ": input node index: \"" + inputNodeIndexString + "\" cannot be converted to integer");
				return false;
			}
			try {
				stoull(outputNodeIndexString);
			} catch (...) {
				Logger::instance().log(Logger::ERROR, "Error while parsing " + structureFileName + ": output node index: \"" + outputNodeIndexString + "\" cannot be converted to integer");
				return false;
			}
		}
	}
	file.close();

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

	for (auto inputString: getTrafficClassDefinitionStrings(value)) {
		uint64_t numberOfFSUs;
		double serviceTime;

		bool numberOfFSUsWasFound = false;
		bool serviceTimeWasFound = false;

		stringstream ss(inputString);
		string token;

		while (getline(ss, token, ',')) {
			string prefix = token.substr(0, token.find(':'));
			string inputValue = token.substr(token.find(':') + 1, token.length());

			if (prefix == "FSUs") {
				try {
					numberOfFSUs = stoi(inputValue);
					numberOfFSUsWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing number of FSUs required by " + parameter + " traffic class: " + inputValue);
					return false;
				}

				if (numberOfFSUs <= 0) {
					Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class must be greater than 0. Current value: " + to_string(numberOfFSUs));
					return false;
				}
			} else if (prefix == "time") {
				try {
					serviceTime = stod(inputValue);
					serviceTimeWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing service time of " + parameter + " traffic class. Current value: " + inputValue);
					return false;
				}

				if (serviceTime <= 0) {
					Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class must be greater than 0. Current value: " + inputValue);
					return false;
				}
			} else {
				Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: unknown parameter: " + prefix);
				return false;
			}
		}

		if (numberOfFSUsWasFound && serviceTimeWasFound) {
			ErlangTrafficClassDefinition erlangTrafficClassDefinition(numberOfFSUs, serviceTime);
			erlangTrafficClasses.insert(erlangTrafficClassDefinition);
		} else {
			if (!numberOfFSUsWasFound) {
				Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class was not found");
			}
			if (!serviceTimeWasFound) {
				Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class was not found");
			}
			return false;
		}
	}

	if (erlangTrafficClasses.empty()) {
		Logger::instance().log(Logger::ERROR, "Error parsing " + parameter + " traffic classes");
		return false;
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

	for (auto inputString: getTrafficClassDefinitionStrings(value)) {
		uint64_t numberOfFSUs;
		double serviceTime;
		uint64_t numberOfTrafficClasses;

		bool numberOfFSUsWasFound = false;
		bool serviceTimeWasFound = false;
		bool numberOfTrafficClassesWasFound = false;

		stringstream ss(inputString);
		string token;

		while (getline(ss, token, ',')) {
			string prefix = token.substr(0, token.find(':'));
			string inputValue = token.substr(token.find(':') + 1, token.length());

			if (prefix == "FSUs") {
				try {
					numberOfFSUs = stoi(inputValue);
					numberOfFSUsWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing number of FSUs required by " + parameter + " traffic class: " + inputValue);
					return false;
				}

				if (numberOfFSUs <= 0) {
					Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class must be greater than 0. Current value: " + to_string(numberOfFSUs));
					return false;
				}
			} else if (prefix == "time") {
				try {
					serviceTime = stod(inputValue);
					serviceTimeWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing service time of " + parameter + " traffic class. Current value: " + inputValue);
					return false;
				}

				if (serviceTime <= 0) {
					Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class must be greater than 0. Current value: " + inputValue);
					return false;
				}
			} else if (prefix == "count") {
				try {
					numberOfTrafficClasses = stoi(inputValue);
					numberOfTrafficClassesWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing number of " + parameter + " traffic classes: " + inputValue);
					return false;
				}

				if (numberOfTrafficClasses <= 0) {
					Logger::instance().log(Logger::ERROR, "Number of " + parameter + " traffic classes must be greater than 0. Current value: " + to_string(numberOfTrafficClasses));
					return false;
				}
			} else {
				Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: unknown parameter: " + prefix);
				return false;
			}
		}

		if (numberOfFSUsWasFound && serviceTimeWasFound && numberOfTrafficClassesWasFound) {
			EngsetTrafficClassDefinition engsetTrafficClassDefinition(numberOfFSUs, serviceTime, numberOfTrafficClasses);
			engsetTrafficClasses.insert(engsetTrafficClassDefinition);
		} else {
			if (!numberOfFSUsWasFound) {
				Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class was not found");
			}
			if (!serviceTimeWasFound) {
				Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class was not found");
			}
			if (!numberOfTrafficClassesWasFound) {
				Logger::instance().log(Logger::ERROR, "Number of " + parameter + " traffic classes was not found");
			}
			return false;
		}
	}

	if (engsetTrafficClasses.empty()) {
		Logger::instance().log(Logger::ERROR, "Error parsing " + parameter + " traffic classes");
		return false;
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

	for (auto inputString: getTrafficClassDefinitionStrings(value)) {
		uint64_t numberOfFSUs;
		double serviceTime;
		uint64_t numberOfTrafficClasses;

		bool numberOfFSUsWasFound = false;
		bool serviceTimeWasFound = false;
		bool numberOfTrafficClassesWasFound = false;

		stringstream ss(inputString);
		string token;

		while (getline(ss, token, ',')) {
			string prefix = token.substr(0, token.find(':'));
			string inputValue = token.substr(token.find(':') + 1, token.length());

			if (prefix == "FSUs") {
				try {
					numberOfFSUs = stoi(inputValue);
					numberOfFSUsWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing number of FSUs required by " + parameter + " traffic class: " + inputValue);
					return false;
				}

				if (numberOfFSUs <= 0) {
					Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class must be greater than 0. Current value: " + to_string(numberOfFSUs));
					return false;
				}
			} else if (prefix == "time") {
				try {
					serviceTime = stod(inputValue);
					serviceTimeWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing service time of " + parameter + " traffic class. Current value: " + inputValue);
					return false;
				}

				if (serviceTime <= 0) {
					Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class must be greater than 0. Current value: " + inputValue);
					return false;
				}
			} else if (prefix == "count") {
				try {
					numberOfTrafficClasses = stoi(inputValue);
					numberOfTrafficClassesWasFound = true;
				} catch (...) {
					Logger::instance().log(Logger::ERROR, "Error while parsing number of " + parameter + " traffic classes: " + inputValue);
					return false;
				}

				if (numberOfTrafficClasses <= 0) {
					Logger::instance().log(Logger::ERROR, "Number of " + parameter + " traffic classes must be greater than 0. Current value: " + to_string(numberOfTrafficClasses));
					return false;
				}
			} else {
				Logger::instance().log(Logger::ERROR, "Error while parsing " + parameter + " traffic class: unknown parameter: " + prefix);
				return false;
			}
		}

		if (numberOfFSUsWasFound && serviceTimeWasFound && numberOfTrafficClassesWasFound) {
			PascalTrafficClassDefinition pascalTrafficClassDefinition(numberOfFSUs, serviceTime, numberOfTrafficClasses);
			pascalTrafficClasses.insert(pascalTrafficClassDefinition);
		} else {
			if (!numberOfFSUsWasFound) {
				Logger::instance().log(Logger::ERROR, "Number of FSUs required by " + parameter + " traffic class was not found");
			}
			if (!serviceTimeWasFound) {
				Logger::instance().log(Logger::ERROR, "Service time of " + parameter + " traffic class was not found");
			}
			if (!numberOfTrafficClassesWasFound) {
				Logger::instance().log(Logger::ERROR, "Number of " + parameter + " traffic classes was not found");
			}
			return false;
		}
	}

	if (pascalTrafficClasses.empty()) {
		Logger::instance().log(Logger::ERROR, "Error parsing " + parameter + " traffic classes");
		return false;
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

set<ErlangTrafficClassDefinition> GlobalSettings::getErlangTrafficClasses() {
	return erlangTrafficClasses;
}

set<EngsetTrafficClassDefinition> GlobalSettings::getEngsetTrafficClasses() {
	return engsetTrafficClasses;
}

set<PascalTrafficClassDefinition> GlobalSettings::getPascalTrafficClasses() {
	return pascalTrafficClasses;
}

uint64_t GlobalSettings::getRuns() {
	return runs;
}

GlobalSettings::PATH_SELECTION_ALGORITHM GlobalSettings::getSelectedAlgorithm() {
	return selectedAlgorithm;
}

bool GlobalSettings::maxTrafficClassRequireLessFSUsThanLinkCapacity() {
	uint64_t erlangMaxTrafficClassFSURequirement = 0;
	uint64_t engsetMaxTrafficClassFSURequirement = 0;
	uint64_t pascalMaxTrafficClassFSURequirement = 0;

	for (auto trafficClass: erlangTrafficClasses) {
		if (trafficClass.getRequiredNumberOfFSUs() > erlangMaxTrafficClassFSURequirement) {
			erlangMaxTrafficClassFSURequirement = trafficClass.getRequiredNumberOfFSUs();
		}
	}

	for (auto trafficClass: engsetTrafficClasses) {
		if (trafficClass.getRequiredNumberOfFSUs() > engsetMaxTrafficClassFSURequirement) {
			engsetMaxTrafficClassFSURequirement = trafficClass.getRequiredNumberOfFSUs();
		}
	}

	for (auto trafficClass: pascalTrafficClasses) {
		if (trafficClass.getRequiredNumberOfFSUs() > pascalMaxTrafficClassFSURequirement) {
			pascalMaxTrafficClassFSURequirement = trafficClass.getRequiredNumberOfFSUs();
		}
	}

	if (erlangMaxTrafficClassFSURequirement > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Erlang traffic class requires " + to_string(erlangMaxTrafficClassFSURequirement) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	if (engsetMaxTrafficClassFSURequirement > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Engset traffic class requires " + to_string(engsetMaxTrafficClassFSURequirement) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	if (pascalMaxTrafficClassFSURequirement > linkCapacity) {
		Logger::instance().log(Logger::ERROR, "Error: Pascal traffic class requires " + to_string(pascalMaxTrafficClassFSURequirement) + " FSUs while link capacity is " + to_string(linkCapacity));
		return false;
	}
	return true;
}

vector<string> GlobalSettings::getTrafficClassDefinitionStrings(string input) {
	vector<string> results;
	stack<uint64_t> delimiterPositions;

	for (uint64_t i = 0; i < input.size(); i++) {
		if (input[i] == '{') {
			delimiterPositions.push(i);
		} else if (input[i] == '}' && !delimiterPositions.empty()) {
			uint64_t openingDelimiterPosition = delimiterPositions.top();
			delimiterPositions.pop();

			string result = input.substr(openingDelimiterPosition + 1, i - 1 - openingDelimiterPosition);
			results.push_back(result);
		}
	}
	return results;
}