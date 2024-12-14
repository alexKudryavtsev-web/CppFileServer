#include <iostream>
#include <boost/beast/http.hpp>

#include "config.h"
#include "config.cpp"

#include "utils.h"
#include "utils.cpp"

#include "http_response.h"
#include "http_response.cpp"

int main()
{
  try
  {
    Config config(".env");
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << "Failed parse config: " << error.what() << std::endl;
    return 1;
  }
  return 0;
}