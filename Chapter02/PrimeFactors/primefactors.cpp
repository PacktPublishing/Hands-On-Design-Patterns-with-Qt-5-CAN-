
#include "primefactors.h"

std::list<int> getFactors(int number) {
  std::list<int> factors = {};

  if (number % 2 == 0)
    factors.push_back(2);

  return factors;
}
