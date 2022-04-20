#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVAL_H
#define EONSIMULATOR_EVENTNEWCALLARRIVAL_H

#include <iostream>
#include "Event.h"

class EventNewCallArrival : public Event {
    uint64_t srcLink;
    uint64_t dstLink;
    uint64_t connectionId;
    uint64_t numberOfFSUs;
    uint64_t serviceTime;
public:
    EventNewCallArrival(uint64_t srcLink, uint64_t dstLink, uint64_t connectionId, uint64_t numberOfFSUs,
                        uint64_t serviceTime);
    void execute(Network &network) override;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVAL_H