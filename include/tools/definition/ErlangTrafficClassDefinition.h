#pragma once
#ifndef EONSIMULATOR_ERLANGTRAFFICCLASSDEFINITION_H
#define EONSIMULATOR_ERLANGTRAFFICCLASSDEFINITION_H

#include <iostream>

class ErlangTrafficClassDefinition {
	uint64_t requiredNumberOfFSUs;
	double serviceTime;

public:
	ErlangTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime);

	uint64_t getRequiredNumberOfFSUs();

	double getServiceTime();

	bool operator<(const ErlangTrafficClassDefinition &o) const {
		return requiredNumberOfFSUs < o.requiredNumberOfFSUs;
	}
};

#endif //EONSIMULATOR_ERLANGTRAFFICCLASSDEFINITION_H