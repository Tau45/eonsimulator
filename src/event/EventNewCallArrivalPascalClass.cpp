#include "../../include/event/EventNewCallArrivalPascalClass.h"

EventNewCallArrivalPascalClass::EventNewCallArrivalPascalClass(double occurrenceTime, Connection &connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		trafficClassStatistics(trafficClassStatistics) {
	// TODO: Pascal event initialization
}

void EventNewCallArrivalPascalClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator) {
	// TODO: Pascal event execution
}