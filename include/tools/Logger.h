#pragma once
#ifndef EONSIMULATOR_LOGGER_H
#define EONSIMULATOR_LOGGER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <functional>

using namespace std;

class Logger {
public:
    enum LOG_MESSAGE_TYPE {
        CONNECTION_REJECTED,
        INTERNAL_BLOCK,
        EXTERNAL_BLOCK,
        CONNECTION_ESTABLISHED,
        CONNECTION_CLOSED,
        CONNECTION_SETUP,
        SIMULATION_START,
        SIMULATION_END,
		ALL_SIMULATIONS_ENDED,
        CREATING_STRUCTURE,
        STRUCTURE_VALIDATION,
        ERROR,
        WARN
    };

	static Logger &instance(function<Logger()> *init = nullptr);

	static void initialize(bool logsEnabled);

    void log(double clock, LOG_MESSAGE_TYPE prefix, const string &message);

private:
    bool logsEnabled;
    map<LOG_MESSAGE_TYPE, string> logMessageTypeMap = {
            {CONNECTION_REJECTED,    "[CONNECTION_REJECTED   ] "},
            {INTERNAL_BLOCK,         "[INTERNAL_BLOCK        ] "},
            {EXTERNAL_BLOCK,         "[EXTERNAL_BLOCK        ] "},
            {CONNECTION_ESTABLISHED, "[CONNECTION_ESTABLISHED] "},
            {CONNECTION_CLOSED,      "[CONNECTION_CLOSED     ] "},
            {CONNECTION_SETUP,       "[CONNECTION_SETUP      ] "},
            {SIMULATION_START,       "[SIMULATION_START      ] "},
            {SIMULATION_END,         "[SIMULATION_END        ] "},
            {ALL_SIMULATIONS_ENDED,  "[ALL_SIMULATIONS_ENDED ] "},
            {CREATING_STRUCTURE,     "[CREATING_STRUCTURE    ] "},
            {STRUCTURE_VALIDATION,   "[STRUCTURE_VALIDATION  ] "},
            {ERROR,                  "[ERROR                 ] "},
            {WARN,                   "[WARN                  ] "}
    };

    Logger(bool logsEnabled);

    Logger(const Logger &) = delete;

    void operator=(const Logger &) = delete;

    string getTimestamp(double clock);
};

#endif //EONSIMULATOR_LOGGER_H