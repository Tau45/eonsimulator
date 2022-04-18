#include "../../include/network/Network.h"

void Network::setupConnection(Connection *connection) {
    for (auto &link: connection->path) {
        link->reserveFSUs(connection->firstFSU, connection->numberOfFSUs);
    }
    activeConnections.emplace(connection->id, *connection);
}

int Network::linkWasNotVisited(vector<Link *> &path, int node) {
    for (auto &link: path)
        if (link->destinationNode == node)
            return 0;
    return 1;
}

bool Network::pathIsExternallyBlocked(vector<Link *> &path, int numberOfFSUs) {
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int FSUIndex = firstFSUIndex; FSUIndex < firstFSUIndex + numberOfFSUs; FSUIndex++) {
            if (path.at(0)->FSUIsBusy(FSUIndex) || path.at(path.size() - 1)->FSUIsBusy(FSUIndex)) {
                freeNeighboringFSUsWereFound = false;
            }
        }

        if (freeNeighboringFSUsWereFound) return false;
    }
    return true;
}

int Network::lookForAvailableBandwidthInPath(vector<Link *> &path, uint64_t numberOfFSUs) {
    // Check for external block
    if (pathIsExternallyBlocked(path, numberOfFSUs)) {
        return -1;
    }

    // Check for free path
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int FSUIndex = firstFSUIndex; FSUIndex < firstFSUIndex + numberOfFSUs; FSUIndex++) {
            for (Link *link: path) {
                if (link->FSUIsBusy(FSUIndex)) {
                    freeNeighboringFSUsWereFound = false;
                }
            }
        }

        if (freeNeighboringFSUsWereFound)
            return firstFSUIndex;
    }

    // No path was found due to internal blocking
    return -2;
}

void Network::printPath(vector<Link *> &path) {
    cout << path[0]->sourceNode << " -> ";

    for (int i = 0; i < path.size() - 1; i++)
        cout << path[i]->destinationNode << " -> ";

    cout << path[path.size() - 1]->destinationNode;
}

void Network::tryToEstablishConnection(Connection *connection) {
    Link *sourceLink = inputLinks[connection->srcLink];
    int destinationNode = outputLinks[connection->dstLink]->destinationNode;

    cout << "\nSetting up connection " << connection->id << " between nodes: " << sourceLink->sourceNode << " and "
         << destinationNode << "...\n";

    vector<Link *> currentPath = {sourceLink};

    queue<vector<Link *>> consideredPaths;
    consideredPaths.push(currentPath);

    while (!consideredPaths.empty()) {
        currentPath = consideredPaths.front();
        consideredPaths.pop();

        int currentPathLastNode = currentPath[currentPath.size() - 1]->destinationNode;

        if (currentPathLastNode == destinationNode) {
            cout << "\tConsidering currentPath: ";
            printPath(currentPath);
            cout << ":\n";

            connection->firstFSU = lookForAvailableBandwidthInPath(currentPath, connection->numberOfFSUs);

            if (connection->firstFSU == -1) {
                cout << "\t\tConnection failed due to external blocking" << endl;
            } else if (connection->firstFSU == -2) {
                cout << "\t\tConnection failed due to internal blocking" << endl;
            } else {
                connection->path = currentPath;
                setupConnection(connection);
                cout << "\t\tConnection id:" << connection->id << " has been successfully set up using FSUs: "
                << connection->firstFSU << "-" << connection->firstFSU + connection->numberOfFSUs - 1 << endl;
                break;
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
}

Network::Network() = default;

void Network::closeConnection(uint64_t connectionToCloseId) {
    Connection connection = activeConnections.at(connectionToCloseId);
    activeConnections.erase(connectionToCloseId);

    for (auto &link: connection.path) {
        link->freeFSUs(connection.firstFSU, connection.numberOfFSUs);
    }

    cout << "\nConnection id:" << connectionToCloseId << " has been closed\n";
}
