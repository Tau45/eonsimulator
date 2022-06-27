#ifndef EONSIMULATOR_TESTCASE2_H
#define EONSIMULATOR_TESTCASE2_H

#include "../Network.h"

class TestCase2 : public Network {
public:
    TestCase2() {
        createLink(0, 1, true, false);

        createLink(11, 12, false, true);

        createLink(1, 2, false, false);
        createLink(1, 3, false, false);
        createLink(1, 4, false, false);
        createLink(1, 5, false, false);
        createLink(2, 11, false, false);
        createLink(3, 6, false, false);
        createLink(4, 7, false, false);
        createLink(5, 8, false, false);
        createLink(6, 9, false, false);
        createLink(7, 10, false, false);
        createLink(8, 11, false, false);
        createLink(9, 11, false, false);
        createLink(10, 11, false, false);
    }
};

#endif //EONSIMULATOR_TESTCASE2_H