#ifndef __BITCOINEXCHANGE_HPP_
#define __BITCOINEXCHANGE_HPP_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

class BitcoinExchange {
 private:
  BitcoinExchange(const BitcoinExchange &rhs);
  BitcoinExchange &operator=(const BitcoinExchange &rhs);
  std::string _fileName;
  std::string _input_text;
  std::string _csv_text;
  std::ifstream _input_in;
  std::ifstream _csv_in;
  std::ofstream _input_out;
  std::ofstream _csv_out;
  std::map<std::string, double> _input_keyval;
  std::map<std::string, double> _csv_keyval;

 public:
  BitcoinExchange();
  ~BitcoinExchange();
  void open_File(int ac, const char file[]);
  void open_input_File(const char file[]);
  void open_csv_File();
  void read_File(std::ifstream &in, std::string &txt);
  std::string get_input_text();
  std::string get_csv_text();
  bool check_Date(const std::string file);
  bool check_Value(const std::string file);
  void parseText(const std::string &text);
  void input_map(std::string key, std::string value);
};

#endif