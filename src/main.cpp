#include <future>
#include "../include/Simulator.h"
#include "../include/tools/SeedsProvider.h"

SingleSimulationResults runSingleSimulation(double a, vector<int32_t> seedsForSimulation, uint64_t simulationIndex) {
	int32_t x1 = seedsForSimulation[0];
	int32_t x2 = seedsForSimulation[1];
	int32_t x3 = seedsForSimulation[2];

	Network network;
	Generator generator(a, x1, x2, x3, simulationIndex);
	Simulator simulator(&network, &generator);
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
		return -10;
	}

	/// Build and validate network node structure
	Network network;
	network.printStructureDetails();

	if (!network.isValid()) {
		return -11;
	}

	SimulationSettings::instance().setNumberOfInputLinks(network.getNumberOfInputLinks());
	SimulationSettings::instance().setNumberOfOutputLinks(network.getNumberOfOutputLinks());

	/// Get seeds for random number generators
	SeedsProvider seedsProvider;
	uint64_t requiredNumberOfSeeds = SimulationSettings::instance().getAParameters().size() * SimulationSettings::instance().getRuns() * 3;

	if (requiredNumberOfSeeds > seedsProvider.getNumberOfAvailableSeeds()) {
		Logger::instance().log(Logger::ERROR, to_string(requiredNumberOfSeeds) + " seeds are required to perform required number of simulations, and the program can provide " + to_string(seedsProvider.getNumberOfAvailableSeeds()) + " seeds only");
		return -12;
	}

	vector<vector<vector<int32_t>>> seeds = seedsProvider.getSeeds();
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

	// TODO: Save results in a file

	/// Print results
	/// Results for internal blocks
	cout <<"\nInternal blocks:\n";
	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		ss << "Erlang[";
		for (auto y: simulationSetResult.erlangTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Engset[";
		for (auto y: simulationSetResult.engsetTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Pascal[";
		for (auto y: simulationSetResult.pascalTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\n";
		cout << ss.str();
	}

	/// Results for external blocks
	cout <<"\nExternal blocks:\n";
	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		ss << "Erlang[";
		for (auto y: simulationSetResult.erlangTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Engset[";
		for (auto y: simulationSetResult.engsetTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Pascal[";
		for (auto y: simulationSetResult.pascalTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "}";
		}
		ss << "]\n";
		cout << ss.str();
	}

	/// Results for total blocks
	cout <<"\nTotal blocks:\n";
	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		ss << "Erlang[";
		for (auto y: simulationSetResult.erlangTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgTotalBlockRatio << "\t" << y.second.totalBlockConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Engset[";
		for (auto y: simulationSetResult.engsetTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgTotalBlockRatio << "\t" << y.second.totalBlockConfidenceInterval << "}";
		}
		ss << "]\t";

		ss << "Pascal[";
		for (auto y: simulationSetResult.pascalTrafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgTotalBlockRatio << "\t" << y.second.totalBlockConfidenceInterval << "}";
		}
		ss << "]\n";
		cout << ss.str();
	}
	return 0;
}