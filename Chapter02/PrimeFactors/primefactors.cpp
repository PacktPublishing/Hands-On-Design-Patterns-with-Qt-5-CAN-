
#include "primefactors.h"

std::list<int> getFactors(int number) {
    std::list<int> factors = {};

    for (;number % 2 == 0; number /= 2)
        factors.push_back(2);

    return factors;
}
