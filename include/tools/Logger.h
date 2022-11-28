#pragma once
#ifndef EONSIMULATOR_LOGGER_H
#define EONSIMULATOR_LOGGER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

class Logger {
    enum LOG_MESSAGE_TYPE {
        CONNECTION_REJECTED,
        INTERNAL_BLOCK,
        EXTERNAL_BLOCK,
        CONNECTION_ESTABLISHED,
        CONNECTION_CLOSED,
        CONNECTION_SETUP,
        SIMULATION_START,
        SIMULATION_END,
        CREATING_STRUCTURE,
        STRUCTURE_VALIDATION,
        PARSE_INPUT_PARAMETERS
    };

    map<LOG_MESSAGE_TYPE, string> logMessageTypeMap = {
            {CONNECTION_REJECTED,    "[CONNECTION_REJECTED   ] "},
            {INTERNAL_BLOCK,         "[INTERNAL_BLOCK        ] "},
            {EXTERNAL_BLOCK,         "[EXTERNAL_BLOCK        ] "},
            {CONNECTION_ESTABLISHED, "[CONNECTION_ESTABLISHED] "},
            {CONNECTION_CLOSED,      "[CONNECTION_CLOSED     ] "},
            {CONNECTION_SETUP,       "[CONNECTION_SETUP      ] "},
            {SIMULATION_START,       "[SIMULATION_START      ] "},
            {SIMULATION_END,         "[SIMULATION_END        ] "},
            {CREATING_STRUCTURE,     "[CREATING_STRUCTURE    ] "},
            {STRUCTURE_VALIDATION,   "[STRUCTURE_VALIDATION  ] "},
            {PARSE_INPUT_PARAMETERS, "[PARSE_INPUT_PARAMETERS] "}
    };

    string getTimestamp(double clock);

public:
    void log(bool logsEnabled, double clock, LOG_MESSAGE_TYPE prefix, const string &message);
};

#endif //EONSIMULATOR_LOGGER_H