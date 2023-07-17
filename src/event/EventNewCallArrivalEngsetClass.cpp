#include "../../include/event/EventNewCallArrivalEngsetClass.h"

EventNewCallArrivalEngsetClass::EventNewCallArrivalEngsetClass(double occurrenceTime, double gamma, double serviceTime, Connection *connection, TrafficClassStatistics &trafficClassStatistics) :
		Event(occurrenceTime, connection),
		gamma(gamma),
		serviceTime(serviceTime),
		trafficClassStatistics(trafficClassStatistics) {}

void EventNewCallArrivalEngsetClass::execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) {
	// TODO: Engset event execution
}