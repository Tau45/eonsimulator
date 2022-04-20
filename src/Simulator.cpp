#include "../include/Simulator.h"
#include "../include/event/EventNewCallArrival.h"


Simulator::Simulator() {
    network = new Benes4x4();
    callsToGenerate = 10;
    callsGenerated = 0;
    internalBlockingCount = 0;
    externalBlockingCount = 0;

    connectionId = 0;
    eventQueue.push(new EventNewCallArrival(2, 0, connectionId++, 2, 10));

    clock = eventQueue.top()->occurrenceTime;
}

void Simulator::run() {
    while (callsGenerated < callsToGenerate) {
        while (eventQueue.top()->occurrenceTime == clock) {
            eventQueue.top()->execute(*network);
            eventQueue.pop();
        }
        clock = eventQueue.top()->occurrenceTime;
    }
}
