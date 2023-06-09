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
		double lambda = getLambda(requiredNumberOfFSUs, network->getNumberOfInputLinks());

		eventQueue.push(new EventNewCallArrivalErlangClass(generator->getRandomOccurrenceTime(lambda),
														   lambda,
														   new Connection(generator->getRandomOutputDirectionIndex(network->getNumberOfOutputDirections()), requiredNumberOfFSUs),
														   network->erlangTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

void Simulator::addEngsetTrafficClasses() {}

void Simulator::addPascalTrafficClasses() {}

double Simulator::getLambda(uint32_t requiredNumberOfFSUs, uint64_t numberOfInputLinks) {
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	uint64_t numberOfTrafficClasses = GlobalSettings::instance().getNumberOfTrafficClasses();
	double serviceTime = GlobalSettings::instance().getServiceTime();

	return (generator->getA() * numberOfInputLinks * linkCapacity) / (numberOfTrafficClasses * serviceTime * requiredNumberOfFSUs);
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