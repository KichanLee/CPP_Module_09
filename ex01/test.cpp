#include <iostream>
#include <string>

int main() {
  std::string str = "Hello, World!";

  // Create a substring from position 7 of length 5
  std::string sub = str.substr(7, 1);
  std::cout << "Substring: " << sub << std::endl;  // Outputs: World

  // Create a substring from position 7 until the end of the string
  std::string subToEnd = str.substr(7);
  std::cout << "Substring to end: " << subToEnd
            << std::endl;  // Outputs: World!

  return 0;
}
