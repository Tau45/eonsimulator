#include "../include/Connection.h"

Connection::Connection(uint64_t sourceLinkIndex, uint64_t destinationLinkIndex, uint64_t requiredNumberOfFSUs, double serviceTime) :
		sourceLinkIndex(sourceLinkIndex),
		destinationLinkIndex(destinationLinkIndex),
		requiredNumberOfFSUs(requiredNumberOfFSUs),
		serviceTime(serviceTime) {}

void Connection::reserveResources() {
	assert(!path.empty());
	path.front()->reserveFSUs(firstFSUOfInputLink, requiredNumberOfFSUs);

	if (path.size() > 1) {
		path.back()->reserveFSUs(firstFSUOfOutputLink, requiredNumberOfFSUs);
	}

	if (path.size() > 2) {
		for (int i = 1; i < path.size() - 1; i++) {
			path[i]->reserveFSUs(firstFSUOfInternalLinks, requiredNumberOfFSUs);
		}
	}
}

void Connection::close() {
	path.front()->freeFSUs(firstFSUOfInputLink, requiredNumberOfFSUs);

	if (path.size() > 1) {
		path.back()->freeFSUs(firstFSUOfOutputLink, requiredNumberOfFSUs);
	}

	if (path.size() > 2) {
		for (int i = 1; i < path.size() - 1; i++) {
			path[i]->freeFSUs(firstFSUOfInternalLinks, requiredNumberOfFSUs);
		}
	}
}

uint64_t Connection::getSourceLinkIndex() {
	return sourceLinkIndex;
}

uint64_t Connection::getDestinationLinkIndex() {
	return destinationLinkIndex;
}

uint64_t Connection::getPathSize() {
	return path.size();
}

void Connection::setPath(vector<Link *> &path) {
	this->path = path;
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

double Connection::getServiceTime() {
	return serviceTime;
}