#include "../include/Connection.h"

Connection::Connection(uint64_t srcLink, uint64_t dstLink, uint64_t requiredNumberOfFSUs, double serviceTime) {
    this->sourceLinkIndex = srcLink;
    this->destinationLinkIndex = dstLink;
    this->firstFSU = UINT64_MAX;
    this->requiredNumberOfFSUs = requiredNumberOfFSUs;
    this->serviceTime = serviceTime;
}