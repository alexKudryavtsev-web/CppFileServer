
#include "http_response.h"

HttpResponse::HttpResponse(http::status status, std::string body, std::string contentType) : status_(status), body_(std::move(body)), contentType_(std::move(contentType)) {}

http::response<http::string_body> HttpResponse::build() const
{
  http::response<http::string_body> res(status_, 11);
  res.body() = body_;
  res.prepare_payload();
  res.set(http::field::content_type, contentType_);
  return res;
}
