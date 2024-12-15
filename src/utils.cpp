#include "utils.h"

std::string trim(const std::string &str)
{
  size_t first = str.find_first_not_of(" \t");
  if (std::string::npos == first)
  {
    return str;
  }
  size_t last = str.find_last_not_of(" \t");
  return str.substr(first, (last - first + 1));
}

template <typename T>
T parseValue(const std::string &value)
{
  std::stringstream ss(value);
  T result;
  ss >> result;
  if (ss.fail())
  {
    if constexpr (std::is_same_v<T, bool>)
    {
      std::string lowerValue = value;
      std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
      if (lowerValue == "true")
        result = true;
      else if (lowerValue == "false")
        result = false;
      else
        throw std::runtime_error("Invalid boolean value: " + value);
    }
    else
    {
      throw std::runtime_error("Failed to convert value to the required type: " + value);
    }
  }
  return result;
}

std::string generateUUID()
{
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();
  return boost::uuids::to_string(uuid);
}

std::string getContentType(const std::string &extension)
{
  // Text
  if (extension == "txt")
    return "text/plain";
  if (extension == "html")
    return "text/html";
  if (extension == "htm")
    return "text/html";
  if (extension == "css")
    return "text/css";
  if (extension == "js")
    return "application/javascript";
  if (extension == "csv")
    return "text/csv";

  // Images
  if (extension == "jpg" || extension == "jpeg")
    return "image/jpeg";
  if (extension == "png")
    return "image/png";
  if (extension == "gif")
    return "image/gif";
  if (extension == "svg")
    return "image/svg+xml";
  if (extension == "webp")
    return "image/webp";
  if (extension == "bmp")
    return "image/bmp";
  if (extension == "ico")
    return "image/x-icon";

  // Documents
  if (extension == "pdf")
    return "application/pdf";
  if (extension == "docx")
    return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
  if (extension == "xlsx")
    return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
  if (extension == "pptx")
    return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
  if (extension == "doc")
    return "application/msword";
  if (extension == "xls")
    return "application/vnd.ms-excel";
  if (extension == "ppt")
    return "application/vnd.ms-powerpoint";
  if (extension == "odt")
    return "application/vnd.oasis.opendocument.text";
  if (extension == "ods")
    return "application/vnd.oasis.opendocument.spreadsheet";
  if (extension == "odp")
    return "application/vnd.oasis.opendocument.presentation";

  // Archives
  if (extension == "zip")
    return "application/zip";
  if (extension == "rar")
    return "application/x-rar-compressed";
  if (extension == "7z")
    return "application/x-7z-compressed";
  if (extension == "tar")
    return "application/x-tar";
  if (extension == "gz")
    return "application/gzip";

  // Other common types
  if (extension == "json")
    return "application/json";
  if (extension == "xml")
    return "application/xml";
  if (extension == "mp3")
    return "audio/mpeg";
  if (extension == "mp4")
    return "video/mp4";
  if (extension == "avi")
    return "video/x-msvideo";
  if (extension == "mov")
    return "video/quicktime";

  // Default for unknown types
  return "application/octet-stream";
}