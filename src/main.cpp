#include <future>
#include "../include/Simulator.h"
#include "../include/tools/SeedsProvider.h"

SingleSimulationResults runSingleSimulation(double a, vector<int32_t> seedsForSimulation, uint64_t simulationIndex) {
	Network network;
	network.buildNetworkStructure(false);

	int32_t x1 = seedsForSimulation[0];
	int32_t x2 = seedsForSimulation[1];
	int32_t x3 = seedsForSimulation[2];

	Generator generator(a, x1, x2, x3, network.getNumberOfInputLinks(), network.getNumberOfOutputLinks(), simulationIndex);
	Simulator simulator(network, generator);
	return simulator.run();
}

SimulationSetResults runSimulationSet(double a, vector<vector<int32_t>> seedsForSimulationSet) {
	vector<future<SingleSimulationResults>> simulations;
	vector<SingleSimulationResults> simulationResults;
	auto seedsForSimulation = seedsForSimulationSet.begin();

	for (uint64_t i = 0; i < SimulationSettings::instance().getRuns(); i++) {
		simulations.push_back(async(&runSingleSimulation, a, *seedsForSimulation++, i));
	}

	for (uint64_t i = 0; i < SimulationSettings::instance().getRuns(); i++) {
		simulationResults.push_back(simulations[i].get());
	}

	return SimulationSetResults(a, simulationResults);
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
	bool logsEnabled = args.count("-logs");
	Logger::initialize(logsEnabled);

	/// Initialize and validate SimulationSettings
	SimulationSettings::initialize(args);

	if (!SimulationSettings::instance().areValid()) {
		return -1;
	}

	/// Build and validate network node structure
	Network network;
	network.buildNetworkStructure(logsEnabled);

	if (!network.isValid()) {
		return -2;
	}

	/// Get seeds for random number generators
	SeedsProvider seedsProvider;
	uint64_t numberOfSimulationSets = SimulationSettings::instance().getAParameters().size();
	uint64_t numberOfSimulationsPerSet = SimulationSettings::instance().getRuns();
	uint64_t requiredNumberOfSeeds = numberOfSimulationSets * numberOfSimulationsPerSet * 3;

	if (requiredNumberOfSeeds > seedsProvider.getNumberOfAvailableSeeds()) {
		Logger::instance().log(Logger::ERROR, to_string(requiredNumberOfSeeds) + " seeds are required to perform required number of simulations, and the program can provide " + to_string(seedsProvider.getNumberOfAvailableSeeds()) + " seeds only");
		return -3;
	}

	vector<vector<vector<int32_t>>> seeds = seedsProvider.getSeeds(numberOfSimulationSets, numberOfSimulationsPerSet);
	auto seedsForSimulationSet = seeds.begin();

	/// Create simulators and run simulations
	vector<future<SimulationSetResults>> simulationSets;
	vector<SimulationSetResults> simulationSetResults;

	Logger::instance().log(Logger::STARTING_SIMULATIONS, "Starting simulations...");
	auto start = chrono::high_resolution_clock::now();

	for (double a: SimulationSettings::instance().getAParameters()) {
		simulationSets.push_back(async(&runSimulationSet, a, *seedsForSimulationSet++));
	}

	for (auto &simulationSet: simulationSets) {
		simulationSetResults.push_back(simulationSet.get());
	}

	auto finish = chrono::high_resolution_clock::now();
	auto duration = duration_cast<chrono::milliseconds>(finish - start);

	Logger::instance().log(Logger::SIMULATIONS_ENDED, "All simulations were done in " + to_string((double) duration.count() / 1000) + "s");

	/// Print results
	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		ss << "Erlang[";
		for (auto y: simulationSetResult.erlangTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Engset[";
		for (auto y: simulationSetResult.engsetTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Pascal[";
		for (auto y: simulationSetResult.pascalTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\n";
		cout << ss.str();
	}
	return 0;
}