#include "../include/Simulator.h"

Simulator::Simulator(Network &network) {
    this->network = &network;

    addErlangTrafficClasses();
    addEngsetTrafficClasses();
    addPascalTrafficClasses();
}

void Simulator::run() {
    Logger::instance().log(0, Logger::SIMULATION_START, "Starting simulation with parameters:");
    Logger::instance().log(0, Logger::SIMULATION_START, "Calls to generate: " + to_string(SimulationSettings::instance().getCallsToGenerate()));
    Logger::instance().log(0, Logger::SIMULATION_START, "a: " + to_string(SimulationSettings::instance().getA()));
    Logger::instance().log(0, Logger::SIMULATION_START, "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < SimulationSettings::instance().getCallsToGenerate()) {
        eventQueue.top()->execute(*network, eventQueue);
        eventQueue.pop();
    }

    Logger::instance().log(eventQueue.top()->getOccurrenceTime(), Logger::SIMULATION_END, "The simulation has finished");

    printResults();
}

void Simulator::addErlangTrafficClasses() {
    for (uint64_t erlangTrafficClass: SimulationSettings::instance().getErlangTrafficClasses()) {
        network->erlangTrafficClasses[erlangTrafficClass] = TrafficClassStatistics();
        eventQueue.push(new EventNewCallArrivalErlangClass(0, erlangTrafficClass));
    }
}

void Simulator::addEngsetTrafficClasses() {

}

void Simulator::addPascalTrafficClasses() {

}

void Simulator::printResults() {
    cout << "Erlang traffic:" << endl;

    for (auto const &trafficClass: network->erlangTrafficClasses) {
        cout << trafficClass.first << " FSUs class:"
             << " calls generated: " << trafficClass.second.callsGenerated
             << ", internal blocks: " << trafficClass.second.internalBlocksCount
             << " (" << (double) trafficClass.second.internalBlocksCount / trafficClass.second.callsGenerated << ")"
             << ", external blocks: " << trafficClass.second.externalBlocksCount
             << " (" << (double) trafficClass.second.externalBlocksCount / trafficClass.second.callsGenerated << ")"
             << endl;
    }
}