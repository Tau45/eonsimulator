#include "../include/Connection.h"

Connection::Connection(Link *sourceLink, Link *destinationLink, uint64_t requiredNumberOfFSUs, double serviceTime) {
	this->sourceLink = sourceLink;
	this->destinationLink = destinationLink;
	this->firstFSUOfInputLink = UINT64_MAX;
	this->firstFSUOfInternalLinks = UINT64_MAX;
	this->firstFSUOfOutputLink = UINT64_MAX;
	this->requiredNumberOfFSUs = requiredNumberOfFSUs;
	this->serviceTime = serviceTime;
}

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

Link *Connection::getSourceLink() {
	return sourceLink;
}

Link *Connection::getDestinationLink() {
	return destinationLink;
}

uint64_t Connection::getPathSize() {
	return path.size();
}

void Connection::setPath(vector<Link *> newPath) {
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

Connection::Connection() {
}

Connection::Connection(Connection &connection) {
	sourceLink = connection.sourceLink;
	destinationLink = connection.destinationLink;
	path = connection.path;
	firstFSUOfInputLink = connection.firstFSUOfInputLink;
	firstFSUOfInternalLinks = connection.firstFSUOfInternalLinks;
	firstFSUOfOutputLink = connection.firstFSUOfOutputLink;
	requiredNumberOfFSUs = connection.requiredNumberOfFSUs;
	serviceTime = connection.serviceTime;
}
