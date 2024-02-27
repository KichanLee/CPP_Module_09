#ifndef __RPN_HPP
#define __RPN_HPP

#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class RPN {
 private:
  std::stack<double> cal_stack;
  RPN(const RPN& rhs);
  RPN& operator=(const RPN& rhs);

 public:
  RPN();
  ~RPN();
  double calculate(std::string str);
  void execute(int ac, const char* av[]);
  void check_exception(int ac, const char* av[]);
  void check_argument(const char* str);
  bool check_operator(char c);
  bool check_number(char c);
  double operator_cal(int num1, int num2, char ch);
};

#endif
