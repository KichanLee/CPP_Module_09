#ifndef __PMERGEME_HPP_
#define __PMERGEME_HPP_

#include <deque>
#include <exception>
#include <iostream>
#include <vector>

class PmergeMe {
 private:
  std::vector<unsigned int> std_vector;
  std::vector<std::pair<unsigned int, unsigned int> > _vector;
  std::vector<unsigned int> _sequence;
  std::vector<unsigned int> mainchain;

  std::deque<int> std_deq;
  std::deque<std::pair<int, int> > _deque;
  std::deque<int> _seq;
  std::deque<int> deqmainchain;

 public:
  PmergeMe(/* args */);
  ~PmergeMe();
  void execute(int ac, const char *av[]);
  bool check_number(char c);
  void input_str(int ac, const char *str[]);
};

#endif