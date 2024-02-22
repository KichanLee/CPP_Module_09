#ifndef __BITCOINEXCHANGE_HPP_
#define __BITCOINEXCHANGE_HPP_

#include <cstdlib>
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
  std::map<std::string, double> keyval;

 public:
  BitcoinExchange();
  ~BitcoinExchange();
  void open_File(int ac, const char file[]);
  std::string get_text();
  bool check_Date(const std::string file);
  bool check_Value(const std::string file);
  void parseText(const std::string &text);
  void input_map(std::string key, std::string value);
};

#endif