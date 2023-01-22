#include "../../include/network/Link.h"

Link::Link(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput) {
	this->isInput = isInput;
	this->isOutput = isOutput;
	this->sourceNode = sourceNode;
	this->destinationNode = destinationNode;
	for (int i = 0; i < SimulationSettings::instance().getLinkCapacity(); i++) {
		FSUs.push_back(false);
	}
}

void Link::reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
	for (uint64_t i = firstFSU; i < firstFSU + numberOfFSUs; i++) {
		assert(!FSUs[i]);
		FSUs[i] = true;
	}
}

void Link::freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
	for (uint64_t i = firstFSU; i < firstFSU + numberOfFSUs; i++) {
		assert(FSUs[i]);
		FSUs[i] = false;
	}
}

vector<uint64_t> Link::getAvailableFirstFSUs(uint64_t requiredNumberOfFSUs) {
	vector<uint64_t> availableFirstFSUs;
	for (int i = 0; i <= SimulationSettings::instance().getLinkCapacity() - requiredNumberOfFSUs; i++) {
		if (hasFreeNeighboringFSUs(requiredNumberOfFSUs, i)) {
			availableFirstFSUs.push_back(i);
		}
	}
	return availableFirstFSUs;
}

bool Link::hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs) {
	for (int i = 0; i <= SimulationSettings::instance().getLinkCapacity() - requiredNumberOfFSUs; i++) {
		if (hasFreeNeighboringFSUs(requiredNumberOfFSUs, i)) {
			return true;
		}
	}
	return false;
}

bool Link::hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs, uint64_t startingFromFSU) {
	assert(requiredNumberOfFSUs < SimulationSettings::instance().getLinkCapacity());
	assert(startingFromFSU < SimulationSettings::instance().getLinkCapacity());
	assert(startingFromFSU + requiredNumberOfFSUs <= SimulationSettings::instance().getLinkCapacity());

	for (uint64_t i = startingFromFSU; i < startingFromFSU + requiredNumberOfFSUs; i++) {
		if (FSUIsOccupied(i)) {
			return false;
		}
	}
	return true;
}

bool Link::FSUIsOccupied(uint64_t FSUIndex) {
	return FSUs[FSUIndex];
}

uint64_t Link::getSourceNode() {
	return sourceNode;
}

uint64_t Link::getDestinationNode() {
	return destinationNode;
}

bool Link::isInputLink() {
	return isInput;
}

bool Link::isOutputLink() {
	return isOutput;
}