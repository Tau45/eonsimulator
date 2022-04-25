#include "../include/Connection.h"

Connection::Connection(uint64_t srcLink, uint64_t dstLink, uint64_t numberOfFSUs, uint64_t serviceTime) {
    this->srcLink = srcLink;
    this->dstLink = dstLink;
    this->firstFSU = UINT64_MAX;
    this->numberOfFSUs = numberOfFSUs;
    this->serviceTime = serviceTime;
}