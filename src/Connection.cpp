#include "../include/Connection.h"

Connection::Connection(uint64_t id, uint64_t srcLink, uint64_t dstLink, uint64_t numberOfFSUs) {
    this->id = id;
    this->srcLink = srcLink;
    this->dstLink = dstLink;
    this->firstFSU = UINT64_MAX;
    this->numberOfFSUs = numberOfFSUs;
}