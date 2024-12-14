
#include "http_response.h"

HttpResponse::HttpResponse(http::status status, std::string body) : status_(status), body_(std::move(body)) {}

http::response<http::string_body> HttpResponse::build() const
{
  http::response<http::string_body> res(status_, 11);
  res.body() = body_;
  res.prepare_payload();
  return res;
}
