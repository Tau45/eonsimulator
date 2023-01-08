#include "../include/Connection.h"

Connection::Connection(uint64_t sourceLink, uint64_t destinationLink, uint64_t requiredNumberOfFSUs, double serviceTime) {
	this->sourceLink = sourceLink;
	this->destinationLink = destinationLink;
	this->requiredNumberOfFSUs = requiredNumberOfFSUs;
	this->serviceTime = serviceTime;
}

uint64_t Connection::getSourceLink() {
	return sourceLink;
}

uint64_t Connection::getDestinationLink() {
	return destinationLink;
}

vector<Link *> Connection::getPath() {
	return path;
}

void Connection::setPath(vector<Link *> newPath) {
	this->path = newPath;
}

uint64_t Connection::getFirstFSU() {
	return firstFSU;
}

void Connection::setFirstFSU(uint64_t newFirstFSU) {
	this->firstFSU = newFirstFSU;
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
	firstFSU = connection.firstFSU;
	requiredNumberOfFSUs = connection.requiredNumberOfFSUs;
	serviceTime = connection.serviceTime;
}
