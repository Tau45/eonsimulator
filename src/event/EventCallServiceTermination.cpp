#include "../../include/event/EventCallServiceTermination.h"

EventCallServiceTermination::EventCallServiceTermination(uint64_t occurrenceTime, Connection *connection) {
    this->occurrenceTime = occurrenceTime;
    this->priority = 0;
    this->connection = connection;
}

void EventCallServiceTermination::execute(Network &network, uint64_t clock, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) {
    network.closeConnection(connection);
}