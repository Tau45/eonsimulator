#include "../../include/tools/SimulationId.h"

SimulationId::SimulationId(double a, uint64_t simulationIndex) : a(a), simulationIndex(simulationIndex) {}

double SimulationId::getA() {
	return a;
}

uint64_t SimulationId::getSimulationIndex() {
	return simulationIndex;
}