#include "file_service.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

FileService::FileService(const std::string &uploadDir) : uploadDir_(uploadDir)
{
  std::filesystem::create_directories(uploadDir_);
  std::cout << "FileService created with upload directory: " << uploadDir_ << std::endl;
}

std::optional<std::pair<std::string, std::string>> FileService::uploadFile(const std::string &filename, const std::string &data)
{
  if (filename.empty())
  {
    return std::nullopt;
  }

  std::string uuid_str = generateUUID();
  std::string full_path = uploadDir_ + "/" + uuid_str + "_" + filename;
  std::ofstream file(full_path, std::ios::binary);

  if (!file)
  {
    std::cerr << "Error opening file for writing: " << full_path << std::endl;
    return std::nullopt;
  }

  file << data;
  file.close();
  return std::make_pair(uuid_str, full_path);
}

std::optional<std::pair<std::string, std::string>> FileService::getFile(const std::string &uuid)
{
  if (!isValidUUID(uuid))
  {
    return std::nullopt;
  }

  std::string filePath;
  for (const auto &entry : std::filesystem::directory_iterator(uploadDir_))
  {
    if (entry.path().filename().string().rfind(uuid, 0) == 0)
    {
      filePath = entry.path().string();
      break;
    }
  }

  if (filePath.empty())
  {
    std::cerr << "Error: File with UUID " << uuid << " not found." << std::endl;
    return std::nullopt;
  }

  std::ifstream file(filePath, std::ios::binary);
  if (!file)
  {
    std::cerr << "Error opening file for reading: " << filePath << std::endl;
    return std::nullopt;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
  return std::make_pair(buffer.str(), getContentType(extension));
}
