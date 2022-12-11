#include "../../include/event/EventNewCallArrivalErlangClass.h"

EventNewCallArrivalErlangClass::EventNewCallArrivalErlangClass(double currentTime, uint64_t requiredNumberOfFSUs) {
    double serviceTime = Generator::instance().getRandomServiceTime();
    uint64_t sourceLink = Generator::instance().getRandomInputLink();
    uint64_t destinationLink = Generator::instance().getRandomOutputLink();

    this->requiredNumberOfFSUs = requiredNumberOfFSUs;
    this->occurrenceTime = currentTime + Generator::instance().getRandomOccurrenceTime(requiredNumberOfFSUs, serviceTime);
    this->connection = new Connection(sourceLink, destinationLink, requiredNumberOfFSUs, serviceTime);
}

void EventNewCallArrivalErlangClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) {
    TrafficClassStatistics &trafficClassStatistics = network.erlangTrafficClasses[requiredNumberOfFSUs];

    eventQueue.push(new EventNewCallArrivalErlangClass(occurrenceTime, requiredNumberOfFSUs));

    Logger::instance().log(occurrenceTime, Logger::CONNECTION_SETUP, "Setting up connection between input: " + to_string(network.inputLinks[connection->getSourceLink()]->getSourceNode()) + " and output " + to_string(network.outputLinks[connection->getDestinationLink()]->getDestinationNode()) + "...");

    switch (network.checkIfConnectionCanBeEstablished(connection)) {
        case Network::CONNECTION_CAN_BE_ESTABLISHED:
            network.reserveResources(connection);
            eventQueue.push(new EventCallServiceTermination(occurrenceTime + connection->getServiceTime(), connection));
            trafficClassStatistics.callsGenerated++;
            Logger::instance().log(occurrenceTime, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSU()) + "-" + to_string(connection->getFirstFSU() + connection->getRequiredNumberOfFSUs() - 1) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
            break;
        case Network::CONNECTION_REJECTED:
            Logger::instance().log(occurrenceTime, Logger::CONNECTION_REJECTED, "Connection rejected: free FSUs not found in source link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
            delete connection;
            break;
        case Network::INTERNAL_BLOCK:
            trafficClassStatistics.internalBlocksCount++;
            trafficClassStatistics.callsGenerated++;
            Logger::instance().log(occurrenceTime, Logger::INTERNAL_BLOCK, "Connection rejected: internal blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
            delete connection;
            break;
        case Network::EXTERNAL_BLOCK:
            trafficClassStatistics.externalBlocksCount++;
            trafficClassStatistics.callsGenerated++;
            Logger::instance().log(occurrenceTime, Logger::EXTERNAL_BLOCK, "Connection rejected: external blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
            delete connection;
            break;
    }
}