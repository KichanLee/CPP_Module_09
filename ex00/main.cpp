#include "BitcoinExchange.hpp"

int main(int ac, const char* av[]) {
  BitcoinExchange bp;

  if (ac != 2) {
    std::cout << "Not A Valid Arguments" << std::endl;
    return (1);
  }
  try {
    bp.check_File(av[1]);

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return (0);
}