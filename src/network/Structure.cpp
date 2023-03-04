#include "../../include/network/Structure.h"

vector<uint64_t> Structure::parseLine(const string &line) {
	vector<uint64_t> result;
	stringstream ss(line);
	string item;

	while (getline(ss, item, ';') && result.size() < 2) {
		result.push_back(stoull(item));
	}

	return result;
}

void Structure::createLink(uint64_t sourceNode, uint64_t destinationNode) {
	Link *link = new Link(sourceNode, destinationNode);
	links[sourceNode].push_back(link);
}

void Structure::buildNetworkStructure() {
	Logger::instance().log(Logger::CREATING_STRUCTURE, "Structure creating started...");
	string line;
	ifstream file(SimulationSettings::instance().getStructureFileName());

	while (getline(file, line)) {
		vector<uint64_t> linkData = parseLine(line);
		createLink(linkData[0], linkData[1]);
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
			if (std::count(sourceNodes.begin(), sourceNodes.end(), link->getSourceNode())) {
				link->setAsInput();
				inputLinks.push_back(link);
			}
			if (std::count(destinationNodes.begin(), destinationNodes.end(), link->getDestinationNode())) {
				link->setAsOutput();
				outputLinks.push_back(link);
			}
		}
	}
}

void Structure::printStructureDetails() {
	stringstream inputNodesMessage;
	inputNodesMessage << "Input nodes created: ";
	for (uint64_t i = 0; i < inputLinks.size() - 1; i++) {
		inputNodesMessage << to_string(inputLinks[i]->getSourceNode()) << ", ";
	}
	inputNodesMessage << to_string(inputLinks[inputLinks.size() - 1]->getSourceNode());
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

	for (const auto &index: internalNodeIndexes) {
		uint64_t numberOfInputs = 0;
		for (auto inputLink: inputLinks) {
			if (inputLink->getDestinationNode() == index) {
				numberOfInputs++;
			}
		}

		uint64_t numberOfOutputs = 0;
		for (auto outputLink: outputLinks) {
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

		/// Print information about input links
		if (numberOfInputs > 0) {
			message << to_string(numberOfInputs) << " inputs";

			message << " (";
			bool listSeparatorNeedsToBePrinted = false;
			for (auto inputLink: inputLinks) {
				if (inputLink->getDestinationNode() == index) {
					if (listSeparatorNeedsToBePrinted) {
						message << ", ";
					}
					listSeparatorNeedsToBePrinted = true;
					message << inputLink->getSourceNode();
				}
			}
			message << ")";
		}

		/// Print information about output links
		if (numberOfOutputs > 0) {
			if (numberOfInputs > 0) {
				message << ", ";
			}
			message << to_string(numberOfOutputs) << " outputs";

			message << " (";
			bool listSeparatorNeedsToBePrinted = false;
			for (auto &outputLink: outputLinks) {
				if (outputLink->getSourceNode() == index) {
					if (listSeparatorNeedsToBePrinted) {
						message << ", ";
					}
					listSeparatorNeedsToBePrinted = true;
					message << outputLink->getDestinationNode();
				}
			}
			message << ")";
		}

		/// Print information about links to other nodes
		if (numberOfLinksToOtherNodes > 0) {
			if (numberOfInputs > 0 || numberOfOutputs > 0) {
				message << ", ";
			}
			message << to_string(numberOfLinksToOtherNodes) << " links to nodes";

			message << " (";
			for (int i = 0; i < links[index].size(); i++) {
				if (!links[index][i]->isOutputLink()) {
					message << links[index][i]->getDestinationNode();
					if (i < links[index].size() - 1) {
						message << ", ";
					}
				}
			}
			message << ")";
		}
		Logger::instance().log(Logger::CREATING_STRUCTURE, message.str());
	}

	stringstream outputNodesMessage;
	outputNodesMessage << "Output nodes created: ";
	for (uint64_t i = 0; i < outputLinks.size() - 1; i++) {
		outputNodesMessage << to_string(outputLinks[i]->getDestinationNode()) << ", ";
	}
	outputNodesMessage << to_string(outputLinks[outputLinks.size() - 1]->getDestinationNode());
	Logger::instance().log(Logger::CREATING_STRUCTURE, outputNodesMessage.str());
}

uint64_t Structure::getNumberOfInputLinks() {
	return inputLinks.size();
}

uint64_t Structure::getNumberOfOutputLinks() {
	return outputLinks.size();
}

bool Structure::checkInputToOutputAvailability(Link* sourceLink, Link* destinationLink) {
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
	return everyOutputNodeIsAvailableFromEveryInputNode();
}

bool Structure::everyOutputNodeIsAvailableFromEveryInputNode() {
	Logger::instance().log(Logger::STRUCTURE_VALIDATION, "Structure validation started...");
	for (auto & inputLink : inputLinks) {
		for (auto & outputLink : outputLinks) {
			if (!checkInputToOutputAvailability(inputLink, outputLink)) {
				Logger::instance().log(Logger::ERROR, "Structure is not valid. Output " + to_string(outputLink->getDestinationNode()) + " is not reachable from input " + to_string(inputLink->getSourceNode()));
				return false;
			}
		}
	}
	Logger::instance().log(Logger::STRUCTURE_VALIDATION, "Structure is valid");
	return true;
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