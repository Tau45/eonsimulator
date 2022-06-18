#ifndef EONSIMULATOR_BENES4X4_H
#define EONSIMULATOR_BENES4X4_H

#include "../Network.h"

class Benes4x4 : public Network {
public:
    Benes4x4() {
        setNumberOfNodes(13);

        createInputLink(0, 4);
        createInputLink(1, 4);
        createInputLink(2, 5);
        createInputLink(3, 5);

        createOutputLink(7, 9);
        createOutputLink(7, 10);
        createOutputLink(8, 11);
        createOutputLink(8, 12);

        createLink(4, 6);
        createLink(4, 7);
        createLink(5, 6);
        createLink(5, 8);
        createLink(6, 7);
        createLink(6, 8);
    }
};

#endif //EONSIMULATOR_BENES4X4_H