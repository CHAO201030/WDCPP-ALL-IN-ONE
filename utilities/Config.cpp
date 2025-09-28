#include "./include/Config.h"

Config* Config::_ptr = nullptr;

Config::Config()
{
    std::ifstream ifs("./config.cfg");
    std::string line;

    while(std::getline(ifs, line))
    {
        auto sharp_pos = line.find("#");
        if(sharp_pos != std::string::npos)
        {
            line.erase(sharp_pos);
            if(line.empty()) continue;
        }

        auto equal_pos = line.find("=");
        if(equal_pos == std::string::npos)
        {
            std::cout << "Config Error : " << line << "\n";
            continue;
        }
        
        line.replace(equal_pos, 1, " ");

        std::istringstream iss(line);
        std::string key, value;

        iss >> key >> value;

        _cfg[key] = value;
    }

    ifs.close();
}

Config* Config::getInstance()
{
    if(_ptr == nullptr) _ptr = new Config();
    return _ptr;
}

void Config::delInstance()
{
    if(_ptr)
    {
        delete _ptr;
        _ptr = nullptr;
    }
}

std::string Config::getConfig(std::string name)
{
    auto mit = _cfg.find(name);

    if(mit != _cfg.end())
    {
        return mit->second;
    }
    else
    {
        return {};
    }
}