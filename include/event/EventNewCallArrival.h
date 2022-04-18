#pragma once
#ifndef EONSIMULATOR_EVENTNEWCALLARRIVAL_H
#define EONSIMULATOR_EVENTNEWCALLARRIVAL_H

#include <iostream>
#include "Event.h"

class EventNewCallArrival : public Event {
    uint16_t srcLinkIndex;
    uint16_t dstLinkIndex;
    uint64_t connectionId;
    uint16_t demandedFSUs;
    uint16_t serviceTime;
};

#endif //EONSIMULATOR_EVENTNEWCALLARRIVAL_H