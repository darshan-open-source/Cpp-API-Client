#pragma once
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>


namespace API
{


    extern nlohmann::json get(std::string url, nlohmann::json http_header = 0);
     extern nlohmann::json Delete(std::string url, nlohmann::json http_header = 0);
    extern nlohmann::json option(std::string url, nlohmann::json http_header = 0);

    extern nlohmann::json head(std::string url, nlohmann::json http_header = 0);

    extern nlohmann::json post(std::string url, nlohmann::json data = 0, nlohmann::json http_header = 0);
    extern nlohmann::json post(std::string url,std::string data = 0, nlohmann::json http_header = 0);

    extern nlohmann::json put(std::string url, std::string data = 0, nlohmann::json http_header = 0);
    extern nlohmann::json patch(std::string url, std::string data = 0, nlohmann::json http_header = 0);


    extern nlohmann::json fetch(std::string url, std::string method, nlohmann::json data = 0, nlohmann::json headers = 0);
};

