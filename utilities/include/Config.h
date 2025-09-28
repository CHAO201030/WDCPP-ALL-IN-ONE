#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "utilities.h"

class Config
{
public:
    static Config* getInstance();
    std::string getConfig(std::string name);
    void delInstance();

private:
    Config();
    Config(const Config & rhs) = delete;
    Config(const Config && rhs) = delete;
    Config & operator=(const Config & rhs) = delete;
    Config & operator=(const Config && rhs) = delete;

private:
    static Config * _ptr;
    std::unordered_map<std::string, std::string> _cfg;
};

#endif