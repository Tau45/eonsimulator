#include "../../../include/tools/definition/ErlangTrafficClassDefinition.h"

ErlangTrafficClassDefinition::ErlangTrafficClassDefinition(uint64_t requiredNumberOfFSUs, double serviceTime) {
	this->requiredNumberOfFSUs = requiredNumberOfFSUs;
	this->serviceTime = serviceTime;
}

uint64_t ErlangTrafficClassDefinition::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}

double ErlangTrafficClassDefinition::getServiceTime() {
	return serviceTime;
}