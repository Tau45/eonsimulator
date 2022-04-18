#include "../../include/network/Benes4x4.h"

Benes4x4::Benes4x4() {
    links.resize(13);

    inputLinks.push_back(new Link(0, 4));
    inputLinks.push_back(new Link(1, 4));
    inputLinks.push_back(new Link(2, 5));
    inputLinks.push_back(new Link(3, 5));

    outputLinks.push_back(new Link(7, 9));
    outputLinks.push_back(new Link(7, 10));
    outputLinks.push_back(new Link(8, 11));
    outputLinks.push_back(new Link(8, 12));

    links[0].push_back(inputLinks[0]);
    links[1].push_back(inputLinks[1]);
    links[2].push_back(inputLinks[2]);
    links[3].push_back(inputLinks[3]);
    links[4].push_back(new Link(4, 6));
    links[4].push_back(new Link(4, 7));
    links[5].push_back(new Link(5, 6));
    links[5].push_back(new Link(5, 8));
    links[6].push_back(new Link(6, 7));
    links[6].push_back(new Link(6, 8));
    links[7].push_back(outputLinks[0]);
    links[7].push_back(outputLinks[1]);
    links[8].push_back(outputLinks[2]);
    links[8].push_back(outputLinks[3]);
}