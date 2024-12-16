#include "file_controller.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileController::FileController(const std::string &uploadDir) : fileService_(uploadDir)
{
  std::filesystem::create_directories(uploadDir);
  std::cout << "FileController created with upload directory: " << uploadDir << std::endl;
}

std::optional<HttpResponse> FileController::handleRequest(const http::request<http::string_body> &req)
{
  if (req.method() == http::verb::get && req.target() == "/k8s")
  {
    return HttpResponse{http::status::ok, "Hello, World!"};
  }

  if (req.method() == http::verb::post && req.target() == "/upload")
  {
    std::string filename = req.find("X-File-Name")->value();
    auto result = fileService_.uploadFile(filename, req.body());
    if (result)
    {
      return HttpResponse{http::status::ok, result->first};
    }
    else
    {
      return HttpResponse{http::status::bad_request, "Error uploading file"};
    }
  }

  if (req.method() == http::verb::get && req.target().rfind("/file/", 0) == 0)
  {
    std::string uuid_str = req.target().substr(6);
    auto result = fileService_.getFile(uuid_str);
    if (result)
    {
      return HttpResponse{http::status::ok, result->first, result->second};
    }
    else
    {
      return HttpResponse{http::status::not_found, "File not found"};
    }
  }

  return std::nullopt;
}
