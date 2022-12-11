#include <string>
#include "../include/Simulator.h"

int main(int argc, char *argv[]) {

    /// Read input arguments
    map<string, string> args;
    for (uint64_t i = 1; i < argc; i++) {
        string param = argv[i];
        string prefix = param.substr(0, param.find(':'));
        string inputValue = param.substr(param.find(':') + 1, param.length());
        args[prefix] = inputValue;
    }

    /// Initialize Logger
    Logger::initialize(args.count("-logs"));

    /// Initialize and validate SimulationSettings
    SimulationSettings::initialize(args);

    if (!SimulationSettings::instance().areValid()) {
        return -1;
    }

    /// Build and validate network node structure
    Network network;
    network.buildNetworkStructure();

    if (!network.isValid()) {
        return -2;
    }

    /// Initialize RNG
    Generator::initialize(network.getNumberOfInputLinks(), network.getNumberOfOutputLinks());

    /// Create simulator and run simulation
    Simulator simulator(network);
    simulator.run();

    return 0;
}