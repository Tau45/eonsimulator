#pragma once
#ifndef EONSIMULATOR_EVENTCOMPARATOR_H
#define EONSIMULATOR_EVENTCOMPARATOR_H

#include "../event/Event.h"

class EventComparator {
public:
    bool operator()(const Event *a, const Event *b);
};

#endif //EONSIMULATOR_EVENTCOMPARATOR_H