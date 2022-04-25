#include "../include/Simulator.h"

Simulator::Simulator() {
    network = new Benes4x4();
    callsToGenerate = 10;
    callsGenerated = 0;

    eventQueue.push(new EventNewCallArrival(0, 2, 0, 2, 5));
    eventQueue.push(new EventNewCallArrival(0, 3, 0, 1, 10));
    eventQueue.push(new EventNewCallArrival(0, 3, 1, 1, 10));
    eventQueue.push(new EventNewCallArrival(5, 2, 0, 1, 10));
    eventQueue.push(new EventNewCallArrival(5, 2, 0, 2, 10));
    eventQueue.push(new EventNewCallArrival(5, 2, 0, 1, 10));
    eventQueue.push(new EventNewCallArrival(5, 2, 0, 1, 10));

    clock = eventQueue.top()->occurrenceTime;
}

void Simulator::run() {
    while (callsGenerated < callsToGenerate) {
        while (eventQueue.top()->occurrenceTime == clock) {
            if (eventQueue.empty()) return; // to remove
            Event *resultingEvent = eventQueue.top()->execute(*network, clock);
            eventQueue.pop();

            if (resultingEvent != nullptr) {
                eventQueue.push(resultingEvent);
            }
        }
        clock = eventQueue.top()->occurrenceTime;
    }
}

uint64_t Simulator::getInternalBlocksCount() {
    return network->internalBlocksCount;
}

uint64_t Simulator::getExternalBlocksCount() {
    return network->externalBlocksCount;
}
