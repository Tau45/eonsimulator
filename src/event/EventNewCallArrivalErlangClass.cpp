#include "../../include/event/EventNewCallArrivalErlangClass.h"

EventNewCallArrivalErlangClass::EventNewCallArrivalErlangClass(double occurrenceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		trafficClassStatistics(trafficClassStatistics) {}

void EventNewCallArrivalErlangClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::CONNECTION_SETUP, "Setting up connection from input: " + to_string(connection->getSourceLink()->getSourceNode()) + " to direction " + to_string(connection->getOutputDirection()->at(0)->getDestinationNode()) + "...");
	trafficClassStatistics.totalNumberOfCalls++;

	eventQueue.push(new EventNewCallArrivalErlangClass(occurrenceTime + generator.getRandomOccurrenceTime(connection->getRequiredNumberOfFSUs(), network.getNumberOfInputLinks()),
													   new Connection(network.getRandomInputLink(generator), network.getRandomOutputDirection(generator), connection->getRequiredNumberOfFSUs(), generator.getRandomServiceTime()),
													   trafficClassStatistics));

	switch (network.checkIfConnectionCanBeEstablished(connection, generator)) {
		case Network::CONNECTION_CAN_BE_ESTABLISHED:
			trafficClassStatistics.establishedConnections++;
			connection->reserveResources();
			eventQueue.push(new EventCallServiceTermination(occurrenceTime + connection->getServiceTime(), connection));

			if (connection->getPathSize() == 1) {
				Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else if (connection->getPathSize() == 2) {
				Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else {
				Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfInternalLinks()) + "-" + to_string(connection->getFirstFSUOfInternalLinks() + connection->getRequiredNumberOfFSUs() - 1) + " in internal links, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			}
			break;
		case Network::CONNECTION_REJECTED:
			trafficClassStatistics.totalNumberOfCalls--;
			Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::CONNECTION_REJECTED, "Connection rejected: free FSUs not found in source link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::INTERNAL_BLOCK:
			trafficClassStatistics.internalBlocksCount++;
			Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::INTERNAL_BLOCK, "Connection rejected: internal blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::EXTERNAL_BLOCK:
			trafficClassStatistics.externalBlocksCount++;
			Logger::instance().log(occurrenceTime, generator.getA(), generator.getSimulationIndex(), Logger::EXTERNAL_BLOCK, "Connection rejected: external blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
	}
}