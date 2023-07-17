#pragma once
#ifndef EONSIMULATOR_ENGSETTRAFFICCLASSDEFINITION_H
#define EONSIMULATOR_ENGSETTRAFFICCLASSDEFINITION_H

#include <iostream>

class EngsetTrafficClassDefinition {
	uint64_t requiredNumberOfFSUs;
	double serviceTime;
	uint64_t numberOfTrafficClasses;

public:
	EngsetTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime, uint64_t numberOfTrafficClasses);

	uint64_t getRequiredNumberOfFSUs();

	double getServiceTime();

	uint64_t getNumberOfTrafficClasses();

	bool operator<(const EngsetTrafficClassDefinition &o) const {
		return requiredNumberOfFSUs < o.requiredNumberOfFSUs;
	}
};

#endif //EONSIMULATOR_ENGSETTRAFFICCLASSDEFINITION_H