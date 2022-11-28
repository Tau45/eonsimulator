#include <fstream>
#include "../../include/tools/SimulationSettings.h"

SimulationSettings::SimulationSettings(int numberOfParams, char **params) {
    aIsValid = false;
    structureFileNameIsValid = false;
    callsToGenerateIsValid = false;
    linkCapacityIsValid = false;
    anyTrafficClassIsPresent = false;
    logsEnabled = false;

    for (uint64_t i = 1; i < numberOfParams; i++) {
        string param = params[i];

        string prefix = param.substr(0, param.find(':'));
        string inputValue = param.substr(param.find(':') + 1, param.length());

        if (prefix == "-a") { setA(inputValue); }
        else if (prefix == "-structure") { setStructureFileName(inputValue); }
        else if (prefix == "-callsToGenerate") { setCallsToGenerate(inputValue); }
        else if (prefix == "-fsus") { setLinkCapacity(inputValue); }
        else if (prefix == "-erlang" || prefix == "-engset" || prefix == "-pascal") { setTrafficClasses(inputValue, prefix); }
        else if (prefix == "-logs") { logsEnabled = true; }
        else { cout << "Could not parse parameter: " << param << endl; }
    }
}

bool SimulationSettings::areValid() {
    return aIsValid
           && structureFileNameIsValid
           && callsToGenerateIsValid
           && linkCapacityIsValid
           && anyTrafficClassIsPresent;
}

void SimulationSettings::setA(const string &inputValue) {
    try {
        a = stod(inputValue);
    } catch (...) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "Error while parsing value -a: " + inputValue);
        return;
    }

    if (a <= 0.0) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "-a must be greater than 0");
        return;
    }

    aIsValid = true;
}

void SimulationSettings::setStructureFileName(const string &value) {
    regex rx("^.+\\.(?:[cC][sS][vV])$");
    bool fileExtensionIsCorrect = regex_match(value, rx);

    if (fileExtensionIsCorrect) {
        structureFileName = value;
    } else {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "-structureFileName must point to a .csv file");
        return;
    }

    structureFileNameIsValid = true;
}

void SimulationSettings::setCallsToGenerate(const string &value) {
    try {
        callsToGenerate = stoi(value);
    } catch (...) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "Error while parsing value -callsToGenerate: " + value);
        return;
    }

    if (callsToGenerate <= 0) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "-callsToGenerate must be greater than 0");
        return;
    }

    callsToGenerateIsValid = true;
}

void SimulationSettings::setLinkCapacity(const string &value) {
    try {
        linkCapacity = stoi(value);
    } catch (...) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "Error while parsing value -linkCapacity: " + value);
        return;
    }

    if (linkCapacity <= 0) {
        Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "-linkCapacity must be greater than 0");
        return;
    }

    linkCapacityIsValid = true;
}

void SimulationSettings::setTrafficClasses(const string &value, const string &trafficSource) {
    stringstream ss(value);
    string token;

    while (std::getline(ss, token, ',')) {
        int trafficClass;

        try {
            trafficClass = stoi(token);
        } catch (...) {
            Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "Error while parsing " + trafficSource + ": " + token);
            return;
        }

        if (trafficClass <= 0) {
            Logger::getInstance().log(true, 0, Logger::PARSE_INPUT_PARAMETERS, "Traffic class must be greater than 0");
            return;
        }

        if (trafficSource == "-erlang") {
            erlangTrafficClasses.push_back(trafficClass);
        } else if (trafficSource == "-engset") {
            engsetTrafficClasses.push_back(trafficClass);
        } else if (trafficSource == "-pascal") {
            pascalTrafficClasses.push_back(trafficClass);
        }

        anyTrafficClassIsPresent = true;
    }
}