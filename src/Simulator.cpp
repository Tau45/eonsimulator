#include "../include/Simulator.h"

Simulator::Simulator(Network &network) {
    this->network = &network;
}

void Simulator::run() {
    SimulationSetResults x = runSimulationSet();

    for (auto y : x.erlangTrafficResults) {
        cout << x.a << " " << y.first << " " << y.second.avgInternalBlocksRatio << " " <<  y.second.internalBlocksRatioStandardDeviation << " " <<  y.second.avgExternalBlocksRatio << " " << y.second.externalBlocksRatioStandardDeviation << endl;
    }
    for (auto y : x.engsetTrafficResults) {
        cout << x.a << " " << y.first << " " << y.second.avgInternalBlocksRatio << " " <<  y.second.internalBlocksRatioStandardDeviation << " " <<  y.second.avgExternalBlocksRatio << " " << y.second.externalBlocksRatioStandardDeviation << endl;
    }
    for (auto y : x.pascalTrafficResults) {
        cout << x.a << " " << y.first << " " << y.second.avgInternalBlocksRatio << " " <<  y.second.internalBlocksRatioStandardDeviation << " " <<  y.second.avgExternalBlocksRatio << " " << y.second.externalBlocksRatioStandardDeviation << endl;
    }
}

SimulationSetResults Simulator::runSimulationSet() {
    vector<SingleSimulationResults> simulationResults;

    for (int run = 0; run < SimulationSettings::instance().getRuns(); run++) {
        simulationResults.push_back(runSingleSimulation());
    }

    return SimulationSetResults(SimulationSettings::instance().getA(), simulationResults);
}

SingleSimulationResults Simulator::runSingleSimulation() {
    reset();

    Logger::instance().log(0, Logger::SIMULATION_START, "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < SimulationSettings::instance().getCallsToGenerate()) {
        Event* event = eventQueue.top();
        event->execute(*network, eventQueue);
        eventQueue.pop();
        delete event;
    }

    Logger::instance().log(eventQueue.top()->getOccurrenceTime(), Logger::SIMULATION_END, "The simulation has finished");

    return SingleSimulationResults(network->erlangTrafficClasses, network->engsetTrafficClasses, network->pascalTrafficClasses);
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

void Simulator::reset() {
    while (!eventQueue.empty()) {
        Event* event = eventQueue.top();
        eventQueue.pop();
        delete event;
    }

    network->closeAllConnections();

    addErlangTrafficClasses();
    addEngsetTrafficClasses();
    addPascalTrafficClasses();
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        Event* event = eventQueue.top();
        eventQueue.pop();
        delete event;
    }
}
