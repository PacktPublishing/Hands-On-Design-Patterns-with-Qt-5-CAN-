
#include "primefactors.h"

std::list<int> getFactors(int number) {
    std::list<int> factors = {};

    for (int factor=2; factor<=number; factor++)
        for (;number % factor == 0; number /= factor)
            factors.push_back(factor);

    return factors;
}
