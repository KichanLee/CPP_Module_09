#include "BitcoinExchange.hpp"

int main(int ac, const char* av[]) {
  try {
    BitcoinExchange bp;
    bp.open_File(ac, av[1]);
    // bp.check_Date(bp.get_text());
    // bp.parseText(bp.get_text());

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return (0);
}