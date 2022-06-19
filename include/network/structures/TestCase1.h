#ifndef EONSIMULATOR_TESTCASE1_H
#define EONSIMULATOR_TESTCASE1_H

#include "../Network.h"

class TestCase1 : public Network {
public:
    TestCase1() {
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

#endif //EONSIMULATOR_TESTCASE1_H