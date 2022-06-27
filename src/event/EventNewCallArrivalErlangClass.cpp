#include "../../include/event/EventNewCallArrivalErlangClass.h"

EventNewCallArrivalErlangClass::EventNewCallArrivalErlangClass(Generator *generator, uint64_t clock,
                                                               uint64_t numberOfInputLinks,
                                                               uint64_t numberOfOutputLinks,
                                                               uint64_t requiredNumberOfFSUs) {
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

vector<Event *> EventNewCallArrivalErlangClass::execute(Network &network, uint64_t clock) {
    vector<Event *> resultingEvents;

    if (network.establishConnection(connection, network.erlangTrafficClasses[requiredNumberOfFSUs])) {
        resultingEvents.push_back(
                new EventCallServiceTermination(occurrenceTime + connection->serviceTime, connection));
    } else {
        delete connection;
    }

    resultingEvents.push_back(
            new EventNewCallArrivalErlangClass(generator, clock, numberOfInputLinks, numberOfOutputLinks,
                                               requiredNumberOfFSUs));

    return resultingEvents;
}