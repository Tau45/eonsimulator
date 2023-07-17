#include "../../../include/tools/definition/PascalTrafficClassDefinition.h"

PascalTrafficClassDefinition::PascalTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime, uint64_t numberOfTrafficClasses) {
	this->requiredNumberOfFSUs = requiredNumberOfFSUs;
	this->serviceTime = serviceTime;
	this->numberOfTrafficClasses = numberOfTrafficClasses;
}

uint64_t PascalTrafficClassDefinition::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}

double PascalTrafficClassDefinition::getServiceTime() {
	return serviceTime;
}

uint64_t PascalTrafficClassDefinition::getNumberOfTrafficClasses() {
	return numberOfTrafficClasses;
}