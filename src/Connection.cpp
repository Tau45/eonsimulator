#include "../include/Connection.h"

Connection::Connection(Link *sourceLink, vector<Link *> *outputDirection, uint64_t requiredNumberOfFSUs) :
		sourceLink(sourceLink),
		outputDirection(outputDirection),
		requiredNumberOfFSUs(requiredNumberOfFSUs) {}

void Connection::reserveResources() {
	path->getInputLink()->reserveFSUs(firstFSUOfInputLink, requiredNumberOfFSUs);

	if (getPathSize() > 1) {
		path->getOutputLink()->reserveFSUs(firstFSUOfOutputLink, requiredNumberOfFSUs);
	}

	if (getPathSize() > 2) {
		for (auto internalLink: path->getInternalLinks()) {
			internalLink->reserveFSUs(firstFSUOfInternalLinks, requiredNumberOfFSUs);
		}
	}
}

void Connection::close() {
	path->getInputLink()->freeFSUs(firstFSUOfInputLink, requiredNumberOfFSUs);

	if (getPathSize() > 1) {
		path->getOutputLink()->freeFSUs(firstFSUOfOutputLink, requiredNumberOfFSUs);
	}

	if (getPathSize() > 2) {
		for (auto internalLink: path->getInternalLinks()) {
			internalLink->freeFSUs(firstFSUOfInternalLinks, requiredNumberOfFSUs);
		}
	}
}

Link *Connection::getSourceLink() {
	return sourceLink;
}

Link *Connection::getDestinationLink() {
	return path->getOutputLink();
}

vector<Link *> *Connection::getOutputDirection() {
	return outputDirection;
}

uint64_t Connection::getPathSize() {
	return path->getPathSize();
}

bool Connection::pathHasFreeResources(Path *pathToCheck, Generator &generator) {
	if (pathToCheck->getPathSize() == 1) {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty()) {
			setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			path = pathToCheck;
			return true;
		}

	} else if (pathToCheck->getPathSize() == 2) {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInOutputLink = pathToCheck->getAvailableFirstFSUsInOutputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInOutputLink.empty()) {
			setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			setFirstFSUOfOutputLink(generator.getRandomFirstFSU(availableFirstFSUsInOutputLink));
			path = pathToCheck;
			return true;
		}
	} else {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInInternalLinks = pathToCheck->getAvailableFirstFSUsInInternalLinks(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInOutputLink = pathToCheck->getAvailableFirstFSUsInOutputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInInternalLinks.empty() && !availableFirstFSUsInOutputLink.empty()) {
			setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			setFirstFSUOfInternalLinks(generator.getRandomFirstFSU(availableFirstFSUsInInternalLinks));
			setFirstFSUOfOutputLink(generator.getRandomFirstFSU(availableFirstFSUsInOutputLink));
			path = pathToCheck;
			return true;
		}
	}
	return false;
}

uint64_t Connection::getFirstFSUOfInputLink() {
	return firstFSUOfInputLink;
}

uint64_t Connection::getFirstFSUOfInternalLinks() {
	return firstFSUOfInternalLinks;
}

uint64_t Connection::getFirstFSUOfOutputLink() {
	return firstFSUOfOutputLink;
}

void Connection::setFirstFSUOfInputLink(uint64_t firstFSUOfInputLink) {
	this->firstFSUOfInputLink = firstFSUOfInputLink;
}

void Connection::setFirstFSUOfInternalLinks(uint64_t firstFSUOfInternalLinks) {
	this->firstFSUOfInternalLinks = firstFSUOfInternalLinks;
}

void Connection::setFirstFSUOfOutputLink(uint64_t firstFSUOfOutputLink) {
	this->firstFSUOfOutputLink = firstFSUOfOutputLink;
}

uint64_t Connection::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}