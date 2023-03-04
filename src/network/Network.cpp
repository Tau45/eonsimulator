#include "../../include/network/Network.h"

vector<uint64_t> Network::getAvailableFirstFSUsInPath(vector<Link *> &path, Connection &connection) {
	vector<uint64_t> availableFirstFSUs = path[1]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

	for (int i = 2; i < path.size() - 1; i++) {
		vector<uint64_t> availableFirstFSUsInCurrentLink = path[i]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		for (auto value: availableFirstFSUs) {
			if (!count(availableFirstFSUsInCurrentLink.begin(), availableFirstFSUsInCurrentLink.end(), value)) {
				availableFirstFSUs.erase(std::remove(availableFirstFSUs.begin(), availableFirstFSUs.end(), value), availableFirstFSUs.end());
			}
		}
	}
	return availableFirstFSUs;
}

bool Network::pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, Connection &connection, Generator &generator) {
	if (path.size() == 1) {
		vector<uint64_t> availableFirstFSUsInInputLink = path.front()->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		if (!availableFirstFSUsInInputLink.empty()) {
			connection.setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			return true;
		}
	} else if (path.size() == 2) {
		vector<uint64_t> availableFirstFSUsInInputLink = path.front()->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());
		vector<uint64_t> availableFirstFSUsInOutputLink = path.back()->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInOutputLink.empty()) {
			connection.setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			connection.setFirstFSUOfOutputLink(generator.getRandomFirstFSU(availableFirstFSUsInOutputLink));
			return true;
		}
	} else {
		vector<uint64_t> availableFirstFSUsInInputLink = path.front()->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());
		vector<uint64_t> availableFirstFSUsInInternalLinks = getAvailableFirstFSUsInPath(path, connection);
		vector<uint64_t> availableFirstFSUsInOutputLink = path.back()->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		if (!availableFirstFSUsInInputLink.empty() && !availableFirstFSUsInInternalLinks.empty() && !availableFirstFSUsInOutputLink.empty()) {
			connection.setFirstFSUOfInputLink(generator.getRandomFirstFSU(availableFirstFSUsInInputLink));
			connection.setFirstFSUOfInternalLinks(generator.getRandomFirstFSU(availableFirstFSUsInInternalLinks));
			connection.setFirstFSUOfOutputLink(generator.getRandomFirstFSU(availableFirstFSUsInOutputLink));
			return true;
		}
	}
	return false;
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

		vector<Link *> availableNextHops = generator.shuffleVector(links[currentPath.back()->getDestinationNode()]);

		for (auto &link: availableNextHops) {
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

	for (auto const &trafficClass: erlangTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: engsetTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: pascalTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.callsGenerated;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	return result;
}