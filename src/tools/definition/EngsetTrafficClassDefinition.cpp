#include "../../../include/tools/definition/EngsetTrafficClassDefinition.h"

EngsetTrafficClassDefinition::EngsetTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime, uint64_t numberOfTrafficClasses) {
	this->requiredNumberOfFSUs = requiredNumberOfFSUs;
	this->serviceTime = serviceTime;
	this->numberOfTrafficClasses = numberOfTrafficClasses;
}

uint64_t EngsetTrafficClassDefinition::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}

double EngsetTrafficClassDefinition::getServiceTime() {
	return serviceTime;
}

uint64_t EngsetTrafficClassDefinition::getNumberOfTrafficClasses() {
	return numberOfTrafficClasses;
}