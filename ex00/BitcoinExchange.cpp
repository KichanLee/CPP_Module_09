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

  this->keyval[key] = result;
  std::cout << "Key: " << key << ", Value: " << result << std::endl;
}

void BitcoinExchange::parseText(const std::string& text) {
  size_t start = 0;
  size_t end;
  size_t pos_bar;

  while ((pos_bar = text.find("|", start)) != std::string::npos) {
    end = text.find("\n", pos_bar);
    if (end == std::string::npos) {
      end = text.length();  // 마지막 줄인 경우
    }

    std::string key = text.substr(start, pos_bar - start);
    std::string value = text.substr(pos_bar + 1, end - pos_bar - 1);

    // 공백 제거 (옵션)
    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

    input_map(key, value);
    std::cout << "Key: " << key << ", Value: " << value << std::endl;
    start = end + 1;
  }
}

void BitcoinExchange::open_File(int ac, const char file[]) {
  if (ac != 2) throw std::runtime_error("Error: could not open file.");

  this->fileName = file;
  this->in.open(this->fileName.c_str());
  if (!this->in.is_open())
    throw std::runtime_error("Error: could not open file.");

  this->in.seekg(0, std::ios::end);
  int size = in.tellg();
  this->text.resize(size);
  this->in.seekg(0, std::ios::beg);
  this->in.read(&this->text[0], size);
  std::cout << this->text << std::endl;
}

std::string BitcoinExchange::get_text() { return (this->text); }