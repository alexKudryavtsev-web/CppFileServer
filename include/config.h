#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <stdexcept>
#include <map>

class Config {
public:
    Config(const std::string& envFilePath);
    std::string getFileStorage() const;
    std::string getLogLevel() const;
    int getHttpPort() const;
    bool getDebugMode() const;

private:
    std::string fileStorage;
    int httpPort;
    std::string logLevel;
    bool debugMode;
    std::map<std::string, std::string> configMap;

    std::string trim(const std::string& str) const;
    template <typename T>
    T parseValue(const std::string& value) const;
};

#endif