#include "../../include/event/EventCallServiceTermination.h"

EventCallServiceTermination::EventCallServiceTermination(uint64_t occurrenceTime, Connection *connection) {
    this->occurrenceTime = occurrenceTime;
    this->priority = 0;
    this->connection = connection;
}

vector<Event *> EventCallServiceTermination::execute(Network &network, uint64_t clock) {
    network.closeConnection(connection);
    return vector<Event *>{};
}