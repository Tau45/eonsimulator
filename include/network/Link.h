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
public:
	Link(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity, bool isInput, bool isOutput);

	void reserveFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	void freeFSUs(uint16_t firstFSU, uint16_t numberOfFSUs);

	void freeAllFSUs();

	bool FSUIsOccupied(uint64_t FSUIndex);

	uint64_t getSourceNode();

	uint64_t getDestinationNode();

	bool isInputLink();

	bool isOutputLink();
};

#endif //EONSIMULATOR_LINK_H