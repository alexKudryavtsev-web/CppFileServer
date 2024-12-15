#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

class HttpResponse
{
public:
  HttpResponse(http::status status, std::string body = "", std::string contentType = "");
  http::response<http::string_body> build() const;

private:
  http::status status_;
  std::string body_;
  std::string contentType_;
};

#endif