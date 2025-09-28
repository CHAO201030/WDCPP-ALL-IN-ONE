#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<utility>
#include<functional>
#include<memory>

namespace ds_utilities
{

    enum STATUS
    {
        OK=1,
        False
    };

    struct MicroServiceInfo{
        std::string service_name;
        std::string ip;
        std::string port;
        std::string version;
        STATUS status;
    };   


};

#endif