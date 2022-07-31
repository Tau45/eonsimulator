#include "../include/Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Error: not enough input arguments -> string structureFileName (comma separated .csv file), double a, uint64_t callsToGenerate";
        return 1;
    }

    string structureFileName = argv[1];
    double a = atof(argv[2]);
    uint64_t callsToGenerate = stoi(argv[3]);

    Simulator simulator(structureFileName, a, callsToGenerate);
    simulator.run();

    return 0;
}