#include "BitcoinExchange.hpp"

int main(int ac, const char* av[]) {
  try {
    BitcoinExchange bp;
    bp.open_File(ac, av[1]);
    bp.parseCsv(bp.get_csv_text());
    bp.parseText(bp.get_input_text());
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return (0);
}