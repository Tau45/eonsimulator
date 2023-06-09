#pragma once
#ifndef EONSIMULATOR_EVENT_H
#define EONSIMULATOR_EVENT_H

#include "../network/Network.h"
#include "../tools/SimulationId.h"

class Event {
protected:
	double occurrenceTime;
	Connection *connection;
public:
	class EventComparator {
	public:
		bool operator()(const Event *a, const Event *b) {
			return a->occurrenceTime > b->occurrenceTime;
		}
	};

	Event(double occurrenceTime, Connection *connection) : occurrenceTime(occurrenceTime), connection(connection) {}

	virtual void execute(Network &network, priority_queue<Event *, vector<Event *>, Event::EventComparator> &eventQueue, Generator &generator, SimulationId &simulationId) = 0;

	double getOccurrenceTime() { return occurrenceTime; }
};

#endif //EONSIMULATOR_EVENT_H