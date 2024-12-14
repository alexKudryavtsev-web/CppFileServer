#include "utils.h"

std::string trim(const std::string &str)
{
  size_t first = str.find_first_not_of(" \t");
  if (std::string::npos == first)
  {
    return str;
  }
  size_t last = str.find_last_not_of(" \t");
  return str.substr(first, (last - first + 1));
}

template <typename T>
T parseValue(const std::string &value)
{
  std::stringstream ss(value);
  T result;
  ss >> result;
  if (ss.fail())
  {
    if constexpr (std::is_same_v<T, bool>)
    {
      std::string lowerValue = value;
      std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
      if (lowerValue == "true")
        result = true;
      else if (lowerValue == "false")
        result = false;
      else
        throw std::runtime_error("Invalid boolean value: " + value);
    }
    else
    {
      throw std::runtime_error("Failed to convert value to the required type: " + value);
    }
  }
  return result;
}