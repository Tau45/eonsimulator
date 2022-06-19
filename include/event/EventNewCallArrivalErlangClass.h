#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H
#define EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H

#include <iostream>
#include "Event.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrivalErlangClass : public Event {
    uint64_t numberOfInputLinks;
    uint64_t numberOfOutputLinks;
    uint64_t trafficClass;
public:
    EventNewCallArrivalErlangClass(Generator *generator, uint64_t clock, uint64_t numberOfInputLinks,
                                   uint64_t numberOfOutputLinks, uint64_t trafficClass);

    vector<Event *> execute(Network &network, uint64_t clock, uint64_t &callsGenerated) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVALERLANGCLASS_H