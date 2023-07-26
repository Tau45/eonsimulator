#include "../../include/event/EventCallServiceTermination.h"

EventCallServiceTermination::EventCallServiceTermination(double occurrenceTime, Connection *connection) :
		Event(occurrenceTime, connection) {}

void EventCallServiceTermination::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) {
	connection->close();

	if (connection->getPathSize() == 1) {
		Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_CLOSED, "Connection between input: " + to_string(connection->getSourceLink()->getSourceNode()) + " and output " + to_string(connection->getDestinationLink()->getDestinationNode()) + " closed: Freeing " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
	} else if (connection->getPathSize() == 2) {
		Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_CLOSED, "Connection between input: " + to_string(connection->getSourceLink()->getSourceNode()) + " and output " + to_string(connection->getDestinationLink()->getDestinationNode()) + " closed: Freeing " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
	} else {
		Logger::instance().log(occurrenceTime, simulationId, Logger::CONNECTION_CLOSED, "Connection between input: " + to_string(connection->getSourceLink()->getSourceNode()) + " and output " + to_string(connection->getDestinationLink()->getDestinationNode()) + " closed: Freeing " + to_string(connection->getFirstFSUOfInputLink()) + "-" + to_string(connection->getFirstFSUOfInputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in input link, " + to_string(connection->getFirstFSUOfInternalLinks()) + "-" + to_string(connection->getFirstFSUOfInternalLinks() + connection->getRequiredNumberOfFSUs() - 1) + " in internal links, " + to_string(connection->getFirstFSUOfOutputLink()) + "-" + to_string(connection->getFirstFSUOfOutputLink() + connection->getRequiredNumberOfFSUs() - 1) + " in output link (" + to_string(connection->getRequiredNumberOfFSUs()) + " FSUs)");
	}
	delete connection;
}