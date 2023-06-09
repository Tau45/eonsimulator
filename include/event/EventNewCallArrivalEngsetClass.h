#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalEngsetClass : public Event {
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalEngsetClass(double occurrenceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H