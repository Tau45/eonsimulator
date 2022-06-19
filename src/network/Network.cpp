#include "../../include/network/Network.h"

Network::Network() {
    for (int i = 0; i < 4; i++) {
        blocksCount[i] = 0;
        internalBlocksCountErlangTraffic[i] = 0;
        externalBlocksCountErlangTraffic[i] = 0;
    }
}

Network::~Network() {
    for (const vector<Link *> &node: links) {
        for (Link *link: node) {
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

void Network::printPath(vector<Link *> &path) {
    cout << path[0]->sourceNode << " -> ";

    for (int i = 0; i < path.size() - 1; i++) {
        cout << path[i]->destinationNode << " -> ";
    }

    cout << path[path.size() - 1]->destinationNode;
}

bool Network::establishConnection(Connection *connection, uint64_t clock, uint64_t trafficClass, uint64_t &callsGenerated) {
    Link *sourceLink = inputLinks[connection->srcLink];
    Link *destinationLink = inputLinks[connection->dstLink];

    if (!linkHasRequiredNumberOfFreeFSUs(sourceLink, connection->numberOfFSUs)) {
//        Logger::getInstance().log(clock, "", "Connection failed, free FSUs not found in source link");
        blocksCount[trafficClass]++;
        return false;
    }

    callsGenerated++;

    if (!linkHasRequiredNumberOfFreeFSUs(destinationLink, connection->numberOfFSUs)) {
//        Logger::getInstance().log(clock, "", "Connection failed due to external blocking");
        externalBlocksCountErlangTraffic[trafficClass]++;
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

            uint64_t resultFirstFSU = 0;
            if (connectionCanBeSetUp(currentPath, connection->numberOfFSUs, resultFirstFSU)) {
                connection->firstFSU = resultFirstFSU;
                connection->path = currentPath;
                reserveResources(connection);
//                Logger::getInstance().log(clock, "", "Connection has been successfully set up using FSUs: " + to_string(connection->firstFSU) + "-" + to_string(connection->firstFSU + connection->numberOfFSUs - 1));
                return true;
            } else {
//                cout << "\t\tConnection could not be set up" << endl;
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
    internalBlocksCountErlangTraffic[trafficClass]++;
    return false;
}


void Network::closeConnection(Connection *connection, uint64_t clock) {
    for (auto &link: connection->path) {
        link->freeFSUs(connection->firstFSU, connection->numberOfFSUs);
    }
    activeConnections.remove(connection);
    delete connection;

//    Logger::getInstance().log(clock, "", "Connection has been closed");
}

void Network::setNumberOfNodes(uint64_t numberOfNodes) {
    this->links.resize(numberOfNodes);
}

void Network::createInputLink(uint64_t sourceNode, uint64_t destinationNode) {
    Link *link = new Link(sourceNode, destinationNode);
    inputLinks.push_back(link);
    links[sourceNode].push_back(link);
}

void Network::createLink(uint64_t sourceNode, uint64_t destinationNode) {
    links[sourceNode].push_back(new Link(sourceNode, destinationNode));
}

void Network::createOutputLink(uint64_t sourceNode, uint64_t destinationNode) {
    Link *link = new Link(sourceNode, destinationNode);
    outputLinks.push_back(link);
    links[sourceNode].push_back(link);
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
