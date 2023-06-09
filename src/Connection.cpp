#include "../include/Connection.h"

Connection::Connection(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs) :
		outputDirectionIndex(outputDirectionIndex),
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

void Connection::setSourceLink(Link *newSourceLink) {
	this->sourceLink = newSourceLink;
}

Link *Connection::getSourceLink() {
	return sourceLink;
}

Link *Connection::getDestinationLink() {
	return path->getOutputLink();
}

uint64_t Connection::getOutputDirectionIndex() {
	return outputDirectionIndex;
}

uint64_t Connection::getPathSize() {
	return path->getPathSize();
}

bool Connection::pathHasFreeResources(Path *pathToCheck, Generator &generator) {
	if (pathToCheck->getPathSize() == 1) {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty()) {
			firstFSUOfInputLink = generator.getRandomFirstFSU(availableFirstFSUsInInputLink);
			path = pathToCheck;
			return true;
		}
	} else if (pathToCheck->getPathSize() == 2) {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInOutputLink = pathToCheck->getAvailableFirstFSUsInOutputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInOutputLink.empty()) {
			firstFSUOfInputLink = generator.getRandomFirstFSU(availableFirstFSUsInInputLink);
			firstFSUOfOutputLink = availableFirstFSUsInOutputLink[0];
			path = pathToCheck;
			return true;
		}
	} else {
		vector<uint64_t> availableFirstFSUsInInputLink = pathToCheck->getAvailableFirstFSUsInInputLink(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInInternalLinks = pathToCheck->getAvailableFirstFSUsInInternalLinks(requiredNumberOfFSUs);
		vector<uint64_t> availableFirstFSUsInOutputLink = pathToCheck->getAvailableFirstFSUsInOutputLink(requiredNumberOfFSUs);

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInInternalLinks.empty() && !availableFirstFSUsInOutputLink.empty()) {
			firstFSUOfInputLink = generator.getRandomFirstFSU(availableFirstFSUsInInputLink);
			firstFSUOfInternalLinks = availableFirstFSUsInInternalLinks[0];
			firstFSUOfOutputLink = availableFirstFSUsInOutputLink[0];
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

uint64_t Connection::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}