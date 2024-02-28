#include "PmergeMe.hpp"

int main(int ac, const char* av[]) {
  try {
    PmergeMe pm;
    pm.execute(ac, av);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}