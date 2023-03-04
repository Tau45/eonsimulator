#include "../../include/event/EventNewCallArrivalEngsetClass.h"

EventNewCallArrivalEngsetClass::EventNewCallArrivalEngsetClass(TrafficClassStatistics &trafficClassStatistics) : trafficClassStatistics(trafficClassStatistics) {
	// TODO: Engset event initialization
}

void EventNewCallArrivalEngsetClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	// TODO: Engset event execution
}