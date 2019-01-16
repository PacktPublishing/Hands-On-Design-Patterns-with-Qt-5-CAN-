
#include "primefactors.h"

std::list<int> getFactors(int number) {
  if (number % 2 == 0)
    return std::list<int>{2};

  return std::list<int>{};
}
