#include "../include/Simulator.h"

Simulator::Simulator(uint64_t callsTarget, double a) {
    clock = 0;
    network = new SingleLink();
    callsToGenerate = callsTarget;

    uint64_t M = 3; // number of traffic classes
    uint64_t numberOfInputLinks = network->getNumberOfInputLinks();
    uint64_t numberOfOutputLinks = network->getNumberOfOutputLinks();

    generator = new Generator(a, linkCapacity, M, numberOfInputLinks, numberOfOutputLinks);

    addErlangTrafficClass(1);
    addErlangTrafficClass(2);
    addErlangTrafficClass(4);
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        delete eventQueue.top()->connection;
        eventQueue.pop();
    }
}

void Simulator::run() {
    cout << "##############################################################################" << endl << endl;
    cout << "Starting simulation with parameters:" << endl;
    cout << "Calls to generate: " << callsToGenerate << endl;
    cout << "a: " << generator->a << endl << endl;

    Logger::getInstance().log(clock, Logger::SIMULATION_START, "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < callsToGenerate) {
        clock = eventQueue.top()->occurrenceTime;

        eventQueue.top()->execute(*network, eventQueue);
        eventQueue.pop();
    }

    Logger::getInstance().log(eventQueue.top()->occurrenceTime, Logger::SIMULATION_END, "The simulation has finished");

    printResults();
}

void Simulator::addErlangTrafficClass(uint64_t requiredNumberOfFSUs) {
    network->erlangTrafficClasses[requiredNumberOfFSUs] = TrafficClassStatistics();
    eventQueue.push(new EventNewCallArrivalErlangClass(clock, generator, requiredNumberOfFSUs));
}

void Simulator::printResults() {
    cout << "Erlang traffic:" << endl;

    for (auto const &trafficClass: network->erlangTrafficClasses) {
        cout << "Traffic class requiring " << trafficClass.first << " FSUs:"
             << " calls generated: " << trafficClass.second.callsGenerated
             << ", internal blocks: " << trafficClass.second.internalBlocksCount
             << " (" << (double) trafficClass.second.internalBlocksCount / trafficClass.second.callsGenerated << ")"
             << ", external blocks: " << trafficClass.second.externalBlocksCount
             << " (" << (double) trafficClass.second.externalBlocksCount / trafficClass.second.callsGenerated << ")"
             << endl;
    }
}