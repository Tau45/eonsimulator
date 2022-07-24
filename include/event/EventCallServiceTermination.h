#pragma once
#ifndef EONSIMULATOR_EVENTCALLSERVICETERMINATION_H
#define EONSIMULATOR_EVENTCALLSERVICETERMINATION_H

#include <iostream>
#include "Event.h"

class EventCallServiceTermination : public Event {
public:
    EventCallServiceTermination(uint64_t clock, Connection *connection);

    void execute(Network &network, uint64_t clock, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) override;
};

#endif //EONSIMULATOR_EVENTCALLSERVICETERMINATION_H