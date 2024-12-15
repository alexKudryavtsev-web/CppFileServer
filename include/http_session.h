#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <chrono>
#include "controller.h"

class HttpSession
{
public:
  HttpSession(boost::asio::io_context &ioc, std::shared_ptr<Controller> controller);
  void operator()(boost::asio::ip::tcp::socket socket);

private:
  boost::asio::io_context &ioc_;
  std::shared_ptr<Controller> controller_;
};

#endif