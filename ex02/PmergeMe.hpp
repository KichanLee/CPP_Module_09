#ifndef __PMERGEME_HPP_
#define __PMERGEME_HPP_

#include <climits>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <exception>
#include <iostream>
#include <vector>

class PmergeMe {
 private:
  std::vector<int> std_vector;
  std::vector<std::pair<int, int> > pair_vector;
  std::vector<int> JacobStyle_sequence_vec;
  std::vector<int> mainchain_vector;

  std::deque<int> std_deq;
  std::deque<std::pair<int, int> > pair_deque;
  std::deque<int> JacobStyle_sequence_deque;
  std::deque<int> mainchain_deque;
  clock_t start_time;
  clock_t end_time;
  int sizeofPair;
  int k;
  int p;
  double oddvec;
  PmergeMe(const PmergeMe& rhs);
  PmergeMe& operator=(const PmergeMe& rhs);

 public:
  PmergeMe();
  ~PmergeMe();
  void execute(int ac, const char* av[]);
  void input_str(int ac, const char* str[]);
  void check_sort();
  void print_vec(std::string str);
  void sort_start();
  void sort();
  void pair_make();
  void merge_sort(int left_side, int right_side);
  void merge(int left_side, int right_side, int middle);
  void print_time(std::string str);
  void Jacobnumber(int n);
  void order_pending();
  void pendtomain(int idx, int bidx);
  void binary_search(int value, int left, int right);
  void sort_deque();
  void pair_make_deque();
  void merge_sort_deque(int left_side, int right_side);
  void merge_deque(int left_side, int right_side, int middle);
  void Jacobnumber_deque(int n);
  void order_pending_deque();
  void pendtomain_deque(int idx, int bidx);
  void binary_search_deque(int value, int left, int right);
};

#endif