#pragma once
#ifndef EONSIMULATOR_FSU_H
#define EONSIMULATOR_FSU_H

#include <iostream>

class FSU {
public:
    bool isFree;
    uint64_t connectionId;

    FSU();

    void reserve(uint64_t connectionId);
};

#endif //EONSIMULATOR_FSU_H