#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs) { (void)rhs; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
  (void)rhs;
  return (*this);
}

bool BitcoinExchange::check_Date(const std::string file) {
  (void)file;

  // cpp 내장 함수 사용
  //   std::string substr = " | ";
  //   size_t pos = this->text.find(substr);
  //   std::string str = "Hello World\n";
  //   if (pos != std::string::npos) {
  //     std::cout << "Substring '" << substr << "' found at position: " << pos
  //               << std::endl;
  //   }
  return (true);
}

void BitcoinExchange::input_map(std::string key, std::string value) {
  double result = 0;
  char* endPtr;
  result = std::strtod(value.c_str(), &endPtr);
  std::map<std::string, double>::iterator it;

  this->_input_keyval[key] = result;
  std::cout << "Key: " << key << ", Value: " << result << std::endl;
}

void BitcoinExchange::parseText(const std::string& text) {
  size_t start = 0;
  size_t end;
  size_t pos_bar;

  while ((pos_bar = text.find("|", start)) != std::string::npos) {
    end = text.find("\n", pos_bar);
    if (end == std::string::npos) {
      end = text.length();
    }
    std::string key = text.substr(start, pos_bar - start);
    std::string value = text.substr(pos_bar + 1, end - pos_bar - 1);

    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

    input_map(key, value);
    std::cout << "Key: " << key << ", Value: " << value << std::endl;
    start = end + 1;
  }
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

void BitcoinExchange::read_File(std::ifstream& in, std::string& txt) {
  std::stringstream buffer;
  buffer << in.rdbuf();
  txt = buffer.str();
  std::cout << txt << std::endl;
}

void BitcoinExchange::open_input_File(const char file[]) {
  this->_fileName = file;
  this->_input_in.open(this->_fileName.c_str());
  if (!this->_input_in.is_open())
    throw std::runtime_error("Error: could not open file.");

  read_File(this->_input_in, this->_input_text);
}

std::string BitcoinExchange::get_input_text() { return (this->_input_text); }
std::string BitcoinExchange::get_csv_text() { return (this->_csv_text); }