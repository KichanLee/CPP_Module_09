#include <iostream>
#include <string>

int main() {
  const std::string year = "2021-22-09";

  std::cout << year.at(4) << "\n";
  std::cout << year.at(7) << "\n";

  std::string _year = year.substr(0, 4);
  const char *test = _year.c_str();
  std::cout << _year << std::endl;
}