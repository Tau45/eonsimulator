#include "../../include/network/Network.h"

vector<uint64_t> Network::getAvailableFirstFSUsInPath(vector<Link *> &path, Connection &connection) {
	vector<uint64_t> availableFirstFSUs = path[1]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

	for (int i = 2; i < path.size() - 1; i++) {
		vector<uint64_t> availableFirstFSUsInCurrentLink = path[i]->getAvailableFirstFSUs(connection.getRequiredNumberOfFSUs());

		vector<uint64_t> availableFirstFSUList = availableFirstFSUs;
		for (auto value: availableFirstFSUList) {
			if (!count(availableFirstFSUsInCurrentLink.begin(), availableFirstFSUsInCurrentLink.end(), value)) {
				availableFirstFSUs.erase(remove(availableFirstFSUs.begin(), availableFirstFSUs.end(), value), availableFirstFSUs.end());
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
	Link *sourceLink = connection.getSourceLink();
	vector<Link *> availableOutputLinks = getAvailableLinksInOutputDirection(connection.getOutputDirectionIndex(), connection.getRequiredNumberOfFSUs());

	if (!sourceLink->hasFreeNeighboringFSUs(connection.getRequiredNumberOfFSUs()) && !structureIsOneLink()) {
		return CONNECTION_REJECTED;
	}

	if (availableOutputLinks.empty()) {
		return EXTERNAL_BLOCK;
	}

	switch (GlobalSettings::instance().getSelectedAlgorithm()) {
		case GlobalSettings::POINT_TO_GROUP:
			availableOutputLinks = generator.shuffleVector(availableOutputLinks);
			for (auto link: availableOutputLinks) {
				if (checkPath({sourceLink}, link, connection, generator)) {
					return CONNECTION_CAN_BE_ESTABLISHED;
				}
			}
		case GlobalSettings::POINT_TO_POINT:
			Link *destinationLink = generator.getRandomOutputLink(availableOutputLinks);
			if (checkPath({sourceLink}, destinationLink, connection, generator)) {
				return CONNECTION_CAN_BE_ESTABLISHED;
			}
	}
	return INTERNAL_BLOCK;
}

bool Network::checkPath(vector<Link *> currentPath, Link *destinationLink, Connection &connection, Generator &generator) {
	if (currentPath.back() == destinationLink && pathHasRequiredNumberOfFreeFSUs(currentPath, connection, generator)) {
		connection.setPath(currentPath);
		return true;
	}

	vector<Link *> availableNextHops = generator.shuffleVector(getNextHops(currentPath.back()));

	for (auto &link: availableNextHops) {
		if (linkWasNotVisited(currentPath, link) && link->hasFreeNeighboringFSUs(connection.getRequiredNumberOfFSUs())) {
			vector<Link *> newPath(currentPath);
			newPath.push_back(link);

			if (checkPath(newPath, destinationLink, connection, generator)) {
				return true;
			}
		}
	}
	return false;
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