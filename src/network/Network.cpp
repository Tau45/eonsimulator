#include "../../include/network/Network.h"

Network::Network() {
    internalBlocksCount = 0;
    externalBlocksCount = 0;
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

int Network::linkWasNotVisited(vector<Link *> &path, int node) {
    for (auto &link: path) {
        if (link->destinationNode == node) {
            return 0;
        }
    }

    return 1;
}

bool Network::pathIsExternallyBlocked(vector<Link *> &path, uint64_t numberOfFSUs) {
    //todo: replace 2 with number of FSUs
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int i = firstFSUIndex; i < firstFSUIndex + numberOfFSUs; i++) {
            if (path.at(0)->FSUIsBusy(i) || path.at(path.size() - 1)->FSUIsBusy(i)) {
                freeNeighboringFSUsWereFound = false;
            }
        }

        if (freeNeighboringFSUsWereFound) {
            return false;
        }
    }
    return true;
}

bool Network::connectionCanBeSetUp(vector<Link *> &path, uint64_t numberOfFSUs, uint64_t &resultFirstFSU) {
    // Check for free path
    //todo: replace 2 with number of FSUs
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int i = firstFSUIndex; i < firstFSUIndex + numberOfFSUs; i++) {
            for (Link *link: path) {
                if (link->FSUIsBusy(i)) {
                    freeNeighboringFSUsWereFound = false;
                    firstFSUIndex = i;
                    break;
                }
            }
        }

        if (freeNeighboringFSUsWereFound) {
            resultFirstFSU = firstFSUIndex;
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

bool Network::establishConnection(Connection *connection, uint64_t clock) {
    Link *sourceLink = inputLinks[connection->srcLink];
    uint64_t destinationNode = outputLinks[connection->dstLink]->destinationNode;

    cout << "\nSetting up connection between nodes: " << sourceLink->sourceNode << " and "
         << destinationNode << "...\n";

    vector<Link *> currentPath = {sourceLink};

    queue<vector<Link *>> consideredPaths;
    consideredPaths.push(currentPath);

    uint16_t counterOfAttempts = 0;
    //todo: set maxCounterOfAttempts
    uint16_t maxCounterOfAttempts = 5;

    while (!consideredPaths.empty()) {
        currentPath = consideredPaths.front();
        consideredPaths.pop();

        int64_t currentPathLastNode = currentPath[currentPath.size() - 1]->destinationNode;

        if (currentPathLastNode == destinationNode) {
            if (pathIsExternallyBlocked(currentPath, connection->numberOfFSUs)) {
                cout << "\tConnection failed due to external blocking" << endl;
                externalBlocksCount++;
                return false;
            }

            if (++counterOfAttempts == maxCounterOfAttempts) {
                cout << "\t\tThe number of attempts has been exceeded" << endl;
                cout << "\t\tConnection failed due to internal blocking" << endl;
                internalBlocksCount++;
                return false;
            }

            cout << "\tConsidering currentPath: ";
            printPath(currentPath);
            cout << ":\n";

            uint64_t resultFirstFSU = 0;
            if (connectionCanBeSetUp(currentPath, connection->numberOfFSUs, resultFirstFSU)) {
                connection->firstFSU = resultFirstFSU;
                connection->path = currentPath;
                reserveResources(connection);
                Logger::getInstance().log(clock, "", "Connection has been successfully set up using FSUs: " + to_string(connection->firstFSU) + "-" + to_string(connection->firstFSU + connection->numberOfFSUs - 1));
                return true;
            } else {
                cout << "\t\tConnection could not be set up" << endl;
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

    cout << "\t\tConnection failed due to internal blocking" << endl;
    internalBlocksCount++;
    return false;
}


void Network::closeConnection(Connection *connection, uint64_t clock) {
    for (auto &link: connection->path) {
        link->freeFSUs(connection->firstFSU, connection->numberOfFSUs);
    }
    activeConnections.remove(connection);
    delete connection;

    Logger::getInstance().log(clock, "", "Connection has been closed");
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