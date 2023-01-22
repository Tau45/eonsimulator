#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include <cassert>
#include <vector>
#include "../tools/SimulationSettings.h"

class Link {
	bool isInput;
	bool isOutput;
	vector<bool> FSUs;
	uint64_t sourceNode;
	uint64_t destinationNode;

	bool FSUIsOccupied(uint64_t FSUIndex);

	bool hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs, uint64_t startingFromFSU);

public:
	Link(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput);

	void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	vector<uint64_t> getAvailableFirstFSUs(uint64_t requiredNumberOfFSUs);

	bool hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs);

	uint64_t getSourceNode();

	uint64_t getDestinationNode();

	bool isInputLink();

	bool isOutputLink();
};

#endif //EONSIMULATOR_LINK_H