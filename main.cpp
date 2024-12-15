#include <iostream>

#include "config.h"
#include "config.cpp"

#include "utils.h"
#include "utils.cpp"

#include "http_response.h"
#include "http_response.cpp"

#include "controller.h"
#include "file_controller.h"
#include "file_controller.cpp"

#include "server.h"
#include "server.cpp"

#include "http_session.h"
#include "http_session.cpp"

int main()
{
  try
  {
    Config config(".env");
    std::cout << "Loaded config" << std::endl;
    auto controller = std::make_shared<FileController>(config.getFileStorage());

    Server server(config.getHttpPort(), controller);
    server.run();
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << "Failed parse config: " << error.what() << std::endl;
    return 1;
  }
  return 0;
}