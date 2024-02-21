#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs) { (void)rhs; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
  (void)rhs;
  return (*this);
}

bool BitcoinExchange::check_Date(std::string file) {
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

void BitcoinExchange::parsing_Text() {
  // 개행을 찾고 그 안에서 나눠줘야한다.
  std::string substr = "|";

  size_t pos_bar = this->text.find(substr);
  std::string key = this->text.substr(0, pos_bar);

  size_t pos_enter = this->text.find('\n');
  std::string value = this->text.substr(pos_bar + 1, pos_enter);

  //   std::cout << "key : " << key << std::endl;
  std::cout << "value : " << value << std::endl;

  return;
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