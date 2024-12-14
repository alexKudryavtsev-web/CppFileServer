#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

std::string trim(const std::string &str);

template <typename T>
T parseValue(const std::string &value);

#endif