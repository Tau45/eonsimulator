#include "../include/Simulator.h"

Simulator::Simulator(SimulationSettings &settings) {
    this->clock = 0;
    this->settings = &settings;
    this->network = new Network(settings);
    this->generator = new Generator(settings, network->getNumberOfInputLinks(), network->getNumberOfOutputLinks());

    addErlangTrafficClasses();
    addEngsetTrafficClasses();
    addPascalTrafficClasses();
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        delete eventQueue.top()->connection;
        eventQueue.pop();
    }
}

void Simulator::run() {
    if (!network->everyOutputNodeIsAvailableFromEveryInputNode()) {
        cout << "error validating network structure\n";
    }

    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "");
    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "Starting simulation with parameters:");
    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "Calls to generate: " + to_string(settings->callsToGenerate));
    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "a: " + to_string(generator->a));
    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "");
    logger.log(settings->logsEnabled, clock, Logger::SIMULATION_START, "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < settings->callsToGenerate) {
        clock = eventQueue.top()->occurrenceTime;

        eventQueue.top()->execute(*network, eventQueue);
        eventQueue.pop();
    }

    logger.log(settings->logsEnabled, eventQueue.top()->occurrenceTime, Logger::SIMULATION_END, "The simulation has finished");

    printResults();
}

void Simulator::addErlangTrafficClasses() {
    for (uint64_t erlangTrafficClass: settings->erlangTrafficClasses) {
        network->erlangTrafficClasses[erlangTrafficClass] = TrafficClassStatistics();
        eventQueue.push(new EventNewCallArrivalErlangClass(clock, generator, erlangTrafficClass));
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