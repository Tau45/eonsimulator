#include "../include/Simulator.h"

Simulator::Simulator(uint64_t callsTarget, double a) {
    clock = 0;
    network = new SingleLink();
    numberOfInputLinks = network->getNumberOfInputLinks();
    numberOfOutputLinks = network->getNumberOfOutputLinks();

    callsToGenerate = callsTarget;

    uint64_t V = linkCapacity;    // number of FSUs
    uint64_t M = 3;     // number of traffic classes
    uint64_t mi = 1;    // service time

    generator = new Generator(a, V, M, mi);

    addErlangTrafficClass(1);
    addErlangTrafficClass(2);
    addErlangTrafficClass(4);
}

void Simulator::run() {
    cout << "##############################################################################" << endl << endl;
    cout << "Starting simulation with parameters:" << endl;
    cout << "Calls to generate: " << callsToGenerate << endl;
    cout << "a: " << generator->getA() << endl << endl;

    Logger::getInstance().log(clock, "", "The simulation has started...");

    while (network->getNumberOfGeneratedCallsOfTheLeastActiveClass() < callsToGenerate) {
        clock = eventQueue.top()->occurrenceTime;

        vector<Event *> resultingEvents = eventQueue.top()->execute(*network, clock);
        eventQueue.pop();

        for (Event *event: resultingEvents) {
            eventQueue.push(event);
        }
    }

    Logger::getInstance().log(clock, "", "The simulation has finished");

    printResults();
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        delete eventQueue.top()->connection;
        eventQueue.pop();
    }
}

void Simulator::addErlangTrafficClass(uint64_t requiredNumberOfFSUs) {
    network->erlangTrafficClasses[requiredNumberOfFSUs].callsGenerated = 0;
    eventQueue.push(new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks,
                                                       requiredNumberOfFSUs));
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