#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H

#include <iostream>
#include "../tools/Generator.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalEngsetClass : public Event {
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalEngsetClass(TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALENGSETCLASS_H