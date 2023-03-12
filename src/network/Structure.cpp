#include "../../include/network/Structure.h"

vector<uint64_t> Structure::parseLine(const string &line) {
	vector<uint64_t> result;
	stringstream ss(line);
	string item;

	while (getline(ss, item, ';') && result.size() < 3) {
		result.push_back(stoull(item));
	}

	return result;
}

void Structure::createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t outputDirectionIndex) {
	Link *link = new Link(sourceNode, destinationNode, outputDirectionIndex);
	links[sourceNode].push_back(link);
}

void Structure::buildNetworkStructure() {
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Structure creating started...");
	string line;
	ifstream file(GlobalSettings::instance().getStructureFileName());

	while (getline(file, line)) {
		vector<uint64_t> linkData = parseLine(line);
		createLink(linkData[0], linkData[1], linkData[2]);
	}

	setInputOutputLinks();

	file.close();
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Structure created");
}

void Structure::setInputOutputLinks() {
	vector<uint64_t> inputNodes;
	vector<uint64_t> outputNodes;

	for (const auto &node: links) {
		for (const auto &link: node.second) {
			inputNodes.push_back(link->getSourceNode());
			outputNodes.push_back(link->getDestinationNode());
		}
	}

	vector<uint64_t> sourceNodes;
	vector<uint64_t> destinationNodes;

	for (auto value: inputNodes) {
		if (!count(outputNodes.begin(), outputNodes.end(), value)) {
			sourceNodes.push_back(value);
		}
	}

	for (auto value: outputNodes) {
		if (!count(inputNodes.begin(), inputNodes.end(), value)) {
			destinationNodes.push_back(value);
		}
	}

	for (const auto &node: links) {
		for (const auto &link: node.second) {
			if (count(sourceNodes.begin(), sourceNodes.end(), link->getSourceNode())) {
				link->setAsInput();
				inputLinks.push_back(link);
			}
			if (count(destinationNodes.begin(), destinationNodes.end(), link->getDestinationNode())) {
				link->setAsOutput();
				outputDirections[link->getOutputDirectionIndex()].push_back(link);
			}
		}
	}
}

void Structure::printStructureDetails() {
	string separator;

	/// Print information about input nodes
	stringstream inputNodesMessage;
	inputNodesMessage << "Input nodes created: ";
	for (auto &inputLink: inputLinks) {
		inputNodesMessage << separator << to_string(inputLink->getSourceNode());
		separator = ", ";
	}
	Logger::instance().log(Logger::CREATING_STRUCTURE, inputNodesMessage.str());

	set<uint64_t> internalNodeIndexes;
	for (const auto &node: links) {
		for (const auto &link: node.second) {
			if (!link->isInputLink() && !link->isOutputLink()) {
				internalNodeIndexes.insert(link->getSourceNode());
				internalNodeIndexes.insert(link->getDestinationNode());
			}
		}
	}

	/// Print information about internal nodes
	for (const auto &index: internalNodeIndexes) {
		uint64_t numberOfInputs = 0;
		for (auto inputLink: inputLinks) {
			if (inputLink->getDestinationNode() == index) {
				numberOfInputs++;
			}
		}

		uint64_t numberOfOutputs = 0;
		for (const auto &outputDirection: outputDirections) {
			for (auto outputLink: outputDirection.second)
				if (outputLink->getSourceNode() == index) {
					numberOfOutputs++;
				}
		}

		uint64_t numberOfLinksToOtherNodes = 0;
		for (auto &i: links[index]) {
			if (!i->isOutputLink()) {
				numberOfLinksToOtherNodes++;
			}
		}

		stringstream message;
		message << "Node " << to_string(index) << " created: ";

		/// Print information about input nodes linked to node
		if (numberOfInputs > 0) {
			message << to_string(numberOfInputs) << " inputs (";

			separator = "";
			for (auto inputLink: inputLinks) {
				if (inputLink->getDestinationNode() == index) {
					message << separator << inputLink->getSourceNode();
					separator = ", ";
				}
			}
			message << ")";
		}

		/// Print information about output nodes from this node
		if (numberOfOutputs > 0) {
			if (numberOfInputs > 0) {
				message << separator;
			}
			message << to_string(numberOfOutputs) << " outputs (";

			separator = "";
			for (const auto &outputDirection: outputDirections) {
				for (auto outputLink: outputDirection.second)
					if (outputLink->getSourceNode() == index) {
						message << separator << outputLink->getDestinationNode();
						separator = ", ";
					}
			}
			message << ")";
		}

		/// Print information about links to other nodes
		if (numberOfLinksToOtherNodes > 0) {
			if (numberOfInputs > 0 || numberOfOutputs > 0) {
				message << separator;
			}
			message << to_string(numberOfLinksToOtherNodes) << " links to nodes (";

			separator = "";
			for (auto &link: links[index]) {
				if (!link->isOutputLink()) {
					message << separator << link->getDestinationNode();
					separator = ", ";
				}
			}
			message << ")";
		}
		Logger::instance().log(Logger::CREATING_STRUCTURE, message.str());
	}

	/// Print information about output nodes
	stringstream outputNodesMessage;
	outputNodesMessage << "Output nodes created: ";

	separator = "";
	for (const auto &outputDirection: outputDirections) {
		for (auto outputLink: outputDirection.second) {
			outputNodesMessage << separator << to_string(outputLink->getDestinationNode());
			separator = ", ";
		}
	}
	Logger::instance().log(Logger::CREATING_STRUCTURE, outputNodesMessage.str());

	/// Print information about output directions
	for (const auto &outputDirection: outputDirections) {
		stringstream outputDirectionMessage;
		separator = "";
		outputDirectionMessage << "Direction " << outputDirection.first << " created (";
		for (const auto &outputLink: outputDirection.second) {
			outputDirectionMessage << separator << outputLink->getDestinationNode();
			separator = ", ";
		}
		outputDirectionMessage << ")";
		Logger::instance().log(Logger::CREATING_STRUCTURE, outputDirectionMessage.str());
	}
}

Link *Structure::getInputLink(uint64_t inputLinkIndex) {
	return inputLinks[inputLinkIndex];
}

vector<Link *> Structure::getAvailableLinksInOutputDirection(uint64_t outputDirectionIndex, uint64_t requiredNumberOfFSUs) {
	vector<Link *> availableOutputLinks;
	for (auto outputLink: outputDirections[outputDirectionIndex]) {
		if (outputLink->hasFreeNeighboringFSUs(requiredNumberOfFSUs)) {
			availableOutputLinks.push_back(outputLink);
		}
	}
	return availableOutputLinks;
}

vector<Link *> Structure::getNextHops(Link *sourceLink) {
	return links[sourceLink->getDestinationNode()];
}

uint64_t Structure::getNumberOfInputLinks() {
	return inputLinks.size();
}

uint64_t Structure::getNumberOfOutputDirections() {
	return outputDirections.size();
}

bool Structure::checkInputToOutputAvailability(Link *sourceLink, Link *destinationLink) {
	queue<vector<Link *>> consideredPaths;
	consideredPaths.push({sourceLink});

	while (!consideredPaths.empty()) {
		vector<Link *> currentPath = consideredPaths.front();
		consideredPaths.pop();

		if (currentPath.back() == destinationLink) {
			return true;
		}

		for (auto &link: links[currentPath.back()->getDestinationNode()]) {
			if (linkWasNotVisited(currentPath, link)) {
				vector<Link *> newPath(currentPath);
				newPath.push_back(link);
				consideredPaths.push(newPath);
			}
		}
	}

	return false;
}

bool Structure::linkWasNotVisited(vector<Link *> &path, Link *linkToCheck) {
	return !ranges::any_of(path.cbegin(), path.cend(), [linkToCheck](Link *link) { return link == linkToCheck; });
}

bool Structure::isValid() {
	return everyOutputNodeIsAvailableFromEveryInputNode()
		   && atLeastOneInputExists()
		   && atLeastOneOutputDirectionExists();
}

bool Structure::everyOutputNodeIsAvailableFromEveryInputNode() {
	Logger::instance().log(Logger::STRUCTURE_VALIDATION, "Structure validation started...");
	for (auto &inputLink: inputLinks) {
		for (const auto &outputDirection: outputDirections) {
			for (auto outputLink: outputDirection.second) {
				if (!checkInputToOutputAvailability(inputLink, outputLink)) {
					Logger::instance().log(Logger::ERROR, "Structure is not valid. Output " + to_string(outputLink->getDestinationNode()) + " is not reachable from input " + to_string(inputLink->getSourceNode()));
					return false;
				}
			}
		}
	}
	Logger::instance().log(Logger::STRUCTURE_VALIDATION, "Structure is valid");
	return true;
}

bool Structure::atLeastOneInputExists() {
	if (inputLinks.empty()) {
		Logger::instance().log(Logger::ERROR, "Structure is not valid. No input links found");
		return false;
	}
	return true;
}

bool Structure::atLeastOneOutputDirectionExists() {
	if (outputDirections.empty()) {
		Logger::instance().log(Logger::ERROR, "Structure is not valid. No output links found");
		return false;
	}
	return true;
}

bool Structure::structureIsOneLink() {
	return links.size() == 1;
}

Structure::Structure() {
	buildNetworkStructure();
}

Structure::~Structure() {
	for (const auto &node: links) {
		for (auto &link: node.second) {
			delete link;
		}
	}
}