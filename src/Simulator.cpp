#include "../include/Simulator.h"

Simulator::Simulator(uint64_t callsTarget, int32_t x, double a) {
    clock = 0;
    network = new SingleLink();
    numberOfInputLinks = network->getNumberOfInputLinks();
    numberOfOutputLinks = network->getNumberOfOutputLinks();

    callsToGenerate = callsTarget;
    callsGenerated = 0;

    uint64_t V = 10;    // number of FSUs
    uint64_t M = 3;     // number of traffic classes
    uint64_t mi = 1;    // service time

    generator = new Generator(x, a, V, M, mi);

    eventQueue.push(new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks, 1));
    eventQueue.push(new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks, 2));
    eventQueue.push(new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks, 4));

    clock = eventQueue.top()->occurrenceTime;

    cout << "Starting simulation with parameters:" << endl;
    cout << "Calls to generate: " << callsTarget << endl;
    cout << "x: " << x << endl;
    cout << "a: " << a << endl;
    cout << endl;
}

void Simulator::run() {
    Logger::getInstance().log(clock, "", "The simulation has started...");
    while (callsGenerated < callsToGenerate) {
        vector<Event *> resultingEvents = eventQueue.top()->execute(*network, clock, callsGenerated);

        for (Event *event: resultingEvents) {
            eventQueue.push(event);
        }

        eventQueue.pop();
        clock = eventQueue.top()->occurrenceTime;
    }

    Logger::getInstance().log(clock, "", "The simulation has finished");

    cout << endl << "Calls of Erlang traffic generated: " << callsGenerated << endl;
    cout << "Blocks count: " << endl;
    cout << "Class 1: " << network->blocksCount[1] << " (result: " << (double) network->blocksCount[1]/callsGenerated << ")" << endl;
    cout << "Class 2: " << network->blocksCount[2] << " (result: " << (double) network->blocksCount[2]/callsGenerated << ")" << endl;
    cout << "Class 4: " << network->blocksCount[4] << " (result: " << (double) network->blocksCount[4]/callsGenerated << ")" << endl;
}

Simulator::~Simulator() {
    while (!eventQueue.empty()) {
        delete eventQueue.top()->connection;
        eventQueue.pop();
    }
}
