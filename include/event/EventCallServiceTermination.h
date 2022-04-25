#pragma once
#ifndef EONSIMULATOR_EVENTCALLSERVICETERMINATION_H
#define EONSIMULATOR_EVENTCALLSERVICETERMINATION_H

#include <iostream>
#include "Event.h"

class EventCallServiceTermination : public Event {
public:
    EventCallServiceTermination(uint64_t occurrenceTime, Connection *connection);

    Event *execute(Network &network, uint64_t clock) override;
};

#endif //EONSIMULATOR_EVENTCALLSERVICETERMINATION_H