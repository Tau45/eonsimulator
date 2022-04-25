#include "../../include/tools/EventComparator.h"

bool EventComparator::operator()(const Event *a, const Event *b) {
    return a->occurrenceTime == b->occurrenceTime
           ? a->priority > b->priority
           : a->occurrenceTime > b->occurrenceTime;
}