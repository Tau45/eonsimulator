#include "../include/Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {
    SimulationSettings settings(argc, argv);

    if (!settings.areValid()) {
        return -1;
    }

    Simulator simulator(settings);
    simulator.run();

    return 0;
}