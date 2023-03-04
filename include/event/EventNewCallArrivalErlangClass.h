#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include <iostream>
#include "../tools/Generator.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
	uint64_t requiredNumberOfFSUs;
	TrafficClassStatistics &trafficClassStatistics;
public:
	EventNewCallArrivalErlangClass(double currentTime, uint64_t requiredNumberOfFSUs, Network &network, Generator &generator, TrafficClassStatistics &trafficClassStatistics);

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H