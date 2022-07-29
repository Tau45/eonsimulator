#include "../../include/event/EventCallServiceTermination.h"

EventCallServiceTermination::EventCallServiceTermination(double occurrenceTime, Connection *connection) {
    this->occurrenceTime = occurrenceTime;
    this->connection = connection;
}

void EventCallServiceTermination::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) {
    network.closeConnection(occurrenceTime, connection);
}