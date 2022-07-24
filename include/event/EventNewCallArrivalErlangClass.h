#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include <iostream>
#include "Event.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;
    uint64_t requiredNumberOfFSUs;
public:
    EventNewCallArrivalErlangClass(Generator *generator, uint64_t clock, uint64_t numberOfInputLinks, uint64_t numberOfOutputLinks, uint64_t requiredNumberOfFSUs);

    void execute(Network &network, uint64_t clock, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H