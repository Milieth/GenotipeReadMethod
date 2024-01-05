#include <random>
#include <chrono>
#include "randomGenerator.h"

namespace generator
{
    std::mt19937 mt{ static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
        ) };
}

int getRand(int min, int max)
{
    std::uniform_int_distribution<> UIDist{min,max};

    return UIDist(generator::mt);
}

int getRand(int max)
{
    return getRand(1, max);
}
