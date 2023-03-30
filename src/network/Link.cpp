#include "../../include/network/Link.h"

Link::Link(uint64_t sourceNode, uint64_t destinationNode) :
		sourceNode(sourceNode),
		destinationNode(destinationNode) {
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	for (int i = 0; i < linkCapacity; i++) {
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
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	assert(requiredNumberOfFSUs < linkCapacity);

	vector<uint64_t> availableFirstFSUs;
	for (int i = 0; i <= linkCapacity - requiredNumberOfFSUs; i++) {
		if (hasFreeNeighboringFSUs(requiredNumberOfFSUs, i)) {
			availableFirstFSUs.push_back(i);
		}
	}
	return availableFirstFSUs;
}

bool Link::hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs) {
	return !getAvailableFirstFSUs(requiredNumberOfFSUs).empty();
}

bool Link::hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs, uint64_t startingFromFSU) {
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	assert(requiredNumberOfFSUs < linkCapacity);
	assert(startingFromFSU < linkCapacity);
	assert(startingFromFSU + requiredNumberOfFSUs <= linkCapacity);

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