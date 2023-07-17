#pragma once
#ifndef EONSIMULATOR_PASCALTRAFFICCLASSDEFINITION_H
#define EONSIMULATOR_PASCALTRAFFICCLASSDEFINITION_H

#include <iostream>

class PascalTrafficClassDefinition {
	uint64_t requiredNumberOfFSUs;
	double serviceTime;
	uint64_t numberOfTrafficClasses;

public:
	PascalTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime, uint64_t numberOfTrafficClasses);

	uint64_t getRequiredNumberOfFSUs();

	double getServiceTime();

	uint64_t getNumberOfTrafficClasses();

	bool operator<(const PascalTrafficClassDefinition &o) const {
		return requiredNumberOfFSUs < o.requiredNumberOfFSUs;
	}
};

#endif //EONSIMULATOR_PASCALTRAFFICCLASSDEFINITION_H