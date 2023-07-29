#include "../include/Simulator.h"

Simulator::Simulator(double a, uint64_t simulationIndex, vector<int32_t> &seeds) :
		simulationId(a, simulationIndex),
		generator(seeds[0], seeds[1], seeds[2]) {
	addErlangTrafficClasses();
	addEngsetTrafficClasses();
	addPascalTrafficClasses();
}

SingleSimulationResults Simulator::run() {
	Logger::instance().log(0, simulationId, Logger::SIMULATION_START, "The simulation has started...");
	auto start = chrono::high_resolution_clock::now();

	while (network.getNumberOfGeneratedCallsOfTheLeastActiveClass() < GlobalSettings::instance().getCallsToGenerate()) {
		Event *event = eventQueue.top();
		eventQueue.pop();
		event->execute(network, eventQueue, generator, simulationId);

		delete event;
	}

	auto finish = chrono::high_resolution_clock::now();
	auto duration = duration_cast<chrono::milliseconds>(finish - start);
	Logger::instance().log(eventQueue.top()->getOccurrenceTime(), simulationId, Logger::SIMULATION_END, "The simulation has finished in " + to_string((double) duration.count() / 1000) + "s");

	return SingleSimulationResults(network.trafficClassStatistics);
}

void Simulator::addErlangTrafficClasses() {
	for (auto erlangTrafficClass: GlobalSettings::instance().getErlangTrafficClasses()) {
		network.trafficClassStatistics[erlangTrafficClass.getRequiredNumberOfFSUs()] = TrafficClassStatistics();
		double lambda = getLambda(erlangTrafficClass.getRequiredNumberOfFSUs(), network.getNumberOfInputLinks(), erlangTrafficClass.getServiceTime());

		eventQueue.push(new EventNewCallArrivalErlangClass(generator.getRandomOccurrenceTime(lambda),
														   lambda,
														   erlangTrafficClass.getServiceTime(),
														   new Connection(generator.getRandomOutputDirectionIndex(network.getNumberOfOutputDirections()), erlangTrafficClass.getRequiredNumberOfFSUs()),
														   network.trafficClassStatistics[erlangTrafficClass.getRequiredNumberOfFSUs()]));
	}
}

void Simulator::addEngsetTrafficClasses() {
	for (auto engsetTrafficClass: GlobalSettings::instance().getEngsetTrafficClasses()) {
		network.trafficClassStatistics[engsetTrafficClass.getRequiredNumberOfFSUs()] = TrafficClassStatistics();
		double gamma = getLambda(engsetTrafficClass.getRequiredNumberOfFSUs(), network.getNumberOfInputLinks(), engsetTrafficClass.getServiceTime());

		for (uint64_t i = 0; i < engsetTrafficClass.getNumberOfTrafficClasses(); i++) {
			eventQueue.push(new EventNewCallArrivalEngsetClass(generator.getRandomOccurrenceTime(gamma),
															   gamma,
															   engsetTrafficClass.getServiceTime(),
															   new Connection(generator.getRandomOutputDirectionIndex(network.getNumberOfOutputDirections()), engsetTrafficClass.getRequiredNumberOfFSUs()),
															   network.trafficClassStatistics[engsetTrafficClass.getRequiredNumberOfFSUs()]));
		}
	}
}

void Simulator::addPascalTrafficClasses() {}

double Simulator::getLambda(uint32_t requiredNumberOfFSUs, uint64_t numberOfInputLinks, double serviceTime) {
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	uint64_t numberOfTrafficClasses = GlobalSettings::instance().getNumberOfTrafficClasses();

	return (simulationId.getA() * numberOfInputLinks * linkCapacity) / (numberOfTrafficClasses * serviceTime * requiredNumberOfFSUs);
}

Simulator::~Simulator() {
	while (!eventQueue.empty()) {
		Event *event = eventQueue.top();
		eventQueue.pop();
		delete event;
	}
}