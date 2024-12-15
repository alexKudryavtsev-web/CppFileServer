#include "server.h"
#include "http_session.h"
#include <iostream>
#include <thread>
#include <boost/asio/ip/tcp.hpp>

Server::Server(unsigned short port, std::shared_ptr<Controller> controller) : port_(port), controller_(controller)
{
  std::cout << "Server created on port " << port_ << std::endl;
}

void Server::run()
{
  boost::asio::ip::tcp::acceptor acceptor(ioc_, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_));
  std::cout << "Server listening on port " << port_ << std::endl;

  for (;;)
  {
    boost::asio::ip::tcp::socket socket(ioc_);
    acceptor.accept(socket);
    std::cout << "Accepted connection from " << socket.remote_endpoint().address().to_string() << std::endl;
    auto session = std::make_shared<HttpSession>(ioc_, controller_);
    std::thread([s = std::move(socket), session]() mutable
                {
            std::cout << "Starting session thread" << std::endl;
            (*session)(std::move(s));
            std::cout << "Session thread finished" << std::endl; })
        .detach();
  }
}