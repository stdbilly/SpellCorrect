#pragma once
#include <iostream>
#include <string>
using std::string;

namespace wd {

size_t getBytes(const char ch);
size_t length(const string &str);
int tripleMin(const int &a, const int &b, const int &c);
int editDistance(const string &lhs, const string &rhs);
}  // namespace wd