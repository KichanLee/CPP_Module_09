#ifndef __PMERGEME_HPP_
#define __PMERGEME_HPP_

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
  std::deque<std::pair<int, int> > _deque;
  std::deque<int> JacobStyle_sequence_deque;  // 야곱 순서 시퀀스
  std::deque<int> mainchain_deque;
  clock_t start_time;
  clock_t end_time;
  int sizeofPair;
  int k;
  double oddvec;

 public:
  PmergeMe(/* args */);
  ~PmergeMe();
  void execute(int ac, const char *av[]);
  void input_str(int ac, const char *str[]);
  void check_sort();
  void print_vec(std::string str);
  void sort_start();
  void sort();
  void pair_make();
  void merge_sort(int left_side, int right_side);
  void merge(int left_side, int right_side, int middle);
  void print_time();
  void Jacobnumber(int n);
  void pendingorder();
  void pendtomain(int idx, int bidx);
  void binaryinsert(int value, int left, int right);
  void mainsort(int left, int mid, int right);
};

#endif