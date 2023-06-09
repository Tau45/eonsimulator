#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H

#include "EventCallServiceTermination.h"

class EventNewCallArrivalPascalClass : public Event {
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalPascalClass(double occurrenceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H