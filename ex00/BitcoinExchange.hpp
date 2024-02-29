#ifndef __BITCOINEXCHANGE_HPP_
#define __BITCOINEXCHANGE_HPP_

#include <cstdlib>
#include <fstream>
#include <iomanip>
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
  bool check_Value(const std::string file, double *count);
  void parseText(const std::string &text);
  void parseCsv(const std::string &csv);
  void input_map(std::string key, std::string value);
  bool isLeapYear(int year);
  bool valid_year(int year, int month, int day);
  void find_key(std::string &one_line);
  bool validFormat(std::string date);
  void find_closest_date(const std::string &target_date, double count);
  void print_decimal(double num);
};

#endif