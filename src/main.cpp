#include <future>
#include "../include/Simulator.h"

SingleSimulationResults runSingleSimulation() {
    Network network;
    network.buildNetworkStructure();
    Generator generator(network.getNumberOfInputLinks(), network.getNumberOfOutputLinks());
    Simulator simulator(network, generator);
    return simulator.run();
}

SimulationSetResults runSimulationSet() {
    vector<future<SingleSimulationResults>> simulations;
    vector<SingleSimulationResults> simulationResults;

    for (int j = 0; j < SimulationSettings::instance().getRuns(); j++) {
        simulations.push_back(async(&runSingleSimulation));
    }

    for (int j = 0; j < SimulationSettings::instance().getRuns(); j++) {
        simulationResults.push_back(simulations[j].get());
    }

    return SimulationSetResults(SimulationSettings::instance().getA(), simulationResults);
}

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

    /// Create simulator and run simulation
    vector<future<SimulationSetResults>> simulationSets;
    vector<SimulationSetResults> simulationSetResults;

    for (int i = 0; i < 2; i++) {
        simulationSets.push_back(async(&runSimulationSet));
    }

    for (int i = 0; i < 2; i++) {
        simulationSetResults.push_back(simulationSets[i].get());
    }

    for (int i = 0; i < 2; i++) {
        stringstream ss;
        ss << simulationSetResults[i].a << "\t";
        ss << "Erlang[";
        for (auto y: simulationSetResults[i].erlangTrafficResults) {
            ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioStandardDeviation << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioStandardDeviation << "}";
        }
        ss << "]\t";

        ss << "Engset[";
        for (auto y: simulationSetResults[i].engsetTrafficResults) {
            ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioStandardDeviation << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioStandardDeviation << "}";
        }
        ss << "]\t";

        ss << "Pascal[";
        for (auto y: simulationSetResults[i].pascalTrafficResults) {
            ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioStandardDeviation << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioStandardDeviation << "}";
        }
        ss << "]\n";
        cout << ss.str();
    }
    return 0;
}