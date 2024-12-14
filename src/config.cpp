#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

string Config::trim(const string &str) const
{
  size_t first = str.find_first_not_of(" \t");
  if (string::npos == first)
  {
    return str;
  }
  size_t last = str.find_last_not_of(" \t");
  return str.substr(first, (last - first + 1));
}

template <typename T>
T Config::parseValue(const string &value) const
{
  stringstream ss(value);
  T result;
  ss >> result;
  if (ss.fail())
  {
    if constexpr (is_same_v<T, bool>)
    {
      string lowerValue = value;
      transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
      if (lowerValue == "true")
        result = true;
      else if (lowerValue == "false")
        result = false;
      else
        throw runtime_error("Invalid boolean value: " + value);
    }
    else
    {
      throw runtime_error("Failed to convert value to the required type: " + value);
    }
  }
  return result;
}

Config::Config(const string &envFilePath) : httpPort(8080), debugMode(false), logLevel("info")
{
  ifstream envFile(envFilePath);
  if (!envFile.is_open())
  {
    throw runtime_error("Could not open .env file: " + envFilePath);
  }

  string line;
  while (getline(envFile, line))
  {
    size_t commentPos = line.find('#');
    if (commentPos != string::npos)
    {
      line = line.substr(0, commentPos);
    }
    line = trim(line);

    if (line.empty())
      continue;

    size_t eqPos = line.find('=');
    if (eqPos == string::npos)
    {
      throw runtime_error("Incorrect line in .env file: " + line);
    }

    string key = trim(line.substr(0, eqPos));
    string value = trim(line.substr(eqPos + 1));
    configMap[key] = value;
  }

  try
  {
    fileStorage = configMap.at("FILE_STORAGE");
    httpPort = parseValue<int>(configMap.at("HTTP_PORT"));
    logLevel = configMap.at("LOG_LEVEL");
    debugMode = parseValue<bool>(configMap.at("DEBUG_MODE"));
  }
  catch (const out_of_range &oor)
  {
    cerr << "Warning: Configuration key '" << oor.what() << "' not found. Using defaults." << endl;
  }
  catch (const runtime_error &re)
  {
    throw;
  }
}

string Config::getFileStorage() const
{
  return this->fileStorage;
}

string Config::getLogLevel() const
{
  return this->logLevel;
}

int Config::getHttpPort() const
{
  return this->httpPort;
}

bool Config::getDebugMode() const
{
  return this->debugMode;
}