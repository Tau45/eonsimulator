#include "../../include/event/EventCallServiceTermination.h"

EventCallServiceTermination::EventCallServiceTermination(double occurrenceTime, const Connection &connection) {
	this->occurrenceTime = occurrenceTime;
	this->connection = connection;
}

void EventCallServiceTermination::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	network.closeConnection(occurrenceTime, connection, generator);
}