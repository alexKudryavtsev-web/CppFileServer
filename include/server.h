#ifndef SERVER_H
#define SERVER_H

#include <boost/asio/io_context.hpp>
#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include "controller.h"

class Server
{
public:
  Server(unsigned short port, std::shared_ptr<Controller> controller);
  void run();

private:
  unsigned short port_;
  boost::asio::io_context ioc_;
  std::shared_ptr<Controller> controller_;
};

#endif