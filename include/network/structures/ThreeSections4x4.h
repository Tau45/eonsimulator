#ifndef EONSIMULATOR_THREESECTIONS4X4_H
#define EONSIMULATOR_THREESECTIONS4X4_H

#include "../Network.h"

class ThreeSections4x4 : public Network {
public:
    ThreeSections4x4() {
        // input links
        createLink(0, 16, true, false);
        createLink(1, 16, true, false);
        createLink(2, 16, true, false);
        createLink(3, 16, true, false);

        createLink(4, 17, true, false);
        createLink(5, 17, true, false);
        createLink(6, 17, true, false);
        createLink(7, 17, true, false);

        createLink(8, 18, true, false);
        createLink(9, 18, true, false);
        createLink(10, 18, true, false);
        createLink(11, 18, true, false);

        createLink(12, 19, true, false);
        createLink(13, 19, true, false);
        createLink(14, 19, true, false);
        createLink(15, 19, true, false);

        // output links
        createLink(24, 28, false, true);
        createLink(24, 29, false, true);
        createLink(24, 30, false, true);
        createLink(24, 31, false, true);

        createLink(25, 32, false, true);
        createLink(25, 33, false, true);
        createLink(25, 34, false, true);
        createLink(25, 35, false, true);

        createLink(26, 36, false, true);
        createLink(26, 37, false, true);
        createLink(26, 38, false, true);
        createLink(26, 39, false, true);

        createLink(27, 40, false, true);
        createLink(27, 41, false, true);
        createLink(27, 42, false, true);
        createLink(27, 43, false, true);

        // other links
        createLink(16, 20, false, false);
        createLink(16, 21, false, false);
        createLink(16, 22, false, false);
        createLink(16, 23, false, false);

        createLink(17, 20, false, false);
        createLink(17, 21, false, false);
        createLink(17, 22, false, false);
        createLink(17, 23, false, false);

        createLink(18, 20, false, false);
        createLink(18, 21, false, false);
        createLink(18, 22, false, false);
        createLink(18, 23, false, false);

        createLink(19, 20, false, false);
        createLink(19, 21, false, false);
        createLink(19, 22, false, false);
        createLink(19, 23, false, false);

        createLink(20, 24, false, false);
        createLink(20, 25, false, false);
        createLink(20, 26, false, false);
        createLink(20, 27, false, false);

        createLink(21, 24, false, false);
        createLink(21, 25, false, false);
        createLink(21, 26, false, false);
        createLink(21, 27, false, false);

        createLink(22, 24, false, false);
        createLink(22, 25, false, false);
        createLink(22, 26, false, false);
        createLink(22, 27, false, false);

        createLink(23, 24, false, false);
        createLink(23, 25, false, false);
        createLink(23, 26, false, false);
        createLink(23, 27, false, false);
    }
};

#endif //EONSIMULATOR_THREESECTIONS4X4_H