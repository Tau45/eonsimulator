#include "../include/Simulator.h"

Simulator::Simulator(string structureFileName, double a, uint64_t callsToGenerate) {
    clock = 0;
    network = new Network();

    network->createStructure(structureFileName);

    // napisz weryfikacje czy kazde wyjscie jest dostepne z kazdego wejscia
    // wyjmij tworzenie networka do maina

    this->callsToGenerate = callsToGenerate;

    uint64_t numberOfTrafficClasses = 3;
    uint64_t numberOfInputLinks = network->getNumberOfInputLinks();
    uint64_t numberOfOutputLinks = network->getNumberOfOutputLinks();

    generator = new Generator(a, linkCapacity, numberOfTrafficClasses, numberOfInputLinks, numberOfOutputLinks);

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
    Logger::getInstance().log(clock, Logger::CREATING_STRUCTURE, "");
    Logger::getInstance().log(clock, Logger::SIMULATION_START, "Starting simulation with parameters:");
    Logger::getInstance().log(clock, Logger::SIMULATION_START, "Calls to generate: " + to_string(callsToGenerate));
    Logger::getInstance().log(clock, Logger::SIMULATION_START, "a: " + to_string(generator->a));
    Logger::getInstance().log(clock, Logger::SIMULATION_START, "");
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
        cout << trafficClass.first << " FSUs class:"
             << " calls generated: " << trafficClass.second.callsGenerated
             << ", internal blocks: " << trafficClass.second.internalBlocksCount
             << " (" << (double) trafficClass.second.internalBlocksCount / trafficClass.second.callsGenerated << ")"
             << ", external blocks: " << trafficClass.second.externalBlocksCount
             << " (" << (double) trafficClass.second.externalBlocksCount / trafficClass.second.callsGenerated << ")"
             << endl;
    }
}