#include "../../include/event/EventNewCallArrival.h"

EventNewCallArrival::EventNewCallArrival(uint64_t srcLink, uint64_t dstLink, uint64_t connectionId,
                                         uint64_t demandedFSUs, uint64_t serviceTime) {
    this->srcLink = srcLink;
    this->dstLink = dstLink;
    this->connectionId = connectionId;
    this->numberOfFSUs = numberOfFSUs;
    this->serviceTime = serviceTime;
}

void EventNewCallArrival::execute(Network &network) {
    Connection *connection = new Connection(connectionId, srcLink, dstLink, numberOfFSUs);

    network.tryToEstablishConnection(connection);
}