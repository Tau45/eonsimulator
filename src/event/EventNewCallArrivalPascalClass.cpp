#include "../../include/event/EventNewCallArrivalPascalClass.h"

EventNewCallArrivalPascalClass::EventNewCallArrivalPascalClass(double occurrenceTime, double beta, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		beta(beta),
		serviceTime(serviceTime),
		trafficClassStatistics(trafficClassStatistics) {}

void EventNewCallArrivalPascalClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) {
	// TODO: Pascal event execution
}