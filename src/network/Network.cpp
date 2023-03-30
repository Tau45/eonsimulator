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
				paths[inputLink->getSourceNode()][currentPath.back()->getDestinationNode()].emplace_back(new Path(currentPath));
			} else {
				for (auto &link: links[currentPath.back()->getDestinationNode()]) {
					if (!linkWasVisited(currentPath, link)) {
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
		outputDirectionMessage << "Created output direction " << outputDirection[0]->getDestinationNode() << ", reachable from nodes: ";
		separator = "";
		for (auto &outputNode: outputDirection) {
			outputDirectionMessage << separator << to_string(outputNode->getSourceNode());
			separator = ", ";
		}
		Logger::instance().log(Logger::CREATING_STRUCTURE, outputDirectionMessage.str());
	}

	/// Print information about paths
	separator = " -> ";
	uint64_t totalNumberOfPaths = 0;
	for (const auto &pathsFromInput: paths) {
		Logger::instance().log(Logger::CREATING_STRUCTURE, "Paths starting from input " + to_string(pathsFromInput.first) + ":");
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
		Logger::instance().log(Logger::CREATING_STRUCTURE, "Total number of paths starting from input " + to_string(pathsFromInput.first) + ": " + to_string(numberOfPathsFromInput));
		totalNumberOfPaths += numberOfPathsFromInput;
	}
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Total number of paths: " + to_string(totalNumberOfPaths));
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablished(Connection &connection, Generator &generator) {
	Link *sourceLink = connection.getSourceLink();
	vector<Link *> outputDirection = connection.getOutputDirection();
	vector<Link *> availableOutputLinks = getAvailableLinksToDestination(outputDirection, connection.getRequiredNumberOfFSUs());
	availableOutputLinks = generator.shuffleVector(availableOutputLinks);

	if (!sourceLink->hasFreeNeighboringFSUs(connection.getRequiredNumberOfFSUs()) && !structureIsOneLink()) {
		return CONNECTION_REJECTED;
	}

	if (availableOutputLinks.empty()) {
		return EXTERNAL_BLOCK;
	}

	for (auto outputLink: availableOutputLinks) {
		for (auto path: generator.shuffleVector(getPaths(sourceLink, outputLink))) {
			if (connection.pathHasFreeResources(path, generator)) {
				return CONNECTION_CAN_BE_ESTABLISHED;
			}
		}

		if (GlobalSettings::instance().getSelectedAlgorithm() == GlobalSettings::POINT_TO_POINT) {
			break;
		}
	}
	return INTERNAL_BLOCK;
}

uint64_t Network::getNumberOfGeneratedCallsOfTheLeastActiveClass() {
	uint64_t result = UINT64_MAX;

	for (auto const &trafficClass: erlangTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.establishedConnections + trafficClass.second.callsRejected + trafficClass.second.internalBlocksCount + trafficClass.second.externalBlocksCount;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: engsetTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.establishedConnections + trafficClass.second.callsRejected + trafficClass.second.internalBlocksCount + trafficClass.second.externalBlocksCount;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	for (auto const &trafficClass: pascalTrafficClassStatistics) {
		uint64_t numberOfCalls = trafficClass.second.establishedConnections + trafficClass.second.callsRejected + trafficClass.second.internalBlocksCount + trafficClass.second.externalBlocksCount;
		if (numberOfCalls < result) {
			result = numberOfCalls;
		}
	}

	return result;
}

Link *Network::getRandomInputLink(Generator &generator, uint64_t requiredNumberOfFSUs) {
	vector<Link *> availableInputLinks;
	for (auto inputLink: inputLinks) {
		if (inputLink->hasFreeNeighboringFSUs(requiredNumberOfFSUs)) {
			availableInputLinks.push_back(inputLink);
		}
	}
	if (availableInputLinks.empty()) {
		return generator.getRandomLink(inputLinks);
	}
	return generator.getRandomLink(availableInputLinks);
}

vector<Link *> Network::getAvailableLinksToDestination(vector<Link *> &outputDirection, uint64_t requiredNumberOfFSUs) {
	vector<Link *> availableOutputLinks;
	for (auto outputLink: outputDirection) {
		if (outputLink->hasFreeNeighboringFSUs(requiredNumberOfFSUs)) {
			availableOutputLinks.push_back(outputLink);
		}
	}
	return availableOutputLinks;
}

uint64_t Network::getNumberOfInputLinks() {
	return paths.size();
}

bool Network::linkWasVisited(vector<Link *> &path, Link *linkToCheck) {
	return find(path.begin(), path.end(), linkToCheck) != path.end();
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

vector<Path *> Network::getPaths(Link *inputLink, Link *destinationLink) {
	return paths[inputLink->getSourceNode()][destinationLink->getDestinationNode()];
}

vector<Link *> Network::getRandomOutputDirection(Generator &generator) {
	return generator.getRandomOutputDirection(outputDirections);
}