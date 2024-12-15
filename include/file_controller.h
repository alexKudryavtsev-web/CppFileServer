#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "controller.h"
#include <boost/beast/http.hpp>
#include <optional>
#include <string>
#include <filesystem>

namespace beast = boost::beast;
namespace http = beast::http;

class FileController : public Controller
{
public:
  FileController(const std::string &uploadDir);
  std::optional<HttpResponse> handleRequest(const http::request<http::string_body> &req) override;

private:
  std::string uploadDir_;
};

#endif