#include "../include/FSU.h"

FSU::FSU() {
    isFree = true;
    connectionId = UINT64_MAX;
}

void FSU::reserve(uint64_t id) {
    isFree = false;
    connectionId = id;
}
