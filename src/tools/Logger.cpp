#include "../../include/tools/Logger.h"

Logger::Logger(bool logsEnabled) {
    this->logsEnabled = logsEnabled;
}

Logger &Logger::instance(function<Logger()> *init) {
    static Logger s{(*init)()};
    return s;
}

void Logger::initialize(bool logsEnabled) {
    function<Logger()> init = [logsEnabled]() { return Logger(logsEnabled); };
    instance(&init);
}

void Logger::log(double clock, LOG_MESSAGE_TYPE prefix, const string &message) {
    if (logsEnabled || prefix == ERROR || prefix == WARN) {
        cout << getTimestamp(clock);
        cout << logMessageTypeMap.at(prefix);
        cout << message << endl;
    }
}

string Logger::getTimestamp(double clock) {
    uint64_t d = clock / 86400;
    clock -= d * 86400;
    uint64_t h = clock / 3600;
    clock -= h * 3600;
    uint64_t m = clock / 60;
    clock -= m * 60;
    uint64_t s = clock;
    clock -= s;
    uint64_t ms = clock * 1000;

    stringstream ss;
    ss << "["
       << setfill(' ')
       << setw(3) << d << "d "
       << setfill('0')
       << setw(2) << h << ":"
       << setw(2) << m << ":"
       << setw(2) << s << ":"
       //           << setw(6) << ms << "] ";
       << setw(3) << ms << "] ";
    return ss.str();
}