#include "../../include/tools/Generator.h"

Generator::Generator(double a, int32_t x1, int32_t x2, int32_t x3, uint64_t simulationIndex) :
		a(a),
		simulationIndex(simulationIndex),
		x1(x1),
		x2(x2),
		x3(x3) {}

double Generator::rown_v1(int &x) {
	int a = 16807, q = 127773, r = 2836, h;
	h = int(x / q);
	x = a * (x - q * h) - r * h;
	if (x < 0) x = x + 2147483647;
	return double(x) / 2147483647;
}

double Generator::rown_v2(int &x) {
	int a = 48271, q = 44488, r = 3399, h;
	h = int(x / q);
	x = a * (x - q * h) - r * h;
	if (x < 0) x = x + 2147483647;
	return double(x) / 2147483647;
}

double Generator::rown_v3(int &x) {
	int a = 69621, q = 30845, r = 23902, h;
	h = int(x / q);
	x = a * (x - q * h) - r * h;
	if (x < 0) x = x + 2147483647;
	return double(x) / 2147483647;
}

double Generator::getLambda(uint32_t requiredNumberOfFSUs) {
	uint64_t numberOfInputLinks = SimulationSettings::instance().getNumberOfInputLinks();
	uint64_t linkCapacity = SimulationSettings::instance().getLinkCapacity();
	uint64_t numberOfTrafficClasses = SimulationSettings::instance().getNumberOfTrafficClasses();
	double serviceTime = SimulationSettings::instance().getServiceTime();

	return (a * numberOfInputLinks * linkCapacity) / (numberOfTrafficClasses * serviceTime * requiredNumberOfFSUs);
}

double Generator::getRandomServiceTime() {
	double serviceTime = SimulationSettings::instance().getServiceTime();
	return log(rown_v1(x3)) * (-serviceTime);
}

double Generator::getRandomOccurrenceTime(uint32_t requiredNumberOfFSUs) {
	return log(rown_v1(x1)) * (-1 / getLambda(requiredNumberOfFSUs));
}

uint64_t Generator::getRandomInputLink() {
	uint64_t randomLink = rown_v3(x3) * SimulationSettings::instance().getNumberOfInputLinks();

	if (randomLink == SimulationSettings::instance().getNumberOfInputLinks()) {
		return randomLink - 1;
	}

	return randomLink;
}

uint64_t Generator::getRandomOutputLink() {
	uint64_t randomLink = rown_v3(x3) * SimulationSettings::instance().getNumberOfOutputLinks();

	if (randomLink == SimulationSettings::instance().getNumberOfOutputLinks()) {
		return randomLink - 1;
	}

	return randomLink;
}

uint64_t Generator::getRandomFirstFSU(vector<uint64_t> availableFirstFSUs) {
	uint64_t randomFirstFSUIndex = rown_v2(x2) * availableFirstFSUs.size();

	if (randomFirstFSUIndex == availableFirstFSUs.size()) {
		randomFirstFSUIndex--;
	}

	return availableFirstFSUs[randomFirstFSUIndex];
}

vector<Link *> Generator::shuffleVector(vector<Link *> inputVector) {
	vector<Link *> outputVector;

	while (!inputVector.empty()) {
		uint64_t randomVectorElementIndex = rown_v2(x2) * inputVector.size();

		if (randomVectorElementIndex == inputVector.size()) {
			randomVectorElementIndex--;
		}

		outputVector.push_back(inputVector.at(randomVectorElementIndex));
		inputVector.erase(inputVector.begin() + randomVectorElementIndex);
	}
	return outputVector;
}

double Generator::getA() {
	return a;
}

uint64_t Generator::getSimulationIndex() {
	return simulationIndex;
}