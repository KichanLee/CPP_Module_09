#ifndef __BITCOINEXCHANGE_HPP_
#define __BITCOINEXCHANGE_HPP_

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class BitcoinExchange {
 private:
  BitcoinExchange(const BitcoinExchange &rhs);
  BitcoinExchange &operator=(const BitcoinExchange &rhs);
  std::string fileName;
  std::string text;
  std::ifstream in;
  std::ofstream out;
  std::map<std::string, int> keyval;

 public:
  BitcoinExchange();
  ~BitcoinExchange();
  void open_File(const char file[]);
  bool check_Date(std::string file);
  bool check_Value(std::string file);
};

#endif