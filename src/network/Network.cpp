#include "../../include/network/Network.h"

void Network::buildNetworkStructure() {
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Structure creating started...");

	/// Parse file to create links:
	map<uint64_t, vector<Link *>> links;
	ifstream file(GlobalSettings::instance().getStructureFileName());

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string inputNodeIndexString;
		string outputNodeIndexString;

		if (getline(ss, inputNodeIndexString, ';') && getline(ss, outputNodeIndexString, ';')) {
			uint64_t inputNodeIndex = stoull(inputNodeIndexString);
			uint64_t outputNodeIndex = stoull(outputNodeIndexString);
			links[inputNodeIndex].push_back(new Link(inputNodeIndex, outputNodeIndex));
		}
	}
	file.close();

	/// Find input and output nodes:
	vector<uint64_t> sourceNodes;
	vector<uint64_t> destinationNodes;

	for (const auto &node: links) {
		for (const auto &link: node.second) {
			sourceNodes.push_back(link->getSourceNode());
			destinationNodes.push_back(link->getDestinationNode());
		}
	}

	vector<uint64_t> inputNodes;
	vector<uint64_t> outputNodes;

	for (auto value: sourceNodes) {
		if (!count(destinationNodes.begin(), destinationNodes.end(), value)) {
			inputNodes.push_back(value);
		}
	}

	for (auto value: destinationNodes) {
		if (!count(sourceNodes.begin(), sourceNodes.end(), value)) {
			outputNodes.push_back(value);
		}
	}

	/// Group output links pointing towards the same direction:
	map<uint64_t, vector<Link *>> outputDirectionsMap;

	for (const auto &node: links) {
		for (const auto &link: node.second) {
			if (count(inputNodes.begin(), inputNodes.end(), link->getSourceNode())) {
				inputLinks.push_back(link);
			}
			if (count(outputNodes.begin(), outputNodes.end(), link->getDestinationNode())) {
				outputDirectionsMap[link->getDestinationNode()].push_back(link);
			}
		}
	}

	for (auto &outputDirection: outputDirectionsMap) {
		outputDirections.push_back(outputDirection.second);
	}

	/// Calculate paths
	for (auto inputLink: inputLinks) {
		queue<vector<Link *>> incompletePaths;
		incompletePaths.push({inputLink});

		while (!incompletePaths.empty()) {
			vector<Link *> currentPath = incompletePaths.front();
			incompletePaths.pop();

			if (outputDirectionsMap.contains(currentPath.back()->getDestinationNode())) {
				paths[inputLink][currentPath.back()].emplace_back(new Path(currentPath));
			} else {
				for (auto &link: links[currentPath.back()->getDestinationNode()]) {
					if (!(find(currentPath.begin(), currentPath.end(), link) != currentPath.end())) {
						vector<Link *> newPath(currentPath);
						newPath.push_back(link);
						incompletePaths.push(newPath);
					}
				}
			}
		}
	}

	Logger::instance().log(Logger::CREATING_STRUCTURE, "Structure created");
}

void Network::printNetworkStructure() {
	string separator;

	/// Print information about input nodes
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Total number of input nodes: " + to_string(inputLinks.size()));
	stringstream inputNodesMessage;
	inputNodesMessage << "Input node list: ";
	for (auto &inputLink: inputLinks) {
		inputNodesMessage << separator << to_string(inputLink->getSourceNode());
		separator = ", ";
	}
	Logger::instance().log(Logger::CREATING_STRUCTURE, inputNodesMessage.str());

	/// Print information about output directions
	for (auto outputDirection: outputDirections) {
		stringstream outputDirectionMessage;
		outputDirectionMessage << "Created output direction " << outputDirection.at(0)->getDestinationNode() << " (" << outputDirection.size() << " nodes), reachable from nodes: ";
		separator = "";
		for (auto outputNode: outputDirection) {
			outputDirectionMessage << separator << to_string(outputNode->getSourceNode()) << "-" << to_string(outputNode->getDestinationNode());
			separator = ", ";
		}
		Logger::instance().log(Logger::CREATING_STRUCTURE, outputDirectionMessage.str());
	}

	/// Print information about paths
	separator = " -> ";
	uint64_t totalNumberOfPaths = 0;
	for (const auto &pathsFromInput: paths) {
		Logger::instance().log(Logger::CREATING_STRUCTURE, "Paths starting from input " + to_string(pathsFromInput.first->getSourceNode()) + ":");
		uint64_t numberOfPathsFromInput = 0;
		for (const auto &pathsToDirection: pathsFromInput.second) {
			numberOfPathsFromInput += pathsToDirection.second.size();
			for (auto path: pathsToDirection.second) {
				stringstream pathMessage;
				pathMessage << path->getInputLink()->getSourceNode();
				for (auto link: path->getPath()) {
					pathMessage << separator << link->getDestinationNode();
				}
				Logger::instance().log(Logger::CREATING_STRUCTURE, pathMessage.str());
			}
		}
		Logger::instance().log(Logger::CREATING_STRUCTURE, "Total number of paths starting from input " + to_string(pathsFromInput.first->getSourceNode()) + ": " + to_string(numberOfPathsFromInput));
		totalNumberOfPaths += numberOfPathsFromInput;
	}
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Total number of paths: " + to_string(totalNumberOfPaths));
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablished(Connection *connection, Generator &generator) {
	if (!findInputLinkWithFreeResources(connection, generator) && !structureIsOneLink()) {
		return CONNECTION_REJECTED;
	}

	if (!anyOutputLinkHasFreeResources(connection->getOutputDirectionIndex(), connection->getRequiredNumberOfFSUs())) {
		return EXTERNAL_BLOCK;
	}

	switch (GlobalSettings::instance().getSelectedAlgorithm()) {
		case GlobalSettings::POINT_TO_GROUP:
			return checkIfConnectionCanBeEstablishedPointToGroup(connection, generator);
		case GlobalSettings::POINT_TO_POINT:
			return checkIfConnectionCanBeEstablishedPointToPoint(connection, generator);
	}
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablishedPointToGroup(Connection *connection, Generator &generator) {
	vector<Link *> availableOutputLinks = getAvailableLinksToDestination(connection->getOutputDirectionIndex(), connection->getRequiredNumberOfFSUs());

	for (auto outputLink: generator.shuffleVector(availableOutputLinks)) {
		for (auto internalPath: generator.shuffleVector(getAllInternalPathsBetweenLinks(connection->getSourceLink(), outputLink))) {
			if (connection->pathHasFreeResources(internalPath, generator)) {
				return CONNECTION_CAN_BE_ESTABLISHED;
			}
		}
	}
	return INTERNAL_BLOCK;
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablishedPointToPoint(Connection *connection, Generator &generator) {
	vector<Link *> availableOutputLinks = getAvailableLinksToDestination(connection->getOutputDirectionIndex(), connection->getRequiredNumberOfFSUs());
	Link *randomDestinationLink = generator.getRandomLink(availableOutputLinks);

	for (auto internalPath: generator.shuffleVector(getAllInternalPathsBetweenLinks(connection->getSourceLink(), randomDestinationLink))) {
		if (connection->pathHasFreeResources(internalPath, generator)) {
			return CONNECTION_CAN_BE_ESTABLISHED;
		}
	}
	return INTERNAL_BLOCK;
}

uint64_t Network::getNumberOfGeneratedCallsOfTheLeastActiveClass() {
	uint64_t result = UINT64_MAX;

	for (auto const &trafficClass: erlangTrafficClassStatistics) {
		if (trafficClass.second.totalNumberOfCalls < result) {
			result = trafficClass.second.totalNumberOfCalls;
		}
	}

	for (auto const &trafficClass: engsetTrafficClassStatistics) {
		if (trafficClass.second.totalNumberOfCalls < result) {
			result = trafficClass.second.totalNumberOfCalls;
		}
	}

	for (auto const &trafficClass: pascalTrafficClassStatistics) {
		if (trafficClass.second.totalNumberOfCalls < result) {
			result = trafficClass.second.totalNumberOfCalls;
		}
	}

	return result;
}

vector<Link *> Network::getAvailableLinksToDestination(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs) {
	vector<Link *> availableOutputLinks;
	for (auto outputLink: outputDirections[outputDirectionIndex]) {
		if (outputLink->hasFreeNeighboringFSUs(requiredNumberOfFSUs)) {
			availableOutputLinks.push_back(outputLink);
		}
	}
	return availableOutputLinks;
}

bool Network::findInputLinkWithFreeResources(Connection *connection, Generator &generator) {
	for (auto inputLink: generator.shuffleVector(inputLinks)) {
		if (inputLink->hasFreeNeighboringFSUs(connection->getRequiredNumberOfFSUs())) {
			connection->setSourceLink(inputLink);
			return true;
		}
	}
	return false;
}

bool Network::anyOutputLinkHasFreeResources(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs) {
	for (auto outputLink: outputDirections[outputDirectionIndex]) {
		if (outputLink->hasFreeNeighboringFSUs(requiredNumberOfFSUs)) {
			return true;
		}
	}
	return false;
}

uint64_t Network::getNumberOfInputLinks() {
	return paths.size();
}

bool Network::structureIsOneLink() {
	return inputLinks.size() == 1 && outputDirections.size() == 1;
}

Network::Network() {
	buildNetworkStructure();
}

Network::~Network() {
	set<Link *> links;
	for (const auto &pathsFromInput: paths) {
		for (const auto &pathsToDirection: pathsFromInput.second) {
			for (auto path: pathsToDirection.second) {
				for (auto link: path->getPath()) {
					links.insert(link);
				}
				delete path;
			}
		}
	}
	for (auto link: links) {
		delete link;
	}
}

vector<Path *> Network::getAllInternalPathsBetweenLinks(Link *inputLink, Link *destinationLink) {
	return paths[inputLink][destinationLink];
}

uint64_t Network::getNumberOfOutputDirections() {
	return outputDirections.size();
}