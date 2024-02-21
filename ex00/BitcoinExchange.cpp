#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs) { (void)rhs; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
  (void)rhs;
  return (*this);
}

// bool BitcoinExchange::check_Date(std::string file) {}

void BitcoinExchange::check_File(const char file[]) {
  this->fileName = file;
  this->in.open(this->fileName.c_str());
  if (!this->in.is_open()) throw std::runtime_error("Can't Open The File\n");

  this->in.seekg(0, std::ios::end);
  int size = in.tellg();
  this->text.resize(size);
  this->in.seekg(0, std::ios::beg);
  this->in.read(&this->text[0], size);
  std::cout << this->text << std::endl;
}