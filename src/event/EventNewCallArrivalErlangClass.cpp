#include "../../include/event/EventNewCallArrivalErlangClass.h"

EventNewCallArrivalErlangClass::EventNewCallArrivalErlangClass(Generator *generator, uint64_t clock, uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks, uint64_t requiredNumberOfFSUs) {
    this->generator = generator;
    this->occurrenceTime = generator->getOccurrenceTime(clock, requiredNumberOfFSUs);
    this->priority = 1;
    this->numberOfInputLinks = numberOfInputLinks;
    this->numberOfOutputLinks = numberOfOutputLinks;
    this->requiredNumberOfFSUs = requiredNumberOfFSUs;

    uint64_t srcLink = generator->getRandomLink(numberOfInputLinks);
    uint64_t dstLink = generator->getRandomLink(numberOfOutputLinks);
    uint64_t serviceTime = generator->getServiceTime();

    this->connection = new Connection(srcLink, dstLink, requiredNumberOfFSUs, serviceTime);
}

void EventNewCallArrivalErlangClass::execute(Network &network, uint64_t clock, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) {
    TrafficClassStatistics &trafficClassStatistics = network.erlangTrafficClasses[requiredNumberOfFSUs];
    Network::ESTABLISH_CONNECTION_RESULT result = network.tryToEstablishConnection(connection);

    switch (result) {
        case Network::CONNECTION_ESTABLISHED:
            eventQueue.push(new EventCallServiceTermination(occurrenceTime + connection->serviceTime, connection));
            trafficClassStatistics.callsGenerated++;
            break;
        case Network::FREE_FSUS_NOT_FOUND_IN_SOURCE_LINK:
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

    eventQueue.push(new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks, requiredNumberOfFSUs));
}