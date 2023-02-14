#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H

#include <iostream>
#include "../tools/Generator.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalPascalClass : public Event {
public:
	EventNewCallArrivalPascalClass();

	void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALPASCALCLASS_H