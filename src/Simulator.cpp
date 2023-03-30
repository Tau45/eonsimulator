#include "../include/Simulator.h"

Simulator::Simulator(double a, vector<int32_t> &seedsForSimulation, uint64_t simulationIndex) {
	int32_t x1 = seedsForSimulation[0];
	int32_t x2 = seedsForSimulation[1];
	int32_t x3 = seedsForSimulation[2];

	generator = new Generator(a, x1, x2, x3, simulationIndex);
	network = new Network();
	addErlangTrafficClasses();
	addEngsetTrafficClasses();
	addPascalTrafficClasses();
}

SingleSimulationResults Simulator::run() {
	Logger::instance().log(0, generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_START, "The simulation has started...");
	auto start = chrono::high_resolution_clock::now();

	while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < GlobalSettings::instance().getCallsToGenerate()) {
		Event *event = eventQueue.top();
		eventQueue.pop();
		event->execute(*network, eventQueue, *generator);

		delete event;
	}

	auto finish = chrono::high_resolution_clock::now();
	auto duration = duration_cast<chrono::milliseconds>(finish - start);
	Logger::instance().log(eventQueue.top()->getOccurrenceTime(), generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_END, "The simulation has finished in " + to_string((double) duration.count() / 1000) + "s");

	return SingleSimulationResults(network->erlangTrafficClassStatistics, network->engsetTrafficClassStatistics, network->pascalTrafficClassStatistics);
}

void Simulator::addErlangTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: GlobalSettings::instance().getErlangTrafficClasses()) {
		network->erlangTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs, network->getNumberOfInputLinks());
		vector<Link *> outputDirection = network->getRandomOutputDirection(*generator);
		Connection connection = Connection(network->getRandomInputLink(*generator, requiredNumberOfFSUs), outputDirection, requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalErlangClass(occurrenceTime, connection, network->erlangTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

void Simulator::addEngsetTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: GlobalSettings::instance().getEngsetTrafficClasses()) {
		network->engsetTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs, network->getNumberOfInputLinks());
		vector<Link *> outputDirection = network->getRandomOutputDirection(*generator);
		Connection connection = Connection(network->getRandomInputLink(*generator, requiredNumberOfFSUs), outputDirection, requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalEngsetClass(occurrenceTime, connection, network->engsetTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

void Simulator::addPascalTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: GlobalSettings::instance().getPascalTrafficClasses()) {
		network->pascalTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs, network->getNumberOfInputLinks());
		vector<Link *> outputDirection = network->getRandomOutputDirection(*generator);
		Connection connection = Connection(network->getRandomInputLink(*generator, requiredNumberOfFSUs), outputDirection, requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalPascalClass(occurrenceTime, connection, network->pascalTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

Simulator::~Simulator() {
	while (!eventQueue.empty()) {
		Event *event = eventQueue.top();
		eventQueue.pop();
		delete event;
	}
	delete generator;
	delete network;
}