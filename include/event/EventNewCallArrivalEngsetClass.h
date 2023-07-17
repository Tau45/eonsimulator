#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalEngsetClass : public Event {
	double gamma;
	double serviceTime;
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalEngsetClass(double occurrenceTime, double gamma, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H