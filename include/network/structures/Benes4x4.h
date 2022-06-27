#ifndef EONSIMULATOR_BENES4X4_H
#define EONSIMULATOR_BENES4X4_H

#include "../Network.h"

class Benes4x4 : public Network {
public:
    Benes4x4() {
        createLink(0, 4, true, false);
        createLink(1, 4, true, false);
        createLink(2, 5, true, false);
        createLink(3, 5, true, false);

        createLink(8, 10, false, true);
        createLink(8, 11, false, true);
        createLink(9, 12, false, true);
        createLink(9, 13, false, true);

        createLink(4, 6, false, false);
        createLink(4, 7, false, false);
        createLink(5, 6, false, false);
        createLink(5, 7, false, false);
        createLink(6, 8, false, false);
        createLink(6, 9, false, false);
        createLink(7, 8, false, false);
        createLink(7, 9, false, false);
    }
};

#endif //EONSIMULATOR_BENES4X4_H