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
	uint64_t numberOfInputLinks = GlobalSettings::instance().getNumberOfInputLinks();
	uint64_t linkCapacity = GlobalSettings::instance().getLinkCapacity();
	uint64_t numberOfTrafficClasses = GlobalSettings::instance().getNumberOfTrafficClasses();
	double serviceTime = GlobalSettings::instance().getServiceTime();

	return (a * numberOfInputLinks * linkCapacity) / (numberOfTrafficClasses * serviceTime * requiredNumberOfFSUs);
}

double Generator::getRandomServiceTime() {
	double serviceTime = GlobalSettings::instance().getServiceTime();
	return log(rown_v2(x2)) * (-serviceTime);
}

double Generator::getRandomOccurrenceTime(uint32_t requiredNumberOfFSUs) {
	return log(rown_v1(x1)) * (-1 / getLambda(requiredNumberOfFSUs));
}

uint64_t Generator::getRandomNaturalNumber(uint64_t numberOfNumbers) {
	uint64_t randomLink = rown_v3(x3) * numberOfNumbers;

	if (randomLink == numberOfNumbers) {
		randomLink--;
	}
	return randomLink;
}

uint64_t Generator::getRandomInputLinkIndex() {
	return getRandomNaturalNumber(GlobalSettings::instance().getNumberOfInputLinks());
}

uint64_t Generator::getRandomOutputDirectionIndex() {
	return getRandomNaturalNumber(GlobalSettings::instance().getNumberOfOutputDirections());
}

Link *Generator::getRandomOutputLink(vector<Link *> outputLinks) {
	return outputLinks[getRandomNaturalNumber(outputLinks.size())];
}

uint64_t Generator::getRandomFirstFSU(vector<uint64_t> availableFirstFSUs) {
	return availableFirstFSUs[getRandomNaturalNumber(availableFirstFSUs.size())];
}

vector<Link *> Generator::shuffleVector(vector<Link *> inputVector) {
	vector<Link *> outputVector;

	while (!inputVector.empty()) {
		uint64_t randomVectorElementIndex = getRandomNaturalNumber(inputVector.size());

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