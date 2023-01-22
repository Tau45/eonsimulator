#include "../include/Simulator.h"

Simulator::Simulator(Network &network, Generator &generator) {
    this->network = &network;
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

    return SingleSimulationResults(network->erlangTrafficClasses, network->engsetTrafficClasses, network->pascalTrafficClasses);
}

void Simulator::addErlangTrafficClasses() {
    for (uint64_t erlangTrafficClass: SimulationSettings::instance().getErlangTrafficClasses()) {
        network->erlangTrafficClasses[erlangTrafficClass] = TrafficClassStatistics();
        eventQueue.push(new EventNewCallArrivalErlangClass(0, erlangTrafficClass, *network, *generator));
    }
}

void Simulator::addEngsetTrafficClasses() {

}

void Simulator::addPascalTrafficClasses() {

}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        Event* event = eventQueue.top();
        eventQueue.pop();
        delete event;
    }
}
