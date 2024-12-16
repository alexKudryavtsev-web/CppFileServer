#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <string>
#include <optional>
#include <utility>
#include "utils.h"

class FileService
{
public:
  FileService(const std::string &uploadDir);
  std::optional<std::pair<std::string, std::string>> uploadFile(const std::string &filename, const std::string &data);
  std::optional<std::pair<std::string, std::string>> getFile(const std::string &uuid);

private:
  std::string uploadDir_;
};

#endif