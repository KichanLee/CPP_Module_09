#include "RPN.HPP"

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(const RPN& rhs) { (void)rhs; }
RPN& RPN::operator=(const RPN& rhs) {
  (void)rhs;
  return (*this);
}

bool RPN::check_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::check_number(char c) { return c >= '0' && c <= '9'; }

void RPN::check_argument(const char* str) {
  std::string str_check(str);

  unsigned int cal = 0;
  unsigned int num = 0;

  for (std::string::iterator it = str_check.begin(); it != str_check.end();
       ++it) {
    if (*it == ' ') continue;
    if (check_number(*it))
      num++;
    else if (check_operator(*it))
      cal++;
    else
      throw std::runtime_error("Error");
  }
  if (cal + 1 != num)
    throw std::runtime_error("Operator count must be number + 1");
  return;
}

void RPN::check_exception(int ac, const char* av[]) {
  if (ac != 2) throw std::runtime_error("Argument must be two");
  check_argument(av[1]);
}

double RPN::operator_cal(int num1, int num2, char ch) {
  if (ch == '+')
    return (num1 + num2);
  else if (ch == '-')
    return (num1 - num2);
  else if (ch == '/') {
    if (num2 == 0) throw std::runtime_error("Cannot divide by Zero.");
    return (num1 / num2);
  }
  return (num1 * num2);
}

double RPN::calculate(std::string str) {
  std::string::iterator it = str.begin();
  int tmp_one = 0;
  int tmp_two = 0;

  while (it != str.end()) {
    if (*it == ' ') {
      ++it;
      continue;
    } else if (check_number(*it)) {
      int num = *it - '0';
      this->cal_stack.push(num);
    } else if (check_operator(*it)) {
      if (!cal_stack.empty()) {
        tmp_one = this->cal_stack.top();
        this->cal_stack.pop();
        if (this->cal_stack.empty())
          throw std::runtime_error("Operator Order is not Properly.");
      }
      if (!cal_stack.empty()) {
        tmp_two = this->cal_stack.top();
        this->cal_stack.pop();
      }
      this->cal_stack.push(operator_cal(tmp_two, tmp_one, *it));
    }
    ++it;
  }
  return (this->cal_stack.top());
}

void RPN::execute(int ac, const char* av[]) {
  check_exception(ac, av);
  std::cout << calculate(std::string(av[1])) << std::endl;
}