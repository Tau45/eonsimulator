#include "../../include/tools/Generator.h"

Generator::Generator(int32_t seed1, int32_t seed2, int32_t seed3) {
	this->x1 = seed1;
	this->x2 = seed2;
	this->x3 = seed3;
}

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

double Generator::getRandomServiceTime(double serviceTime) {
	return log(rown_v2(x2)) * (-serviceTime);
}

double Generator::getRandomOccurrenceTime(double intensity) {
	return log(rown_v1(x1)) * (-1 / intensity);
}

uint64_t Generator::getRandomNaturalNumber(uint64_t numberOfNumbers) {
	uint64_t randomLink = rown_v3(x3) * numberOfNumbers;

	if (randomLink == numberOfNumbers) {
		randomLink--;
	}
	return randomLink;
}

uint64_t Generator::getRandomOutputDirectionIndex(uint64_t numberOfOutputDirections) {
	return getRandomNaturalNumber(numberOfOutputDirections);
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