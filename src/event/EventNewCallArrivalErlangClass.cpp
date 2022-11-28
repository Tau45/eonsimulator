#include "../../include/event/EventNewCallArrivalErlangClass.h"

EventNewCallArrivalErlangClass::EventNewCallArrivalErlangClass(double currentTime, Generator *generator, uint64_t requiredNumberOfFSUs) {
    double serviceTime = generator->getServiceTime();
    uint64_t srcLink = generator->getRandomInputLink();
    uint64_t dstLink = generator->getRandomOutputLink();

    this->generator = generator;
    this->requiredNumberOfFSUs = requiredNumberOfFSUs;
    this->occurrenceTime = currentTime + generator->getOccurrenceTime(requiredNumberOfFSUs, serviceTime);
    this->connection = new Connection(srcLink, dstLink, requiredNumberOfFSUs, serviceTime);
}

void EventNewCallArrivalErlangClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) {
    TrafficClassStatistics &trafficClassStatistics = network.erlangTrafficClasses[requiredNumberOfFSUs];

    eventQueue.push(new EventNewCallArrivalErlangClass(occurrenceTime, generator, requiredNumberOfFSUs));

    switch (network.establishConnection(occurrenceTime, connection)) {
        case Network::CONNECTION_ESTABLISHED:
            network.reserveResources(connection);
            eventQueue.push(new EventCallServiceTermination(occurrenceTime + connection->serviceTime, connection));
            trafficClassStatistics.callsGenerated++;
            break;
        case Network::CONNECTION_REJECTED:
            delete connection;
            break;
        case Network::INTERNAL_BLOCK:
            trafficClassStatistics.internalBlocksCount++;
            trafficClassStatistics.callsGenerated++;
            delete connection;
            break;
        case Network::EXTERNAL_BLOCK:
            trafficClassStatistics.externalBlocksCount++;
            trafficClassStatistics.callsGenerated++;
            delete connection;
            break;
    }
}