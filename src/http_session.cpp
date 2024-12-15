#include "http_session.h"
#include <iostream>
#include <boost/beast/core/flat_buffer.hpp>

HttpSession::HttpSession(boost::asio::io_context &ioc, std::shared_ptr<Controller> controller) : ioc_(ioc), controller_(controller) {}

void HttpSession::operator()(boost::asio::ip::tcp::socket socket)
{
  boost::beast::tcp_stream stream(std::move(socket));
  stream.expires_after(std::chrono::seconds(30));
  boost::beast::flat_buffer buffer;
  boost::beast::error_code ec;

  boost::beast::http::request<boost::beast::http::string_body> req;
  boost::beast::http::read(stream, buffer, req, ec);

  if (ec == boost::beast::http::error::end_of_stream)
  {
    std::cerr << "Client closed connection prematurely.\n";
    return;
  }
  else if (ec)
  {
    std::cerr << "Error reading request: " << ec.message() << "\n";
    return;
  }

  std::cout << "Request received: " << req.method_string() << " " << req.target() << std::endl;

  auto response = controller_->handleRequest(req);
  if (response)
  {
    boost::beast::error_code ec;
    boost::beast::http::write(stream, response->build(), ec);
    if (ec)
    {
      std::cerr << "Error writing response: " << ec.message() << "\n";
    }
  }
  else
  {
    std::cerr << "Controller returned empty response\n";
  }

  stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
  stream.socket().close(ec);
}