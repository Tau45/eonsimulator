#include "../../include/network/Structure.h"

Structure::Structure(SimulationSettings &settings) {
    this->settings = &settings;
    createStructure();
}

void Structure::createLink(uint64_t sourceNode, uint64_t destinationNode, uint64_t linkCapacity, bool isInput, bool isOutput) {
    Link *link = new Link(sourceNode, destinationNode, linkCapacity);
    links[sourceNode].push_back(link);

    if (isInput) {
        inputLinks.push_back(link);
    }

    if (isOutput) {
        outputLinks.push_back(link);
    }
}

void Structure::createStructure() {
    logger.log(settings->logsEnabled, 0, Logger::CREATING_STRUCTURE, "Structure creating started...");
    string line;
    vector<vector<int>> nodes;
    ifstream file(settings->structureFileName);

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
            createLink(index, destinationNode, settings->linkCapacity, false, false);
        }
    }

    for (const auto &node: nodes) {
        int index = node[0];
        int numberOfInputs = node[1];

        for (int i = 0; i < numberOfInputs; i++) {
            createLink(++lastNodeIndex, index, settings->linkCapacity, true, false);
        }
    }

    for (const auto &node: nodes) {
        int index = node[0];
        int numberOfOutputs = node[2];

        for (int i = 0; i < numberOfOutputs; i++) {
            createLink(index, ++lastNodeIndex, settings->linkCapacity, false, true);
        }
    }

    printStructureDetails(nodes);

    logger.log(settings->logsEnabled, 0, Logger::CREATING_STRUCTURE, "Structure created");
}

void Structure::printStructureDetails(vector<vector<int>> &nodes) {
    for (const auto &node: nodes) {
        int index = node[0];
        stringstream message;
        message << "Node created: index: " << to_string(index) << ", ";

        uint64_t numberOfInputs = 0;

        for (auto inputLink: inputLinks) {
            if (inputLink->destinationNode == index) {
                numberOfInputs++;
            }
        }

        message << to_string(numberOfInputs) << " inputs";

        if (numberOfInputs > 0) {
            message << " (";
            bool isTheFirstOne = true;
            for (auto inputLink: inputLinks) {
                if (inputLink->destinationNode == index) {
                    if (!isTheFirstOne) {
                        message << " ";
                    }
                    isTheFirstOne = false;
                    message << inputLink->sourceNode;
                }
            }
            message << ")";
        }

        message << ", ";

        uint64_t numberOfOutputs = 0;

        for (auto outputLink: outputLinks) {
            if (outputLink->sourceNode == index) {
                numberOfOutputs++;
            }
        }

        message << to_string(numberOfOutputs) << " outputs";

        if (numberOfOutputs > 0) {
            message << " (";
            bool isTheFirstOne = true;
            for (auto &outputLink: outputLinks) {
                if (outputLink->sourceNode == index) {
                    if (!isTheFirstOne) {
                        message << " ";
                    }
                    isTheFirstOne = false;
                    message << outputLink->destinationNode;
                }
            }
            message << ")";
        }

        message << ", ";

        message << to_string(links[index].size()) << " links to nodes";

        if (!links[index].empty()) {
            message << " (";
            for (int i = 0; i < links[index].size(); i++) {
                message << links[index][i]->destinationNode;
                if (i < links[index].size() - 1) {
                    message << " ";
                }
            }
            message << ")";
        }

        logger.log(settings->logsEnabled, 0, Logger::CREATING_STRUCTURE, message.str());
    }
}

uint64_t Structure::getNumberOfInputLinks() {
    return inputLinks.size();
}

uint64_t Structure::getNumberOfOutputLinks() {
    return outputLinks.size();
}