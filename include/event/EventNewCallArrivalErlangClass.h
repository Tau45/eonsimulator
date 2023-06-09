#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
	double lambda;
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalErlangClass(double occurrenceTime, double lambda, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H