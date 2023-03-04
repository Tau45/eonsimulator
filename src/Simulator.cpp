#include "../include/Simulator.h"

Simulator::Simulator(Generator &generator) {
    this->network = new Network();
    this->generator = &generator;

    addErlangTrafficClasses();
    addEngsetTrafficClasses();
    addPascalTrafficClasses();
}

SingleSimulationResults Simulator::run() {
    Logger::instance().log(0, generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_START, "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < SimulationSettings::instance().getCallsToGenerate()) {
        Event* event = eventQueue.top();
        event->execute(*network, eventQueue, *generator);
        eventQueue.pop();
        delete event;
    }

    Logger::instance().log(eventQueue.top()->getOccurrenceTime(), generator->getA(), generator->getSimulationIndex(), Logger::SIMULATION_END, "The simulation has finished");

    return SingleSimulationResults(network->erlangTrafficClassStatistics, network->engsetTrafficClassStatistics, network->pascalTrafficClassStatistics);
}

void Simulator::addErlangTrafficClasses() {
    for (uint64_t erlangTrafficClass: SimulationSettings::instance().getErlangTrafficClasses()) {
        network->erlangTrafficClassStatistics[erlangTrafficClass] = TrafficClassStatistics();
        eventQueue.push(new EventNewCallArrivalErlangClass(0, erlangTrafficClass, *network, *generator, network->erlangTrafficClassStatistics[erlangTrafficClass]));
    }
}

void Simulator::addEngsetTrafficClasses() {
	for (uint64_t engsetTrafficClass: SimulationSettings::instance().getEngsetTrafficClasses()) {
		network->engsetTrafficClassStatistics[engsetTrafficClass] = TrafficClassStatistics();
		eventQueue.push(new EventNewCallArrivalEngsetClass());
	}
}

void Simulator::addPascalTrafficClasses() {
	for (uint64_t pascalTrafficClass: SimulationSettings::instance().getPascalTrafficClasses()) {
		network->pascalTrafficClassStatistics[pascalTrafficClass] = TrafficClassStatistics();
		eventQueue.push(new EventNewCallArrivalPascalClass());
	}
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        Event* event = eventQueue.top();
        eventQueue.pop();
        delete event;
    }
}