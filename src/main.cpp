#include "../include/Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Error: not enough input arguments -> uint64_t callsToGenerate, int32_t x, double a";
        return 1;
    }

    uint64_t callsToGenerate = stoi(argv[1]);
    int32_t x = stoi(argv[2]);
    double a = atof(argv[3]);

    Simulator simulator(callsToGenerate, x, a);
    simulator.run();

    return 0;
}