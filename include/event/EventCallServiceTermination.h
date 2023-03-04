#pragma once
#ifndef EONSIMULATOR_EVENTCALLSERVICETERMINATION_H
#define EONSIMULATOR_EVENTCALLSERVICETERMINATION_H

#include <iostream>
#include "Event.h"

class EventCallServiceTermination : public Event {
public:
	EventCallServiceTermination(double occurrenceTime, Connection &connection);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTCALLSERVICETERMINATION_H