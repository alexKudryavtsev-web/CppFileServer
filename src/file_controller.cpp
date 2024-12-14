#include "file_controller.h"

std::optional<HttpResponse> FileController::handleRequest(const http::request<http::string_body> &req)
{
  if (req.method() == http::verb::get && req.target() == "/k8s")
  {
    return HttpResponse{http::status::ok, "Hello, World!"};
  }
  return std::nullopt;
}