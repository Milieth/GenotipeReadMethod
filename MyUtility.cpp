#include "MyUtility.h"
#include <assert.h>
#include <limits>
#include <iostream>

std::bitset<8> bitTrue(unsigned int manyTrue)
{
    unsigned int bitLenght = 8u;
    unsigned int bitDel = bitLenght-manyTrue;
    std::bitset<8> zeroBit{0b0000'0000};
    return (~zeroBit) << bitDel >> bitDel;
}
