#include "../../include/network/Network.h"

bool Network::setFirstFSUOfInputLink(Link *link, Connection &connection, Generator &generator) {
	vector<uint64_t> availableFirstFSUs = link->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

	if (!availableFirstFSUs.empty()) {
		connection.setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUs));
		return true;
	}
	return false;
}

bool Network::setFirstFSUOfOutputLink(Link *link, Connection &connection, Generator &generator) {
	vector<uint64_t> availableFirstFSUs = link->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

	if (!availableFirstFSUs.empty()) {
		connection.setFirstFSUOfOutputLink(generator.getRandomFirstFSU(availableFirstFSUs));
		return true;
	}
	return false;
}

bool Network::setFirstFSUOfInternalLinks(vector<Link *> &path, Connection &connection, Generator &generator) {
	vector<uint64_t> availableFirstFSUs = path[1]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

	for (int i = 2; i < path.size() - 1; i++) {
		if (availableFirstFSUs.empty()) {
			return false;
		}
		vector<uint64_t> availableFirstFSUsInCurrentLink = path[i]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		for (auto value: availableFirstFSUsInCurrentLink) {
			remove(availableFirstFSUs.begin(), availableFirstFSUs.end(), value);
		}
	}

	if (!availableFirstFSUs.empty()) {
		connection.setFirstFSUOfInternalLinks(generator.getRandomFirstFSU(availableFirstFSUs));
		return true;
	}
	return false;
}

bool Network::pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, Connection &connection, Generator &generator) {
	bool result = setFirstFSUOfInputLink(path.front(), connection, generator);
	if (path.size() > 1) {
		result = result && setFirstFSUOfOutputLink(path.back(), connection, generator);
	}
	if (path.size() > 2) {
		result = result && setFirstFSUOfInternalLinks(path, connection, generator);
	}
	return result;
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablished(Connection &connection, Generator &generator) {
	if (!connection.getSourceLink()->hasFreeNeighboringFSUs(connection.getRequiredNumberOfFSUs()) && links.size() > 1) {
		return CONNECTION_REJECTED;
	}

	if (!connection.getDestinationLink()->hasFreeNeighboringFSUs(connection.getRequiredNumberOfFSUs())) {
		return EXTERNAL_BLOCK;
	}

	queue<vector<Link *>> consideredPaths;
	consideredPaths.push({connection.getSourceLink()});

	while (!consideredPaths.empty()) {
		vector<Link *> currentPath = consideredPaths.front();
		consideredPaths.pop();

		if (currentPath.back() == connection.getDestinationLink() && pathHasRequiredNumberOfFreeFSUs(currentPath, connection, generator)) {
			connection.setPath(currentPath);
			return CONNECTION_CAN_BE_ESTABLISHED;
		}

		for (auto &link: links[currentPath.back()->getDestinationNode()]) {
			if (linkWasNotVisited(currentPath, link->getDestinationNode())) {
				vector<Link *> newPath(currentPath);
				newPath.push_back(link);
				consideredPaths.push(newPath);
			}
		}
	}

	return INTERNAL_BLOCK;
}

uint64_t Network::getNumberOfGeneratedCallsOfTheLeastActiveClass() {
	uint64_t result = UINT64_MAX;

	for (auto const &trafficClass: erlangTrafficClasses) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: engsetTrafficClasses) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: pascalTrafficClasses) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	return result;
}