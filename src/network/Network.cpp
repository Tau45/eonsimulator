#include "../../include/network/Network.h"

Network::Network(SimulationSettings &settings) : Structure(settings) {}

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
    assert(!connection->path.empty());
    for (auto &link: connection->path) {
        link->reserveFSUs(connection->firstFSU, connection->requiredNumberOfFSUs);
    }
    activeConnections.push_back(connection);
}

bool Network::linkWasNotVisited(vector<Link *> &path, uint64_t node) {
    for (auto &link: path) {
        if (link->destinationNode == node) {
            return false;
        }
    }

    return true;
}

bool Network::pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, uint64_t requiredNumberOfFSUs, uint64_t &resultFirstFSU) {
    for (int i = 0; i <= settings->linkCapacity - requiredNumberOfFSUs; i++) {
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

Network::ESTABLISH_CONNECTION_RESULT Network::establishConnection(double clock, Connection *connection) {
    Link *sourceLink = inputLinks[connection->sourceLinkIndex];
    Link *destinationLink = outputLinks[connection->destinationLinkIndex];

    logger.log(settings->logsEnabled, clock, Logger::CONNECTION_SETUP, "Setting up connection between input: " + to_string(sourceLink->sourceNode) + " and output " + to_string(destinationLink->destinationNode) + "...");

    if (!linkHasRequiredNumberOfFreeFSUs(sourceLink, connection->requiredNumberOfFSUs) && inputLinks.size() > 1) {
        logger.log(settings->logsEnabled, clock, Logger::CONNECTION_REJECTED, "Connection rejected: free FSUs not found in source link (" + to_string(connection->requiredNumberOfFSUs) + " FSUs)");
        return CONNECTION_REJECTED;
    }

    if (!linkHasRequiredNumberOfFreeFSUs(destinationLink, connection->requiredNumberOfFSUs)) {
        logger.log(settings->logsEnabled, clock, Logger::EXTERNAL_BLOCK, "Connection rejected: external blocking (" + to_string(connection->requiredNumberOfFSUs) + " FSUs)");
        return EXTERNAL_BLOCK;
    }

    queue<vector<Link *>> consideredPaths;
    consideredPaths.push({sourceLink});

    while (!consideredPaths.empty()) {
        vector<Link *> currentPath = consideredPaths.front();
        consideredPaths.pop();

        uint64_t currentPathLastNode = currentPath[currentPath.size() - 1]->destinationNode;

        if (currentPathLastNode == destinationLink->destinationNode) {
//            cout << "\tConsidering currentPath: ";
//            printPath(currentPath);
//            cout << ":\n";

            if (pathHasRequiredNumberOfFreeFSUs(currentPath, connection->requiredNumberOfFSUs, connection->firstFSU)) {
                connection->path = currentPath;
                logger.log(settings->logsEnabled, clock, Logger::CONNECTION_ESTABLISHED, "Connection has been successfully set up using FSUs: " + to_string(connection->firstFSU) + "-" + to_string(connection->firstFSU + connection->requiredNumberOfFSUs - 1) + " (" + to_string(connection->requiredNumberOfFSUs) + " FSUs)");
                return CONNECTION_ESTABLISHED;
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

    logger.log(settings->logsEnabled, clock, Logger::INTERNAL_BLOCK, "Connection rejected: internal blocking (" + to_string(connection->requiredNumberOfFSUs) + " FSUs)");
    return INTERNAL_BLOCK;
}

void Network::closeConnection(double clock, Connection *connection) {
    for (auto &link: connection->path) {
        link->freeFSUs(connection->firstFSU, connection->requiredNumberOfFSUs);
    }
    activeConnections.remove(connection);
    logger.log(settings->logsEnabled, clock, Logger::CONNECTION_CLOSED, "Connection closed: Freeing FSUs: " + to_string(connection->firstFSU) + "-" + to_string(connection->firstFSU + connection->requiredNumberOfFSUs - 1));
    delete connection;
}

bool Network::linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs) {
    for (int i = 0; i <= settings->linkCapacity - requiredNumberOfFSUs; i++) {
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
        uint64_t numberOfCalls = trafficClass.second.callsGenerated;
        if (numberOfCalls < result) {
            result = numberOfCalls;
        }
    }

    for (auto const &trafficClass: engsetTrafficClasses) {
        uint64_t numberOfCalls = trafficClass.second.callsGenerated;
        if (numberOfCalls < result) {
            result = numberOfCalls;
        }
    }

    for (auto const &trafficClass: pascalTrafficClasses) {
        uint64_t numberOfCalls = trafficClass.second.callsGenerated;
        if (numberOfCalls < result) {
            result = numberOfCalls;
        }
    }

    return result;
}

bool Network::everyOutputNodeIsAvailableFromEveryInputNode() {
    logger.log(settings->logsEnabled, 0, Logger::STRUCTURE_VALIDATION, "Structure validation started...");

    for (uint64_t i = 0; i < inputLinks.size(); i++) {
        for (uint64_t j = 0; j < outputLinks.size(); j++) {
            Connection *connection = new Connection(i, j, 1, 1);
            if (establishConnection(0, connection) != CONNECTION_ESTABLISHED) {
                logger.log(settings->logsEnabled, 0, Logger::STRUCTURE_VALIDATION, "Structure is not valid. Output " + to_string(outputLinks[j]->destinationNode) + " is not reachable from input " + to_string(inputLinks[i]->sourceNode));
                delete connection;
                return false;
            }
            delete connection;
        }
    }

    logger.log(settings->logsEnabled, 0, Logger::STRUCTURE_VALIDATION, "Structure is valid");
    return true;
}