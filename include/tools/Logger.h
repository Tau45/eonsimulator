#pragma once
#ifndef EONSIMULATOR_LOGGER_H
#define EONSIMULATOR_LOGGER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include "../constants/Constants.h"

using namespace std;

class Logger {
private:
    Logger() = default;

public:
    static Logger &getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(Logger const &) = delete;

    void operator=(Logger const &) = delete;

    enum LOG_MESSAGE_TYPE {
        CONNECTION_REJECTED,
        INTERNAL_BLOCK,
        EXTERNAL_BLOCK,
        CONNECTION_ESTABLISHED,
        CONNECTION_CLOSED,
        CONNECTION_SETUP,
        SIMULATION_START,
        SIMULATION_END
    };

    map<LOG_MESSAGE_TYPE, string> logMessageTypeMap = {
            {CONNECTION_REJECTED,    "[CONNECTION_REJECTED   ] "},
            {INTERNAL_BLOCK,         "[INTERNAL_BLOCK        ] "},
            {EXTERNAL_BLOCK,         "[EXTERNAL_BLOCK        ] "},
            {CONNECTION_ESTABLISHED, "[CONNECTION_ESTABLISHED] "},
            {CONNECTION_CLOSED,      "[CONNECTION_CLOSED     ] "},
            {CONNECTION_SETUP,       "[CONNECTION_SETUP      ] "},
            {SIMULATION_START,       "[SIMULATION_START      ] "},
            {SIMULATION_END,         "[SIMULATION_END        ] "}
    };

    void log(double clock, LOG_MESSAGE_TYPE prefix, const string &message);

    string getTimestamp(double clock);
};

#endif //EONSIMULATOR_LOGGER_H