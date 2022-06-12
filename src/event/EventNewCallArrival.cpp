#include "../../include/event/EventNewCallArrival.h"

EventNewCallArrival::EventNewCallArrival(uint64_t occurrenceTime, uint64_t srcLink, uint64_t dstLink,
                                         uint64_t numberOfFSUs, uint64_t serviceTime) {
    this->occurrenceTime = occurrenceTime;
    this->priority = 1;
    this->connection = new Connection(srcLink, dstLink, numberOfFSUs, serviceTime);
}

Event *EventNewCallArrival::execute(Network &network, uint64_t clock) {
    if (network.establishConnection(connection, clock)) {
        return new EventCallServiceTermination(occurrenceTime + connection->serviceTime, connection);
    } else {
        delete connection;
    }
    return nullptr;
}