#include "file_controller.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileController::FileController(const std::string &uploadDir) : uploadDir_(uploadDir)
{
  std::filesystem::create_directories(uploadDir_); // Создаем директорию, если ее нет
  std::cout << "FileController created with upload directory: " << uploadDir_ << std::endl;
}

std::optional<HttpResponse> FileController::handleRequest(const http::request<http::string_body> &req)
{
  // GET /k8s
  if (req.method() == http::verb::get && req.target() == "/k8s")
  {
    return HttpResponse{http::status::ok, "Hello, World!"};
  }

  // PODT /upload
  if (req.method() == http::verb::post && req.target() == "/upload")
  {
    std::string uuid_str = generateUUID();
    std::string filename = uploadDir_ + "/" + uuid_str;
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
      std::cerr << "Error opening file for writing: " << filename << std::endl;
      return HttpResponse{http::status::internal_server_error, "Error saving file"};
    }

    file << req.body();
    file.close();
    return HttpResponse{http::status::ok, uuid_str};
  }

  // GET /file/:uuid
  if (req.method() == http::verb::get && req.target().rfind("/file/", 0) == 0)
  {
    std::string uuid_str = req.target().substr(6); // Извлекаем UUID из пути
    std::string filename = uploadDir_ + "/" + uuid_str;
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
      std::cerr << "Error opening file for reading: " << filename << std::endl;
      return HttpResponse{http::status::not_found, "File not found"};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return HttpResponse{http::status::ok, buffer.str()};
  }

  return std::nullopt;
}