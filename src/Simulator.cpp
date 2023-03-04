#include "../include/Simulator.h"

Simulator::Simulator(Network *network, Generator *generator) :
		network(network),
		generator(generator) {
	addErlangTrafficClasses();
	addEngsetTrafficClasses();
	addPascalTrafficClasses();
}

SingleSimulationResults Simulator::run() {
	Logger::instance().log(0, generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_START, "The simulation has started...");

	while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < SimulationSettings::instance().getCallsToGenerate()) {
		Event *event = eventQueue.top();
		event->execute(*network, eventQueue, *generator);
		eventQueue.pop();
		delete event;
	}

	Logger::instance().log(eventQueue.top()->getOccurrenceTime(), generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_END, "The simulation has finished");

	return SingleSimulationResults(network->erlangTrafficClassStatistics, network->engsetTrafficClassStatistics, network->pascalTrafficClassStatistics);
}

void Simulator::addErlangTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: SimulationSettings::instance().getErlangTrafficClasses()) {
		network->erlangTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs);
		Connection connection = Connection(generator->getRandomInputLink(), generator->getRandomOutputLink(), requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalErlangClass(occurrenceTime, connection, network->erlangTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

void Simulator::addEngsetTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: SimulationSettings::instance().getEngsetTrafficClasses()) {
		network->engsetTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs);
		Connection connection = Connection(generator->getRandomInputLink(), generator->getRandomOutputLink(), requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalEngsetClass(occurrenceTime, connection, network->engsetTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

void Simulator::addPascalTrafficClasses() {
	for (uint64_t requiredNumberOfFSUs: SimulationSettings::instance().getPascalTrafficClasses()) {
		network->pascalTrafficClassStatistics[requiredNumberOfFSUs] = TrafficClassStatistics();

		double occurrenceTime = generator->getRandomOccurrenceTime(requiredNumberOfFSUs);
		Connection connection = Connection(generator->getRandomInputLink(), generator->getRandomOutputLink(), requiredNumberOfFSUs, generator->getRandomServiceTime());
		eventQueue.push(new EventNewCallArrivalPascalClass(occurrenceTime, connection, network->pascalTrafficClassStatistics[requiredNumberOfFSUs]));
	}
}

Simulator::~Simulator() {
	while (!eventQueue.empty()) {
		Event *event = eventQueue.top();
		eventQueue.pop();
		delete event;
	}
}