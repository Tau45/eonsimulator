#include "../../include/event/EventNewCallArrivalEngsetClass.h"

EventNewCallArrivalEngsetClass::EventNewCallArrivalEngsetClass(double occurrenceTime, double gamma, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		gamma(gamma),
		serviceTime(serviceTime),
		trafficClassStatistics(trafficClassStatistics) {}

void EventNewCallArrivalEngsetClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) {
	Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_SETUP, "Engset traffic new call event execution: Setting up " + to_string(connection->getRequiredNumberOfFSUs()) + " FSU connection towards direction " + to_string(connection->getOutputDirectionIndex()) + "...");
	trafficClassStatistics.totalNumberOfCalls++;

	double callTerminationTime;
	double nextCallArrivalTime;

	switch (network.checkIfConnectionCanBeEstablished(connection, generator)) {
		case Network::CONNECTION_CAN_BE_ESTABLISHED:
			trafficClassStatistics.establishedConnections++;
			connection->reserveResources();

			callTerminationTime = occurrenceTime + generator.getRandomServiceTime(serviceTime);
			nextCallArrivalTime = callTerminationTime + generator.getRandomOccurrenceTime(gamma);

			eventQueue.push(new EventCallServiceTermination(callTerminationTime, connection));

			if (connection->getPathSize() == 1) {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else if (connection->getPathSize() == 2) {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			} else {
				Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfInternalLinks()) + "-" + to_string(connection->getFirstFSUOfInternalLinks() + connection->getRequiredNumberOfFSUs() - 1) + " in internal links, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link " + to_string(connection->getDestinationLink()->getSourceNode()) + "-" + to_string(connection->getDestinationLink()->getDestinationNode()) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			}
			break;
		case Network::CONNECTION_REJECTED:
			nextCallArrivalTime = occurrenceTime + generator.getRandomOccurrenceTime(gamma);
			trafficClassStatistics.totalNumberOfCalls--;
			Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_REJECTED, "Connection rejected: free FSUs not found in source link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::INTERNAL_BLOCK:
			nextCallArrivalTime = occurrenceTime + generator.getRandomOccurrenceTime(gamma);
			trafficClassStatistics.internalBlocksCount++;
			Logger::instance().log(occurrenceTime, simulationId, Logger::INTERNAL_BLOCK, "Connection rejected: internal blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
		case Network::EXTERNAL_BLOCK:
			nextCallArrivalTime = occurrenceTime + generator.getRandomOccurrenceTime(gamma);
			trafficClassStatistics.externalBlocksCount++;
			Logger::instance().log(occurrenceTime, simulationId, Logger::EXTERNAL_BLOCK, "Connection rejected: external blocking (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
			delete connection;
			break;
	}

	eventQueue.push(new EventNewCallArrivalEngsetClass(nextCallArrivalTime,
													   gamma,
													   serviceTime,
													   new Connection(generator.getRandomOutputDirectionIndex(network.getNumberOfOutputDirections()), connection->getRequiredNumberOfFSUs()),
													   trafficClassStatistics));
}