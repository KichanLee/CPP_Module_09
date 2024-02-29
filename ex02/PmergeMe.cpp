#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
  this->k = 0;
  this->p = 0;
}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &rhs) { (void)rhs; }
PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
  (void)rhs;
  return (*this);
}
void PmergeMe::Jacobnumber(int n) {
  this->JacobStyle_sequence_vec.push_back(0);
  this->JacobStyle_sequence_vec.push_back(1);

  for (int i = 2; i <= n + 2; ++i)
    this->JacobStyle_sequence_vec.push_back(
        this->JacobStyle_sequence_vec[i - 1] +
        this->JacobStyle_sequence_vec[i - 2] * 2);
}

void PmergeMe::input_str(int ac, const char *str[]) {
  int i = 1;
  int input = 0;
  while (i < ac) {
    char *endPtr = NULL;

    input = static_cast<int>(strtod(str[i], &endPtr));
    if (*endPtr != '\0') throw std::runtime_error("Arguments must be a number");
    if (input > INT_MAX)
      throw std::runtime_error("Int Max vlaue over.");
    else if (input < 0)
      throw std::runtime_error("Arguments must be a positive number");
    else {
      std_vector.push_back(input);
      std_deq.push_back(input);
    }
    ++i;
  }
  if (std_vector.size() % 2 == 1) oddvec = std_vector[std_vector.size() - 1];
}

void PmergeMe::check_sort() {
  int flag = 0;

  std::vector<int>::iterator it_start = this->std_vector.begin();
  std::vector<int>::iterator it_end = this->std_vector.end();

  --it_end;
  while (it_start != it_end) {
    if (*it_start > *(++it_start)) flag = 1;
  }
  if (flag != 1) throw std::runtime_error("Already sorted.");
}

void PmergeMe::print_vec(std::string str) {
  std::cout << str;
  if (str == "Before: ") {
    for (std::vector<int>::iterator it = this->std_vector.begin();
         it != this->std_vector.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << "\n";
  } else {
    for (std::vector<int>::iterator it = this->mainchain_vector.begin();
         it != this->mainchain_vector.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }
}

void PmergeMe::merge(int left_side, int right_side, int middle) {
  std::vector<std::pair<int, int> > left_vector(middle - left_side + 1);
  std::vector<std::pair<int, int> > right_vector(right_side - middle);

  for (int i = 0; i < static_cast<int>(left_vector.size()); ++i) {
    left_vector[i] = this->pair_vector[left_side + i];
  }
  for (int i = 0; i < static_cast<int>(right_vector.size()); ++i)
    right_vector[i] = this->pair_vector[middle + i + 1];

  int l = 0;
  int k = 0;
  int c = left_side;
  while (l < static_cast<int>(left_vector.size()) &&
         k < static_cast<int>(right_vector.size())) {
    if (left_vector[l].first <= right_vector[k].first)
      this->pair_vector[c++] = left_vector[l++];
    else
      this->pair_vector[c++] = right_vector[k++];
  }
  while (l < static_cast<int>(left_vector.size()))
    this->pair_vector[c++] = left_vector[l++];
  while (k < static_cast<int>(right_vector.size()))
    this->pair_vector[c++] = right_vector[k++];
}

void PmergeMe::merge_sort(int left_side, int right_side) {
  if (left_side < right_side) {
    int middle = (left_side + right_side) / 2;
    merge_sort(left_side, middle);
    merge_sort(middle + 1, right_side);
    merge(left_side, right_side, middle);
  }
}

void PmergeMe::pair_make() {
  int middle = this->std_vector.size() / 2;
  for (int i = 0; i < middle; ++i) {
    if (this->std_vector[i] > this->std_vector[middle + i]) {
      this->pair_vector.push_back(
          std::make_pair(this->std_vector[i], this->std_vector[i + middle]));
    } else {
      this->pair_vector.push_back(
          std::make_pair(this->std_vector[i + middle], this->std_vector[i]));
    }
  }
  merge_sort(0, middle - 1);
}

void PmergeMe::pendtomain(int idx, int bidx) {
  while (idx > bidx) {
    binary_search(this->pair_vector[idx - 1].second, 0, idx + this->k - 1);
    idx--;
  }
}

void PmergeMe::binary_search(int value, int left, int right) {
  if (left >= right) {
    if (this->mainchain_vector[left] > value) {
      this->k++;
      this->mainchain_vector.insert(this->mainchain_vector.begin() + left,
                                    value);
    } else {
      this->k++;
      this->mainchain_vector.insert(this->mainchain_vector.begin() + left + 1,
                                    value);
    }
    return;
  }
  int mid = (left + right) / 2;
  if (this->mainchain_vector[mid] == value) {
    this->k++;
    this->mainchain_vector.insert(this->mainchain_vector.begin() + mid, value);
    return;
  } else if (this->mainchain_vector[mid] < value) {
    binary_search(value, mid + 1, right);
  } else {
    binary_search(value, left, mid);
  }
}

void PmergeMe::order_pending() {
  int i = 1;

  while (1) {
    if (this->sizeofPair < this->JacobStyle_sequence_vec[i]) {
      pendtomain(this->sizeofPair, JacobStyle_sequence_vec[i - 1]);
      if (std_vector.size() % 2 != 0) {
        int msize = mainchain_vector.size();
        binary_search(oddvec, 0, msize - 1);
      }
      break;
    } else {
      pendtomain(JacobStyle_sequence_vec[i], JacobStyle_sequence_vec[i - 1]);
      i++;
    }
  }
}

void PmergeMe::sort() {
  this->sizeofPair = this->std_vector.size() / 2;
  pair_make();
  Jacobnumber(this->sizeofPair);
  int i = 0;
  while (i < this->sizeofPair) {
    this->mainchain_vector.push_back(this->pair_vector[i].first);
    ++i;
  }
  order_pending();
}

void PmergeMe::sort_start() {
  this->start_time = clock();
  sort();
  this->end_time = clock();
}

void PmergeMe::print_time(std::string str) {
  double usec = (((double)(end_time - start_time)) * 10 / CLOCKS_PER_SEC);
  std::cout << "\nTime to process a range of " << this->std_vector.size();
  std::cout << " elements with " << str << " : " << usec << " us\n";
}

/// @brief ///////////////////////////////////////////////////////////////////

void PmergeMe::binary_search_deque(int value, int left, int right) {
  if (left >= right) {
    if (this->mainchain_deque[left] > value) {
      this->p++;
      this->mainchain_deque.insert(this->mainchain_deque.begin() + left, value);
    } else {
      this->p++;
      this->mainchain_deque.insert(this->mainchain_deque.begin() + left + 1,
                                   value);
    }
    return;
  }
  int mid = (left + right) / 2;
  if (this->mainchain_deque[mid] == value) {
    this->p++;
    this->mainchain_deque.insert(this->mainchain_deque.begin() + mid, value);
    return;
  } else if (this->mainchain_deque[mid] < value) {
    binary_search_deque(value, mid + 1, right);
  } else {
    binary_search_deque(value, left, mid);
  }
}

void PmergeMe::pendtomain_deque(int idx, int bidx) {
  while (idx > bidx) {
    binary_search_deque(this->pair_vector[idx - 1].second, 0,
                        idx + this->p - 1);
    idx--;
  }
}

void PmergeMe::Jacobnumber_deque(int n) {
  this->JacobStyle_sequence_deque.push_back(0);
  this->JacobStyle_sequence_deque.push_back(1);

  for (int i = 2; i <= n + 2; ++i)
    this->JacobStyle_sequence_deque.push_back(
        this->JacobStyle_sequence_deque[i - 1] +
        this->JacobStyle_sequence_deque[i - 2] * 2);
}

void PmergeMe::pair_make_deque() {
  int middle = this->std_deq.size() / 2;
  for (int i = 0; i < middle; ++i) {
    if (this->std_deq[i] > this->std_deq[middle + i]) {
      this->pair_deque.push_back(
          std::make_pair(this->std_deq[i], this->std_deq[i + middle]));
    } else {
      this->pair_deque.push_back(
          std::make_pair(this->std_deq[i + middle], this->std_deq[i]));
    }
  }
  merge_sort_deque(0, middle - 1);
}
void PmergeMe::merge_deque(int left_side, int right_side, int middle) {
  std::deque<std::pair<int, int> > left_deque(middle - left_side + 1);
  std::deque<std::pair<int, int> > right_deque(right_side - middle);

  for (int i = 0; i < static_cast<int>(left_deque.size()); ++i) {
    left_deque[i] = this->pair_deque[left_side + i];
  }
  for (int i = 0; i < static_cast<int>(right_deque.size()); ++i)
    right_deque[i] = this->pair_deque[middle + i + 1];

  int l = 0;
  int k = 0;
  int c = left_side;
  while (l < static_cast<int>(left_deque.size()) &&
         k < static_cast<int>(right_deque.size())) {
    if (left_deque[l].first <= right_deque[k].first)
      this->pair_deque[c++] = left_deque[l++];
    else
      this->pair_deque[c++] = right_deque[k++];
  }
  while (l < static_cast<int>(left_deque.size()))
    this->pair_deque[c++] = left_deque[l++];
  while (k < static_cast<int>(right_deque.size()))
    this->pair_deque[c++] = right_deque[k++];
}

void PmergeMe::merge_sort_deque(int left_side, int right_side) {
  if (left_side < right_side) {
    int middle = (left_side + right_side) / 2;
    merge_sort_deque(left_side, middle);
    merge_sort_deque(middle + 1, right_side);
    merge_deque(left_side, right_side, middle);
  }
}

void PmergeMe::order_pending_deque() {
  int i = 1;

  while (1) {
    if (this->sizeofPair < this->JacobStyle_sequence_deque[i]) {
      pendtomain_deque(this->sizeofPair, JacobStyle_sequence_deque[i - 1]);
      if (std_deq.size() % 2 != 0) {
        int msize = mainchain_deque.size();
        binary_search_deque(oddvec, 0, msize - 1);
      }
      break;
    } else {
      pendtomain_deque(JacobStyle_sequence_deque[i],
                       JacobStyle_sequence_deque[i - 1]);
      i++;
    }
  }
}

void PmergeMe::sort_deque() {
  this->sizeofPair = this->std_deq.size() / 2;
  pair_make_deque();
  Jacobnumber_deque(this->sizeofPair);
  int i = 0;
  while (i < this->sizeofPair) {
    this->mainchain_deque.push_back(this->pair_deque[i].first);
    ++i;
  }
  order_pending_deque();
}

void PmergeMe::execute(int ac, const char *av[]) {
  if (ac < 3) throw std::runtime_error("Arguments must be over three.");
  input_str(ac, av);
  check_sort();
  print_vec("Before: ");
  sort_start();
  print_vec("After: ");
  print_time("std::vector");
  this->start_time = clock();
  sort_deque();
  this->end_time = clock();
  print_time("std::deque");
}