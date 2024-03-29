#include "../../include/event/EventNewCallArrivalPascalClass.h"

EventNewCallArrivalPascalClass::EventNewCallArrivalPascalClass(double occurrenceTime, double beta, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics, bool isCopy) :
		Event(occurrenceTime, connection),
		beta(beta),
		serviceTime(serviceTime),
		trafficClassStatistics(trafficClassStatistics),
		isCopy(isCopy) {}

void EventNewCallArrivalPascalClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) {
	Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_SETUP, "Pascal traffic new call event execution: Setting up " + to_string(connection->getRequiredNumberOfFSUs()) + " FSU connection towards direction " + to_string(connection->getOutputDirectionIndex()) + "...");
	trafficClassStatistics.totalNumberOfCalls++;

	if (!isCopy) {
		eventQueue.push(new EventNewCallArrivalPascalClass(occurrenceTime + generator.getRandomOccurrenceTime(beta),
														   beta,
														   serviceTime,
														   new Connection(generator.getRandomOutputDirectionIndex(network.getNumberOfOutputDirections()), connection->getRequiredNumberOfFSUs()),
														   trafficClassStatistics,
														   false));
	}

	switch (network.checkIfConnectionCanBeEstablished(connection, generator)) {
		case Network::CONNECTION_CAN_BE_ESTABLISHED:
			trafficClassStatistics.establishedConnections++;
			connection->reserveResources();
			eventQueue.push(new EventCallServiceTermination(occurrenceTime + generator.getRandomServiceTime(serviceTime), connection));

			if (!isCopy) {
				eventQueue.push(new EventNewCallArrivalPascalClass(occurrenceTime + generator.getRandomOccurrenceTime(beta),
																   beta,
																   serviceTime,
																   new Connection(generator.getRandomOutputDirectionIndex(network.getNumberOfOutputDirections()), connection->getRequiredNumberOfFSUs()),
																   trafficClassStatistics,
																   true));
			}

			if (connection->getPathSize() == 1) {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else if (connection->getPathSize() == 2) {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfInternalLinks()) + "-" + to_string(connection->getFirstFSUOfInternalLinks() + connection->getRequiredNumberOfFSUs() - 1) + " in internal links, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			}
			break;
		case Network::CONNECTION_REJECTED:
			trafficClassStatistics.totalNumberOfCalls--;
			Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_REJECTED, "Connection rejected: free FSUs not found in source link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::INTERNAL_BLOCK:
			trafficClassStatistics.internalBlocksCount++;
			Logger::instance().log(occurrenceTime, simulationId, Logger::INTERNAL_BLOCK, "Connection rejected: internal blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::EXTERNAL_BLOCK:
			trafficClassStatistics.externalBlocksCount++;
			Logger::instance().log(occurrenceTime, simulationId, Logger::EXTERNAL_BLOCK, "Connection rejected: external blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
	}
}