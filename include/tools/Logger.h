#pragma once
#ifndef EONSIMULATOR_LOGGER_H
#define EONSIMULATOR_LOGGER_H

#include <iostream>
#include <sstream>
#include <iomanip>

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

    void log(uint64_t, string, string);

    string getTimestamp(uint64_t);
};

#endif //EONSIMULATOR_LOGGER_H