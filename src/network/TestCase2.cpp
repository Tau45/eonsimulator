#include "../../include/network/TestCase2.h"

TestCase2::TestCase2() {
    links.resize(13);

    inputLinks.push_back(new Link(0, 1));

    outputLinks.push_back(new Link(11, 12));

    links[0].push_back(inputLinks[0]);
    links[1].push_back(new Link(1, 2));
    links[1].push_back(new Link(1, 3));
    links[1].push_back(new Link(1, 4));
    links[1].push_back(new Link(1, 5));
    links[2].push_back(new Link(2, 11));
    links[3].push_back(new Link(3, 6));
    links[4].push_back(new Link(4, 7));
    links[5].push_back(new Link(5, 8));
    links[6].push_back(new Link(6, 9));
    links[7].push_back(new Link(7, 10));
    links[8].push_back(new Link(8, 11));
    links[9].push_back(new Link(9, 11));
    links[10].push_back(new Link(10, 11));
    links[11].push_back(outputLinks[0]);
}