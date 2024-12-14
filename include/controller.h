#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <boost/beast/http.hpp>
#include <optional>
#include "http_response.h"

namespace beast = boost::beast;
namespace http = beast::http;

class Controller {
public:
  virtual ~Controller() = default;
  virtual std::optional<HttpResponse> handleRequest(const http::request<http::string_body>& req) = 0;
};

#endif