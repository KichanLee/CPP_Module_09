#include "PmergeMe.hpp"

PmergeMe::PmergeMe(/* args */) {}
PmergeMe::~PmergeMe() {}

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
  this->k = 0;
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
  for (int i = 0; i < middle; i++) {
    std::cout << "first  : " << pair_vector[i].first << " ";
    std::cout << "second : " << pair_vector[i].second << " ";
  }
  std::cout << "\n";
  merge_sort(0, middle - 1);
}

void PmergeMe::pendtomain(int idx, int bidx) {
  while (idx > bidx) {
    binaryinsert(this->pair_vector[idx - 1].second, 0, idx + this->k - 1);
    idx--;
  }
}

void PmergeMe::binaryinsert(int value, int left, int right) {
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
    binaryinsert(value, mid + 1, right);
  } else {
    binaryinsert(value, left, mid);
  }
}

void PmergeMe::pendingorder(void) {
  int i = 1;

  while (1) {
    if (this->sizeofPair < this->JacobStyle_sequence_vec[i]) {
      pendtomain(this->sizeofPair, JacobStyle_sequence_vec[i - 1]);
      if (std_vector.size() % 2 != 0) {
        int msize = mainchain_vector.size();
        binaryinsert(oddvec, 0, msize - 1);
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
  pendingorder();
}

void PmergeMe::sort_start() {
  this->start_time = clock();
  sort();
  this->end_time = clock();
}

void PmergeMe::print_time() {
  double usec = static_cast<double>((end_time - start_time)) * 1000000;
  std::cout << "\nTime to process a range of " << this->std_vector.size();
  std::cout << " elements with std::vector : " << usec << " us\n";
}
void PmergeMe::execute(int ac, const char *av[]) {
  if (ac < 3) throw std::runtime_error("Arguments must be over three.");
  input_str(ac, av);
  check_sort();
  print_vec("Before: ");
  sort_start();
  print_vec("After: ");
}