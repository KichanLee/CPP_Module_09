#include "RPN.HPP"

int main(int ac, const char* av[]) {
  try {
    RPN rpn;
    rpn.execute(ac, av);

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}