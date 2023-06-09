#pragma once
#ifndef EONSIMULATOR_EVENTCALLSERVICETERMINATION_H
#define EONSIMULATOR_EVENTCALLSERVICETERMINATION_H

#include "Event.h"

class EventCallServiceTermination : public Event {
public:
	EventCallServiceTermination(double occurrenceTime, Connection *connection);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) override;
};

#endif //EONSIMULATOR_EVENTCALLSERVICETERMINATION_H