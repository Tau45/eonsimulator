#include "../../include/network/Network.h"

void Network::reserveResources(Connection connection) {
    assert(!connection.getPath().empty());
    for (auto &link: connection.getPath()) {
        link->reserveFSUs(connection.getFirstFSU(), connection.getRequiredNumberOfFSUs());
    }
}

bool Network::pathHasRequiredNumberOfFreeFSUs(vector<Link *> &path, Connection &connection) {
    vector<uint64_t> potentialFirstFSUs;

    for (int i = 0; i <= SimulationSettings::instance().getLinkCapacity() - connection.getRequiredNumberOfFSUs(); i++) {
        bool freeNeighboringFSUsWereFound = true;

        for (int j = i; j < i + connection.getRequiredNumberOfFSUs(); j++) {
            for (Link *link: path) {
                if (link->FSUIsOccupied(j)) {
                    freeNeighboringFSUsWereFound = false;
                    i = j;
                    break;
                }
            }
        }

        if (freeNeighboringFSUsWereFound) {
            potentialFirstFSUs.push_back(i);
        }
    }

    if (!potentialFirstFSUs.empty()) {
        connection.setPath(path);
        connection.setFirstFSU(Generator::instance().getRandomFirstFSU(potentialFirstFSUs));
        return true;
    }
    return false;
}

Network::ESTABLISH_CONNECTION_RESULT Network::checkIfConnectionCanBeEstablished(Connection& connection) {
    Link *sourceLink = inputLinks[connection.getSourceLink()];
    Link *destinationLink = outputLinks[connection.getDestinationLink()];

    if (!linkHasRequiredNumberOfFreeFSUs(sourceLink, connection.getRequiredNumberOfFSUs()) && inputLinks.size() > 1) {
        return CONNECTION_REJECTED;
    }

    if (!linkHasRequiredNumberOfFreeFSUs(destinationLink, connection.getRequiredNumberOfFSUs())) {
        return EXTERNAL_BLOCK;
    }

    queue<vector<Link *>> consideredPaths;
    consideredPaths.push({sourceLink});

    while (!consideredPaths.empty()) {
        vector<Link *> currentPath = consideredPaths.front();
        consideredPaths.pop();

        uint64_t currentPathLastNode = currentPath[currentPath.size() - 1]->getDestinationNode();

        if (currentPathLastNode == destinationLink->getDestinationNode() && pathHasRequiredNumberOfFreeFSUs(currentPath, connection)) {
            return CONNECTION_CAN_BE_ESTABLISHED;
        }

        for (auto &link: links[currentPathLastNode]) {
            if (linkWasNotVisited(currentPath, link->getDestinationNode())) {
                vector<Link *> newPath(currentPath);
                newPath.push_back(link);
                consideredPaths.push(newPath);
            }
        }
    }

    return INTERNAL_BLOCK;
}

void Network::closeConnection(double clock, Connection connection) {
    Logger::instance().log(clock, Logger::CONNECTION_CLOSED, "Connection closed: Freeing FSUs: " + to_string(connection.getFirstFSU()) + "-" + to_string(connection.getFirstFSU() + connection.getRequiredNumberOfFSUs() - 1));
    for (auto &link: connection.getPath()) {
        link->freeFSUs(connection.getFirstFSU(), connection.getRequiredNumberOfFSUs());
    }
}

bool Network::linkHasRequiredNumberOfFreeFSUs(Link *link, uint64_t requiredNumberOfFSUs) {
    for (int i = 0; i <= SimulationSettings::instance().getLinkCapacity() - requiredNumberOfFSUs; i++) {
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

void Network::closeAllConnections() {
    for (const auto &node : links) {
        for (auto link : node.second) {
            link->freeAllFSUs();
        }
    }
}