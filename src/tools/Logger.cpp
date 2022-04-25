#include "../../include/tools/Logger.h"

void Logger::log(uint64_t clock, string prefix, string message) {
    cout << getTimestamp(clock);

    /*if (prefix == "[USER_ARRIVAL]   ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x0E);
    }
    else if (prefix == "[BLOCK_RELEASE]  ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x09);
    }
    else if (prefix == "[USER_FINISHED]  ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x0A);
    }
    else if (prefix == "[USER_QUEUED]    ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x0D);
    }
    else if (prefix == "[BLOCK_ASSIGN]   ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x03);
    }
    else if (prefix == "[DATA_TRANSFER]  ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x0B);
    }
    else if (prefix == "[BITRATE_CHANGE] ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x0C);
    }
    else if (prefix == "[SIMULATION_END] ") {
        SetConsoleTextAttribute((CONSOLE_WINDOW), 0x07);
    }*/

    cout << prefix;

//    SetConsoleTextAttribute((CONSOLE_WINDOW), 0x07);

    cout << message << endl;
}

string Logger::getTimestamp(uint64_t clock) {
    uint64_t d = clock / 86400000;
    clock -= d * 86400000;
    uint64_t h = clock / 3600000;
    clock -= h * 3600000;
    uint64_t m = clock / 60000;
    clock -= m * 60000;
    uint64_t s = clock / 1000;
    clock -= s * 1000;
    uint64_t ms = clock;

    stringstream ss;
    ss << "["
       << setfill(' ')
       << setw(3) << d << "d "
       << setfill('0')
       << setw(2) << h << ":"
       << setw(2) << m << ":"
       << setw(2) << s << ":"
       << setw(3) << ms << "] ";
    return ss.str();
}