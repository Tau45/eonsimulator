#pragma once
#ifndef EONSIMULATOR_LINK_H
#define EONSIMULATOR_LINK_H

#include <iostream>
#include <cassert>
#include <vector>
#include "../tools/GlobalSettings.h"

class Link {
	bool isInput;
	bool isOutput;
	vector<bool> FSUs;
	uint64_t sourceNode;
	uint64_t destinationNode;
	uint64_t outputDirectionIndex;

	Link(uint64_t sourceNode, uint64_t destinationNode, uint64_t outputDirectionIndex);

	bool FSUIsOccupied(uint64_t FSUIndex);

	bool hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs, uint64_t startingFromFSU);

	uint64_t getOutputDirectionIndex();

	void setAsInput();

	void setAsOutput();

	bool isInputLink();

	bool isOutputLink();

	friend class Structure;

public:
	void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	vector<uint64_t> getAvailableFirstFSUs(uint64_t requiredNumberOfFSUs);

	bool hasFreeNeighboringFSUs(uint64_t requiredNumberOfFSUs);

	uint64_t getSourceNode();

	uint64_t getDestinationNode();
};

#endif //EONSIMULATOR_LINK_H