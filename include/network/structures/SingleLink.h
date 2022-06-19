#ifndef EONSIMULATOR_SINGLELINK_H
#define EONSIMULATOR_SINGLELINK_H

#include "../Network.h"

class SingleLink : public Network {
public:
    SingleLink() {
        setNumberOfNodes(2);

        Link *link = new Link(0, 1);
        inputLinks.push_back(link);
        outputLinks.push_back(link);
        links[0].push_back(link);
    }
};

#endif //EONSIMULATOR_SINGLELINK_H
