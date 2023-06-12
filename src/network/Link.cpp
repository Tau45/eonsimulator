#include "../../include/network/Link.h"

Link::Link(uint64_t sourceNode, uint64_t destinationNode) :
		sourceNode(sourceNode),
		destinationNode(destinationNode) {
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	/// change
	FSUs = linkCapacity;
}

/// change
void Link::reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
	FSUs -= numberOfFSUs;
	assert(FSUs >= 0);
}

/// change
void Link::freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs) {
	FSUs += numberOfFSUs;
	assert(FSUs <= GlobalSettings::instance().getLinkCapacity());
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

/// change
bool Link::hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs, uint64_t startingFromFSU) {
	return FSUs >= requiredNumberOfFSUs;
}

/// unused
bool Link::FSUIsOccupied(uint64_t FSUIndex) {
	return false;
}

uint64_t Link::getSourceNode() {
	return sourceNode;
}

uint64_t Link::getDestinationNode() {
	return destinationNode;
}