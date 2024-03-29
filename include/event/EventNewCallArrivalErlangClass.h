#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
	double lambda;
	double serviceTime;
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalErlangClass(double occurrenceTime, double lambda, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H