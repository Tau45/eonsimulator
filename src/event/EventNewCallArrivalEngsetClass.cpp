#include "../../include/event/EventNewCallArrivalEngsetClass.h"

EventNewCallArrivalEngsetClass::EventNewCallArrivalEngsetClass(double occurrenceTime, Connection &connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		trafficClassStatistics(trafficClassStatistics) {
	// TODO: Engset event initialization
}

void EventNewCallArrivalEngsetClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	// TODO: Engset event execution
}