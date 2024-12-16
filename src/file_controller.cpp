#include "file_controller.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileController::FileController(const std::string &uploadDir) : uploadDir_(uploadDir)
{
  std::filesystem::create_directories(uploadDir_);
  std::cout << "FileController created with upload directory: " << uploadDir_ << std::endl;
}

std::optional<HttpResponse> FileController::handleRequest(const http::request<http::string_body> &req)
{
  // GET /k8s
  if (req.method() == http::verb::get && req.target() == "/k8s")
  {
    return HttpResponse{http::status::ok, "Hello, World!"};
  }

  // POST /upload
  if (req.method() == http::verb::post && req.target() == "/upload")
  {
    std::string filename = req.find("X-File-Name")->value();

    if (filename.empty())
    {
      return HttpResponse{http::status::bad_request, "Filename not provided"};
    }

    std::string uuid_str = generateUUID();
    std::string full_path = uploadDir_ + "/" + uuid_str + "_" + filename;
    std::ofstream file(full_path, std::ios::binary);

    if (!file)
    {
      std::cerr << "Error opening file for writing: " << full_path << std::endl;
      return HttpResponse{http::status::internal_server_error, "Error saving file"};
    }

    file << req.body();
    file.close();
    return HttpResponse{http::status::ok, uuid_str};
  }

  // GET /file/:uuid
  if (req.method() == http::verb::get && req.target().rfind("/file/", 0) == 0)
  {
    std::string uuid_str = req.target().substr(6);

    if (!isValidUUID(uuid_str))
    {
      return HttpResponse{http::status::bad_request, "Invalid UUID"};
    }

    std::string filename = uploadDir_ + "/" + uuid_str;

    std::filesystem::directory_iterator it(uploadDir_);
    std::string filePath;
    for (const auto &entry : it)
    {
      if (entry.path().filename().string().rfind(uuid_str, 0) == 0)
      {
        filePath = entry.path().string();
        break;
      }
    }
    if (filePath.empty())
    {
      std::cerr << "Error: File with UUID " << uuid_str << " not found." << std::endl;
      return HttpResponse{http::status::not_found, "File not found"};
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file)
    {
      std::cerr << "Error opening file for reading: " << filePath << std::endl;
      return HttpResponse{http::status::not_found, "File not found"};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
    std::string contentType = getContentType(extension);

    return HttpResponse{http::status::ok, buffer.str(), contentType};
  }

  return std::nullopt;
}