#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include <iostream>
#include "Event.h"
#include "../tools/Generator.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
    Generator *generator;
    uint64_t requiredNumberOfFSUs;
public:
    EventNewCallArrivalErlangClass(double currentTime, Generator *generator, uint64_t requiredNumberOfFSUs);

    void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H