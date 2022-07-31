#include "../../include/network/Structure.h"

void Structure::createLink(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput) {
    Link *link = new Link(sourceNode, destinationNode);
    links[sourceNode].push_back(link);

    if (isInput) {
        inputLinks.push_back(link);
    }

    if (isOutput) {
        outputLinks.push_back(link);
    }
}

bool Structure::createStructure(string structureFileName) {
    string line;
    vector<vector<int>> nodes;
    ifstream file(structureFileName);

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
            createLink(index, destinationNode, false, false);
        }
    }

    for (const auto &node: nodes) {
        int index = node[0];
        int numberOfInputs = node[1];

        for (int i = 0; i < numberOfInputs; i++) {
            createLink(++lastNodeIndex, index, true, false);
        }
    }

    for (const auto &node: nodes) {
        int index = node[0];
        int numberOfOutputs = node[2];

        for (int i = 0; i < numberOfOutputs; i++) {
            createLink(index, ++lastNodeIndex, false, true);
        }
    }

    // wyswietlanie
    for (const auto &node: nodes) {
        int index = node[0];
        stringstream message;
        message << "Node created: index: " << to_string(index) << ", ";

        uint64_t numberOfInputs = 0;

        for (auto inputLink : inputLinks) {
            if (inputLink->destinationNode == index) {
                numberOfInputs++;
            }
        }

        message << "inputs: " << to_string(numberOfInputs);

        if (numberOfInputs > 0) {
            message << " (";
            bool isTheFirstOne = true;
            for (auto inputLink : inputLinks) {
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

        for (auto outputLink : outputLinks) {
            if (outputLink->sourceNode == index) {
                numberOfOutputs++;
            }
        }

        message << "outputs: " + to_string(numberOfOutputs);

        if (numberOfOutputs > 0) {
            message << " (";
            bool isTheFirstOne = true;
            for (int i = 0; i < outputLinks.size(); i++) {
                if (outputLinks[i]->sourceNode == index) {
                    if (!isTheFirstOne) {
                        message << " ";
                    }
                    isTheFirstOne = false;
                    message << outputLinks[i]->destinationNode;
                }
            }
            message << ")";
        }

        message << ", ";

        message << "links to nodes: " + to_string(links[index].size());

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


        Logger::getInstance().log(0, Logger::CREATING_STRUCTURE, message.str());
    }
}

uint64_t Structure::getNumberOfInputLinks() {
    return inputLinks.size();
}

uint64_t Structure::getNumberOfOutputLinks() {
    return outputLinks.size();
}