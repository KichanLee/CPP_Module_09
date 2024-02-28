#include "PmergeMe.hpp"

PmergeMe::PmergeMe(/* args */) {}
PmergeMe::~PmergeMe() {}
bool PmergeMe::check_number(char c) { return c >= '0' && c <= '9'; }
// bool PmergeMe::check_sort();
void PmergeMe::input_str(int ac, const char *str[]) {
  int i = 1;
  unsigned int input = 0;
  while (i < ac) {
    char *endPtr = NULL;

    input = static_cast<unsigned int>(strtod(str[i], &endPtr));
    if (*endPtr != '\0')
      throw std::runtime_error("Arguments must be a number");
    else if (input < 0)
      throw std::runtime_error("Arguments must be a positive number");
    else {
      std_vector.push_back(input);
      std_deq.push_back(input);
    }
  }
}

void PmergeMe::execute(int ac, const char *av[]) {
  if (ac < 3) throw std::runtime_error("Arguments must be over three.");
  input_str(ac, av);
}