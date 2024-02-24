
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs) { (void)rhs; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
  (void)rhs;
  return (*this);
}

void BitcoinExchange::open_File(int ac, const char file[]) {
  if (ac != 2) throw std::runtime_error("Error: could not open file.");
  open_csv_File();
  open_input_File(file);
}

void BitcoinExchange::open_csv_File() {
  this->_csv_in.open("data.csv");
  if (!this->_csv_in.is_open())
    throw std::runtime_error("Error : could not open file.");

  read_File(this->_csv_in, this->_csv_text);
}

void BitcoinExchange::open_input_File(const char file[]) {
  this->_fileName = file;
  this->_input_in.open(this->_fileName.c_str());
  if (!this->_input_in.is_open())
    throw std::runtime_error("Error: could not open file.");

  read_File(this->_input_in, this->_input_text);
}

void BitcoinExchange::read_File(std::ifstream& in, std::string& txt) {
  std::stringstream buffer;
  buffer << in.rdbuf();
  txt = buffer.str();
}

void BitcoinExchange::input_map(std::string key, std::string value) {
  double result = 0;
  char* endPtr;
  result = std::strtod(value.c_str(), &endPtr);
  std::map<std::string, double>::iterator it;

  this->_csv_keyval[key] = result;
}

void BitcoinExchange::parseCsv(const std::string& csv) {
  size_t start = 0;
  size_t pos_comma, pos_enter;

  while ((start < csv.length()) &&
         (((pos_enter = csv.find("\n", start)) != std::string::npos) ||
          (start < csv.length()))) {
    pos_comma = csv.find(",", start);
    if (pos_enter == std::string::npos) {
      pos_enter = csv.length();
    }
    if (pos_comma == std::string::npos || pos_comma > pos_enter) {
      throw std::runtime_error(
          "Error: Missing ','  in line starting at position");
    }
    std::string key = csv.substr(start, pos_comma - start);
    std::string value = csv.substr(pos_comma + 1, pos_enter - (pos_comma + 1));
    input_map(key, value);

    start = pos_enter + 1;
  }
}

bool BitcoinExchange::check_Value(const std::string _val, double* count) {
  char* endptr;
  double val = strtod(_val.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Error : Not a Number" << std::endl;
    return (false);
  } else if (val < 0) {
    std::cerr << "Error : Not a Positive Number." << std::endl;
    return (false);
  } else if (val > INT_MAX) {
    std::cerr << "Error : too large a Number." << std::endl;
    return (false);
  }
  *count = val;
  return (true);
}

double change_number(char** endPtr, std::string value) {
  double re = strtod(value.c_str(), endPtr);

  // std::cout << "endPtr : " << *endPtr << std::endl;
  if (*endPtr == '\0') {
    std::cout << "is '\0";
  }
  return (re);
}

bool check_endPtr(char* end) { return (*end == '\0'); }

bool BitcoinExchange::isLeapYear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool BitcoinExchange::valid_year(int year, int month, int day) {
  if (year < 0 || month < 1 || month > 12 || day < 1) return false;

  int daysInMonth[] = {
      31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  return day <= daysInMonth[month - 1];
}
bool BitcoinExchange::validFormat(std::string date) {
  if (date.length() != 10 || date.at(4) != '-' || date.at(7) != '-')
    return (false);
  std::string _year = date.substr(0, 4);
  std::string _month = date.substr(5, 2);
  std::string _date = date.substr(8, 2);

  int year_int, month_int, date_int;

  char* end;
  year_int = static_cast<int>(change_number(&end, _year));
  if (check_endPtr(end) == false) return (false);
  month_int = static_cast<int>(change_number(&end, _month));
  if (check_endPtr(end) == false) return (false);
  date_int = static_cast<int>(change_number(&end, _date));
  if (check_endPtr(end) == false) return (false);
  if (!valid_year(year_int, month_int, date_int)) return (false);

  return (true);
}

void BitcoinExchange::find_key(std::string& one_line) {
  std::string _date = one_line.substr(0, 10);
  std::string _val = one_line.substr(12, one_line.length());
  double count = 0;
  if (validFormat(_date) == false) {
    std::cerr << "Error: bad input => " << _date << std::endl;
    return;
  } else if (one_line.at(11) != '|') {
    std::cerr << "Error: bad input =>  | is needed" << std::endl;
    return;
  } else if (check_Value(_val, &count) == false) {
    return;
  } else {
    std::map<std::string, double>::iterator it;
    it = this->_csv_keyval.find(_date);
    if (it != this->_csv_keyval.end()) {
      std::cout << _date << " --> " << this->_csv_keyval[_date] * count
                << std::endl;
    } else {
      std::cout << _date << "은(는) 목록에 없습니다" << std::endl;
    }
  }
}

void BitcoinExchange::parseText(const std::string& text) {
  size_t start = 0;
  size_t pos_enter;
  int i = 0;

  while (start < text.length()) {
    pos_enter = text.find("\n", start);

    if (pos_enter == std::string::npos) {
      pos_enter = text.length();
    }

    std::string one_line = text.substr(start, pos_enter - start);

    if (i == 0 && one_line != "date | value")
      throw std::runtime_error("Input.txt is Non-Formal");
    else if (i > 0)
      find_key(one_line);

    start = pos_enter + 1;
    ++i;
    if (pos_enter == text.length()) break;
  }
}

// void BitcoinExchange::parseText(const std::string& text) {
//   size_t start = 0;
//   size_t pos_enter;
//   int i = 0;

//   std::cout << "text.length() : " << text.length() << "\n";

//   while (start < text.length()) {
//     if (pos_enter == std::string::npos) {
//       pos_enter = text.length();
//     }
//     std::cout << "\nstart : " << start << std::endl;
//     std::cout << "pos_enter : " << pos_enter << std::endl;
//     // std::cout << "line count : " << i << std::endl;
//     // std::cout << "key value : " << text << std::endl;
//     std::string one_line = text.substr(start, pos_enter - start);

//     if (i == 0 && one_line != "date | value")
//       throw std::runtime_error("Input.txt is Non-Formal");
//     else if (i > 0)
//       find_key(one_line);
//     start = pos_enter + 1;
//     ++i;
//     if (pos_enter == text.length()) break;
//   }
// }

// bool validNum(std::string& one_line) {
//   const char* _year = (one_line.substr(0, 3)).c_str();
//   const char* _month = (one_line.substr(5, 6)).c_str();
//   const char* _date = (one_line.substr(8, 9)).c_str();
// }

// bool parseOneline(std::string& one_line) {
//   // if (!validFormat(one_line)) return (false);
//   // if (!validNum(one_line)) return (false);
// }

bool BitcoinExchange::check_Date(const std::string file) {
  (void)file;

  return (true);
}

std::string BitcoinExchange::get_input_text() { return (this->_input_text); }
std::string BitcoinExchange::get_csv_text() { return (this->_csv_text); }
