#ifndef EONSIMULATOR_TESTCASE1_H
#define EONSIMULATOR_TESTCASE1_H

#include "../Network.h"

class TestCase1 : public Network {
public:
    TestCase1() {
        createLink(0, 4, true, false);
        createLink(1, 4, true, false);
        createLink(2, 5, true, false);
        createLink(3, 5, true, false);

        createLink(7, 9, false, true);
        createLink(7, 10, false, true);
        createLink(8, 11, false, true);
        createLink(8, 12, false, true);

        createLink(4, 6, false, false);
        createLink(4, 7, false, false);
        createLink(5, 6, false, false);
        createLink(5, 8, false, false);
        createLink(6, 7, false, false);
        createLink(6, 8, false, false);
    }
};

#endif //EONSIMULATOR_TESTCASE1_H