#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "controller.h"

class FileController : public Controller
{
public:
  std::optional<HttpResponse> handleRequest(const http::request<http::string_body> &req) override;
};

#endif