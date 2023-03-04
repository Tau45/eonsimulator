#include "../../include/event/EventNewCallArrivalPascalClass.h"

EventNewCallArrivalPascalClass::EventNewCallArrivalPascalClass(TrafficClassStatistics &trafficClassStatistics) : trafficClassStatistics(trafficClassStatistics) {
	// TODO: Pascal event initialization
}

void EventNewCallArrivalPascalClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	// TODO: Pascal event execution
}