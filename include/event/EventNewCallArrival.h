#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVAL_H
#define EONSIMULATOR_EVENTNEWCALLARRIVAL_H

#include <iostream>
#include "Event.h"
#include "EventCallServiceTermination.h"

class EventNewCallArrival : public Event {
public:
    EventNewCallArrival(uint64_t occurrenceTime, uint64_t srcLink, uint64_t dstLink, uint64_t numberOfFSUs,
                        uint64_t serviceTime);

    Event *execute(Network &network, uint64_t clock) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVAL_H