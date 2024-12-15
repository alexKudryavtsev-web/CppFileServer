#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

std::string trim(const std::string &str);

template <typename T>
T parseValue(const std::string &value);

std::string generateUUID();

#endif