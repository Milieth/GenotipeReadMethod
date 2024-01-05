#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>

namespace generator
{
    extern std::mt19937 mt;
}
int getRand(int min, int max);
int getRand(int max);

#endif // RANDOMGENERATOR_H
