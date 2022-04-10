#include "../../include/network/Network.h"

void Network::setupConnection(vector<Link *> &path, int firstFSU, int numberOfFSUs) const {
    for (auto &link: path) {
        link->reserveFSUs(numberOfFSUs, firstFSU, connectionId);
    }
}

int Network::isNotVisited(vector<Link *> &path, int node) {
    for (auto &link: path)
        if (link->destinationNode == node)
            return 0;
    return 1;
}

bool Network::pathIsExternallyBlocked(vector<Link *> &path, int numberOfFSUs) {
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int FSUIndex = firstFSUIndex; FSUIndex < firstFSUIndex + numberOfFSUs; FSUIndex++) {
            if (!path.at(0)->FSUs[FSUIndex].isFree || !path.at(path.size() - 1)->FSUs[FSUIndex].isFree) {
                freeNeighboringFSUsWereFound = false;
            }
        }

        if (freeNeighboringFSUsWereFound) return false;
    }
    return true;
}

int Network::findAvailableBandwidth(vector<Link *> &path, int numberOfFSUs) {
    // Check for external block
    if (pathIsExternallyBlocked(path, numberOfFSUs)) {
        return -1;
    }

    // Check for free path
    for (int firstFSUIndex = 0; firstFSUIndex < 2 - numberOfFSUs + 1; firstFSUIndex++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int FSUIndex = firstFSUIndex; FSUIndex < firstFSUIndex + numberOfFSUs; FSUIndex++) {
            for (Link *link: path) {
                if (!link->FSUs[FSUIndex].isFree) {
                    freeNeighboringFSUsWereFound = false;
                }
            }
        }

        if (freeNeighboringFSUsWereFound) return firstFSUIndex;
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

void Network::establishConnection(int srcLinkIndex, int dstLinkIndex, int numberOfFSUs) {
    Link *sourceLink = inputLinks[srcLinkIndex];
    int destinationNode = outputLinks[dstLinkIndex]->destinationNode;

    cout << "\nSetting up connection " << connectionId << " between nodes: " << sourceLink->sourceNode << " and "
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

            int firstFSUIndex = findAvailableBandwidth(currentPath, numberOfFSUs);

            if (firstFSUIndex == -1) {
                cout << "\t\tConnection failed due to external blocking" << endl;
            } else if (firstFSUIndex == -2) {
                cout << "\t\tConnection failed due to internal blocking" << endl;
            } else {
                setupConnection(currentPath, firstFSUIndex, numberOfFSUs);
                cout << "\t\tConnection has been successfully set up using FSUs: " << firstFSUIndex << "-"
                     << firstFSUIndex + numberOfFSUs - 1 << endl;
                connectionId++;
                return;
            }
        }

        for (auto &link: links[currentPathLastNode]) {
            if (isNotVisited(currentPath, link->destinationNode)) {
                vector<Link *> newPath(currentPath);
                newPath.push_back(link);
                consideredPaths.push(newPath);
            }
        }
    }

    connectionId++;
}

Network::Network() {
    connectionId = 0;
}
