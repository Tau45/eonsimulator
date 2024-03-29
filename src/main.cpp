#include <future>
#include "../include/Simulator.h"
#include "../include/tools/SeedsProvider.h"

SingleSimulationResults runSingleSimulation(double a, uint64_t simulationIndex, vector<int32_t> seedsForSimulation) {
	Simulator simulator(a, simulationIndex, seedsForSimulation);
	return simulator.run();
}

SimulationSetResults runSimulationSet(double a, vector<vector<int32_t>> seedsForSimulationSet) {
	vector<future<SingleSimulationResults>> simulations;
	vector<SingleSimulationResults> simulationResults;
	auto seedsForSimulation = seedsForSimulationSet.begin();

	for (uint64_t i = 0; i < GlobalSettings::instance().getRuns(); i++) {
		simulations.push_back(async(&runSingleSimulation, a, i, *seedsForSimulation++));
	}

	for (uint64_t i = 0; i < GlobalSettings::instance().getRuns(); i++) {
		simulationResults.push_back(simulations[i].get());
	}

	return SimulationSetResults(a, simulationResults);
}

void saveResults(vector<SimulationSetResults> &simulationSetResults) {
	Logger::instance().log(Logger::SIMULATIONS_ENDED, "Saving simulation results...");

	string structureFileName = GlobalSettings::instance().getStructureFileName();
	string structureName = structureFileName.substr(0, structureFileName.length() - 4);

	ofstream internalBlocksResultFile(structureName + "_internal.xls");
	ofstream externalBlocksResultFile(structureName + "_external.xls");
	ofstream totalBlocksResultFile(structureName + "_total.xls");

	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		for (auto y: simulationSetResult.trafficResults) {
			ss << y.second.avgInternalBlocksRatio << "\t" << y.second.internalBlocksRatioConfidenceInterval << "\t";
		}
		ss << endl;
		internalBlocksResultFile << ss.str();
	}

	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		for (auto y: simulationSetResult.trafficResults) {
			ss << y.second.avgExternalBlocksRatio << "\t" << y.second.externalBlocksRatioConfidenceInterval << "\t";
		}
		ss << endl;
		externalBlocksResultFile << ss.str();
	}

	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		for (auto y: simulationSetResult.trafficResults) {
			ss << y.second.avgTotalBlockRatio << "\t" << y.second.totalBlockConfidenceInterval << "\t";
		}
		ss << endl;
		totalBlocksResultFile << ss.str();
	}

	internalBlocksResultFile.close();
	externalBlocksResultFile.close();
	totalBlocksResultFile.close();

	Logger::instance().log(Logger::SIMULATIONS_ENDED, "Saving simulation results has been completed");
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

	/// Initialize and validate GlobalSettings
	GlobalSettings::initialize(args);

	if (!GlobalSettings::instance().areValid()) {
		return -10;
	}

	/// Build and print network node structure
	Network network;
	network.printNetworkStructure();

	/// Get seeds for random number generators
	SeedsProvider seedsProvider;
	uint64_t requiredNumberOfSeeds = GlobalSettings::instance().getAParameters().size() * GlobalSettings::instance().getRuns() * 3;

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

	for (double a: GlobalSettings::instance().getAParameters()) {
		simulationSets.push_back(async(&runSimulationSet, a, *seedsForSimulationSet++));
	}

	for (auto &simulationSet: simulationSets) {
		simulationSetResults.push_back(simulationSet.get());
	}

	auto finish = chrono::high_resolution_clock::now();
	auto duration = duration_cast<chrono::milliseconds>(finish - start);

	Logger::instance().log(Logger::SIMULATIONS_ENDED, "All simulations were done in " + to_string((double) duration.count() / 1000) + "s");

	saveResults(simulationSetResults);

	/// Print results
	/// Results for internal blocks
	cout <<"\nInternal blocks:\n";
	for (auto &simulationSetResult: simulationSetResults) {
		stringstream ss;
		ss << simulationSetResult.a << "\t";
		ss << "[";
		for (auto y: simulationSetResult.trafficResults) {
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
		ss << "[";
		for (auto y: simulationSetResult.trafficResults) {
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
		ss << "[";
		for (auto y: simulationSetResult.trafficResults) {
			ss << "{" << y.first << " FSUs\t" << y.second.avgTotalBlockRatio << "\t" << y.second.totalBlockConfidenceInterval << "}";
		}
		ss << "]\n";
		cout << ss.str();
	}
	return 0;
}