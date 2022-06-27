#include "../include/Connection.h"

Connection::Connection(uint64_t srcLink, uint64_t dstLink, uint64_t requiredNumberOfFSUs, uint64_t serviceTime) {
    this->sourceLinkIndex = srcLink;
    this->destinationLinkIndex = dstLink;
    this->firstFSU = UINT64_MAX;
    this->numberOfFSUs = requiredNumberOfFSUs;
    this->serviceTime = serviceTime;
}