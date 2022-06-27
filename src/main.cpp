#include "../include/Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Error: not enough input arguments -> uint64_t callsToGenerate, double a";
        return 1;
    }

    uint64_t callsToGenerate = stoi(argv[1]);
    double a = atof(argv[2]);

    Simulator simulator(callsToGenerate, a);
    simulator.run();

    return 0;
}