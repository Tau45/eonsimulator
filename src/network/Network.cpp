#include "../../include/network/Network.h"

Network::~Network() {
    for (auto const &node: links) {
        for (Link *link: node.second) {
            delete link;
        }
    }

    for (Connection *connection: activeConnections) {
        delete connection;
    }
}

void Network::reserveResources(Connection *connection) {
    for (auto &link: connection->path) {
        link->reserveFSUs(connection->firstFSU, connection->numberOfFSUs);
    }
    activeConnections.push_back(connection);
}

int Network::linkWasNotVisited(vector<Link *> &path, uint64_t node) {
    for (auto &link: path) {
        if (link->destinationNode == node) {
            return 0;
        }
    }

    return 1;
}

bool Network::connectionCanBeSetUp(vector<Link *> &path, uint64_t requiredNumberOfFSUs, uint64_t &resultFirstFSU) {
    uint64_t numberOfFSUs = path[0]->getNumberOfFSUs();

    for (int i = 0; i <= numberOfFSUs - requiredNumberOfFSUs; i++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int j = i; j < i + requiredNumberOfFSUs; j++) {
            for (Link *link: path) {
                if (link->FSUIsOccupied(j)) {
                    freeNeighboringFSUsWereFound = false;
                    i = j;
                    break;
                }
            }
        }

        if (freeNeighboringFSUsWereFound) {
            resultFirstFSU = i;
            return true;
        }
    }
    return false;
}

bool Network::establishConnection(Connection *connection, TrafficClassStatistics &statistics) {
    Link *sourceLink = inputLinks[connection->sourceLinkIndex];
    Link *destinationLink = inputLinks[connection->destinationLinkIndex];

    if (!linkHasRequiredNumberOfFreeFSUs(sourceLink, connection->numberOfFSUs) && sourceLink != destinationLink) {
        cout << "Connection failed, free FSUs not found in source link" << endl;
        return false;
    }

    statistics.callsGenerated++;

    if (!linkHasRequiredNumberOfFreeFSUs(destinationLink, connection->numberOfFSUs)) {
        cout << "Connection failed due to external blocking" << endl;
        statistics.externalBlocksCount++;
        return false;
    }

    uint64_t destinationNode = destinationLink->destinationNode;

//    cout << "Setting up connection between nodes: " << sourceLink->sourceNode << " and " << destinationNode << "...\n";

    queue<vector<Link *>> consideredPaths;
    consideredPaths.push({sourceLink});

    while (!consideredPaths.empty()) {
        vector<Link *> currentPath = consideredPaths.front();
        consideredPaths.pop();

        uint64_t currentPathLastNode = currentPath[currentPath.size() - 1]->destinationNode;

        if (currentPathLastNode == destinationNode) {
//            cout << "\tConsidering currentPath: ";
//            printPath(currentPath);
//            cout << ":\n";

            if (connectionCanBeSetUp(currentPath, connection->numberOfFSUs, connection->firstFSU)) {
                connection->path = currentPath;
                reserveResources(connection);
                cout << "Connection has been successfully set up using FSUs: " << to_string(connection->firstFSU) << "-" << to_string(connection->firstFSU + connection->numberOfFSUs - 1) << endl;
                return true;
            }
        }

        for (auto &link: links[currentPathLastNode]) {
            if (linkWasNotVisited(currentPath, link->destinationNode)) {
                vector<Link *> newPath(currentPath);
                newPath.push_back(link);
                consideredPaths.push(newPath);
            }
        }
    }

//    cout << "\t\tConnection failed due to internal blocking" << endl;
    statistics.internalBlocksCount++;
    return false;
}


void Network::closeConnection(Connection *connection) {
    for (auto &link: connection->path) {
        link->freeFSUs(connection->firstFSU, connection->numberOfFSUs);
    }
    activeConnections.remove(connection);
    cout << "Connection closed: Freeing FSUs: " << to_string(connection->firstFSU) << "-" << to_string(connection->firstFSU + connection->numberOfFSUs - 1) << endl;
    delete connection;
}

void Network::createLink(uint64_t sourceNode, uint64_t destinationNode, bool isInput, bool isOutput) {
    Link *link = new Link(destinationNode);
    links[sourceNode].push_back(link);

    if (isInput) {
        inputLinks.push_back(link);
    }

    if (isOutput) {
        outputLinks.push_back(link);
    }
}

uint64_t Network::getNumberOfInputLinks() {
    return inputLinks.size();
}

uint64_t Network::getNumberOfOutputLinks() {
    return outputLinks.size();
}

bool Network::linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs) {
    for (int i = 0; i <= link->getNumberOfFSUs() - requiredNumberOfFSUs; i++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int j = i; j < i + requiredNumberOfFSUs; j++) {
            if (link->FSUIsOccupied(j)) {
                freeNeighboringFSUsWereFound = false;
                i = j;
                break;
            }
        }

        if (freeNeighboringFSUsWereFound) {
            return true;
        }
    }
    return false;
}

uint64_t Network::getNumberOfGeneratedCallsOfTheLeastActiveClass() {
    uint64_t result = UINT64_MAX;

    for (auto const &trafficClass: erlangTrafficClasses) {
        if (trafficClass.second.callsGenerated < result) {
            result = trafficClass.second.callsGenerated;
        }
    }

    for (auto const &trafficClass: engsetTrafficClasses) {
        if (trafficClass.second.callsGenerated < result) {
            result = trafficClass.second.callsGenerated;
        }
    }

    for (auto const &trafficClass: pascalTrafficClasses) {
        if (trafficClass.second.callsGenerated < result) {
            result = trafficClass.second.callsGenerated;
        }
    }

    return result;
}