#ifndef EONSIMULATOR_TESTCASE2_H
#define EONSIMULATOR_TESTCASE2_H

#include "../Network.h"

class TestCase2 : public Network {
public:
    TestCase2() {
        setNumberOfNodes(13);

        createInputLink(0, 1);

        createOutputLink(11, 12);

        createLink(1, 2);
        createLink(1, 3);
        createLink(1, 4);
        createLink(1, 5);
        createLink(2, 11);
        createLink(3, 6);
        createLink(4, 7);
        createLink(5, 8);
        createLink(6, 9);
        createLink(7, 10);
        createLink(8, 11);
        createLink(9, 11);
        createLink(10, 11);
    }
};

#endif //EONSIMULATOR_TESTCASE2_H