#include "../../include/network/TestCase2.h"

TestCase2::TestCase2() {
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