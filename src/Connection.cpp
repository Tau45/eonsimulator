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

void Connection::setPath(Path *newPath) {
	this->path = newPath;
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

void Connection::setFirstFSUOfInputLink(uint64_t firstFSU) {
	this->firstFSUOfInputLink = firstFSU;
}

void Connection::setFirstFSUOfInternalLinks(uint64_t firstFSU) {
	this->firstFSUOfInternalLinks = firstFSU;
}

void Connection::setFirstFSUOfOutputLink(uint64_t firstFSU) {
	this->firstFSUOfOutputLink = firstFSU;
}

uint64_t Connection::getRequiredNumberOfFSUs() {
	return requiredNumberOfFSUs;
}