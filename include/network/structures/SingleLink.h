#ifndef EONSIMULATOR_SINGLELINK_H
#define EONSIMULATOR_SINGLELINK_H

#include "../Network.h"

class SingleLink : public Network {
public:
    SingleLink() {
        createLink(0, 1, true, true);
    }
};

#endif //EONSIMULATOR_SINGLELINK_H
