//
// Created by Astolfo on 24-11-16.
//

#ifndef RANDFUNCTION_H
#define RANDFUNCTION_H

#include <random>

inline int rand_range_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}
#endif //RANDFUNCTION_H
