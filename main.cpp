#include <iostream>
#include "config.h"
#include "config.cpp"

#include "utils.h"
#include "utils.cpp"

int main()
{
  try
  {
    Config config(".env");
    std::cout << "FILE_STORAGE: " << config.getFileStorage() << std::endl;
    std::cout << "HTTP_PORT: " << config.getHttpPort() << std::endl;
    std::cout << "LOG_LEVEL: " << config.getLogLevel() << std::endl;
    std::cout << "DEBUG_MODE: " << config.getDebugMode() << std::endl;
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << "Failed parse config: " << error.what() << std::endl;
    return 1;
  }
  return 0;
}