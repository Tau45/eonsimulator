#include "../../include/network/Structure.h"

void Structure::createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity, bool isInput, bool isOutput) {
	Link *link = new Link(sourceNode, destinationNode, linkCapacity, isInput, isOutput);
	links[sourceNode].push_back(link);

	if (isInput) {
		inputLinks.push_back(link);
	}

	if (isOutput) {
		outputLinks.push_back(link);
	}
}

void Structure::buildNetworkStructure() {
	Logger::instance().log(0, Logger::CREATING_STRUCTURE, "Structure creating started...");
	string line;
	vector<vector<int>> nodes;
	ifstream file(SimulationSettings::instance().getStructureFileName());

	while (getline(file, line)) {
		if (line.find_first_of("0123456789") == string::npos) {
			continue;
		}

		int itmp;
		vector<int> tmp;
		stringstream ss(line);

		while (ss >> itmp) {
			string tmpstr;
			tmp.push_back(itmp);
			if (!getline(ss, tmpstr, ';'))
				break;
		}
		nodes.push_back(tmp);
	}

	file.close();

	uint64_t lastNodeIndex = nodes[0][0];
	for (const auto &node: nodes) {
		if (node[0] > lastNodeIndex) {
			lastNodeIndex = node[0];
		}
	}

	for (const auto &node: nodes) {
		int index = node[0];
		vector<int> linkedNodes;

		for (int i = 3; i < node.size(); i++) {
			linkedNodes.push_back(node[i]);
		}

		for (int destinationNode: linkedNodes) {
			createLink(index, destinationNode, SimulationSettings::instance().getLinkCapacity(), false, false);
		}
	}

	for (const auto &node: nodes) {
		int index = node[0];
		int numberOfInputs = node[1];

		for (int i = 0; i < numberOfInputs; i++) {
			createLink(++lastNodeIndex, index, SimulationSettings::instance().getLinkCapacity(), true, false);
		}
	}

	for (const auto &node: nodes) {
		int index = node[0];
		int numberOfOutputs = node[2];

		for (int i = 0; i < numberOfOutputs; i++) {
			createLink(index, ++lastNodeIndex, SimulationSettings::instance().getLinkCapacity(), false, true);
		}
	}

	printStructureDetails(nodes);

	Logger::instance().log(0, Logger::CREATING_STRUCTURE, "Structure created");
}

void Structure::printStructureDetails(vector<vector<int>> &nodes) {
	for (const auto &node: nodes) {
		int index = node[0];
		uint64_t numberOfInputs = 0;
		uint64_t numberOfOutputs = 0;
		stringstream message;
		message << "Node created: index: " << to_string(index) << ", ";

		/// Print information about input links
		for (auto inputLink: inputLinks) {
			if (inputLink->getDestinationNode() == index) {
				numberOfInputs++;
			}
		}

		message << to_string(numberOfInputs) << " inputs";

		if (numberOfInputs > 0) {
			message << " (";
			bool listSeparatorNeedsToBePrinted = false;
			for (auto inputLink: inputLinks) {
				if (inputLink->getDestinationNode() == index) {
					if (listSeparatorNeedsToBePrinted) {
						message << " ";
					}
					listSeparatorNeedsToBePrinted = true;
					message << inputLink->getSourceNode();
				}
			}
			message << ")";
		}

		/// Print information about output links
		for (auto outputLink: outputLinks) {
			if (outputLink->getSourceNode() == index) {
				numberOfOutputs++;
			}
		}

		message << ", " << to_string(numberOfOutputs) << " outputs";

		if (numberOfOutputs > 0) {
			message << " (";
			bool listSeparatorNeedsToBePrinted = false;
			for (auto &outputLink: outputLinks) {
				if (outputLink->getSourceNode() == index) {
					if (listSeparatorNeedsToBePrinted) {
						message << " ";
					}
					listSeparatorNeedsToBePrinted = true;
					message << outputLink->getDestinationNode();
				}
			}
			message << ")";
		}

		/// Print information about links to other nodes
		uint64_t numberOfInternalLinks = 0;
		for (int i = 0; i < links[index].size(); i++) {
			if (!links[index][i]->isOutputLink()) {
				numberOfInternalLinks++;
			}
		}
		message << ", " << to_string(numberOfInternalLinks) << " links to nodes";

		if (numberOfInternalLinks > 0) {
			message << " (";
			for (int i = 0; i < links[index].size(); i++) {
				if (!links[index][i]->isOutputLink()) {
					message << links[index][i]->getDestinationNode();
					if (i < links[index].size() - 1) {
						message << " ";
					}
				}
			}
			message << ")";
		}

		Logger::instance().log(0, Logger::CREATING_STRUCTURE, message.str());
	}
}

uint64_t Structure::getNumberOfInputLinks() {
	return inputLinks.size();
}

uint64_t Structure::getNumberOfOutputLinks() {
	return outputLinks.size();
}

bool Structure::checkInputToOutputAvailability(uint64_t sourceLinkIndex, uint64_t destinationLinkIndex) {
	queue<vector<Link *>> consideredPaths;
	consideredPaths.push({inputLinks[sourceLinkIndex]});

	while (!consideredPaths.empty()) {
		vector<Link *> currentPath = consideredPaths.front();
		consideredPaths.pop();
		uint64_t currentPathLastNode = currentPath[currentPath.size() - 1]->getDestinationNode();

		if (currentPathLastNode == outputLinks[destinationLinkIndex]->getDestinationNode()) {
			return true;
		}

		for (auto &link: links[currentPathLastNode]) {
			if (linkWasNotVisited(currentPath, link->getDestinationNode())) {
				vector<Link *> newPath(currentPath);
				newPath.push_back(link);
				consideredPaths.push(newPath);
			}
		}
	}

	return false;
}

bool Structure::linkWasNotVisited(vector<Link *> &path, uint64_t node) {
	for (auto &link: path) {
		if (link->getDestinationNode() == node) {
			return false;
		}
	}

	return true;
}

bool Structure::isValid() {
	return everyOutputNodeIsAvailableFromEveryInputNode();
}

bool Structure::everyOutputNodeIsAvailableFromEveryInputNode() {
	Logger::instance().log(0, Logger::STRUCTURE_VALIDATION, "Structure validation started...");
	for (uint64_t i = 0; i < inputLinks.size(); i++) {
		for (uint64_t j = 0; j < outputLinks.size(); j++) {
			if (!checkInputToOutputAvailability(i, j)) {
				Logger::instance().log(0, Logger::ERROR, "Structure is not valid. Output " + to_string(outputLinks[j]->getDestinationNode()) + " is not reachable from input " + to_string(inputLinks[i]->getSourceNode()));
				return false;
			}
		}
	}
	Logger::instance().log(0, Logger::STRUCTURE_VALIDATION, "Structure is valid");
	return true;
}

Structure::~Structure() {
	for (const auto &node: links) {
		for (auto &link: node.second) {
			delete link;
		}
	}
}