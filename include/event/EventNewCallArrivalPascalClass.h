#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalPascalClass : public Event {
	double beta;
	double serviceTime;
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalPascalClass(double occurrenceTime, double beta, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H