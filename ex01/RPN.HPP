#ifndef __RPN_HPP
#define __RPN_HPP

#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class RPN {
 private:
  std::stack<int> stack;

 public:
  RPN();
  ~RPN();
  void execute(int ac, const char* av[]);
};

#endif
