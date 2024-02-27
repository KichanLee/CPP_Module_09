#include "RPN.HPP"

RPN::RPN() {}
RPN::~RPN() {}

void check_argument(const char* str) {
  std::string str_check(str);

  unsigned int cal = 0;
  unsigned int num = 0;

  for (std::string::iterator it = str_check.begin(); it != str_check.end();
       it++) {
    if (*it < '0' || *it > '9' || *it != ' ' || *it != '+' || *it != '-' ||
        *it != '/' || *it != '*')
      throw std::runtime_error("You Got the Wrong input");
    else if (*it == '+' || *it == '-' || *it == '/' || *it == '*')
      ++cal;
    else if (*it > 0 && *it < 10)
      ++num;
  }
  if (cal + 1 != num)
    throw std::runtime_error("Operator count must be number + 1");
  return;
}

void check_exception(int ac, const char* av[]) {
  if (ac != 2) throw std::runtime_error("Argument must be two");
  check_argument(av[1]);
}

void RPN::execute(int ac, const char* av[]) {
  check_exception(ac, av);
  //   std::string str(av[1]);
  std::stringstream ss("123");
  int num;
  ss >> num;
  std::cout << num << std::endl;
}