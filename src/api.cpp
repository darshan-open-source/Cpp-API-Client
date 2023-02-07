#include "api.h"
#include <nlohmann/json.hpp>
#include "common.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{

    std::string *mains = (std::string *)(userdata);
    string s;
    s.append(ptr, (size * nmemb));

    mains->append(s);

    return size * nmemb;
}
static size_t header_callback(char *buffer, size_t size,
                              size_t nitems, void *userdata)
{

    json *j = (json *)userdata;

    string s = string(buffer, size * nitems);

    
    s.erase(s.length() - 2, 4);
    int x = s.find(':', 0);
    if (x == std::string::npos)
    {
        // string is mainline
        std::vector<std::string> x = split(s, ' ');

        if (x.size() == 3)
        {

            (*j)["HTTP_VERSION"] = x.at(0);
            (*j)["HTTP_STATUS_CODE"] = x.at(1);
            (*j)["HTTP_STATUS_LINE"] = x.at(2);
        }
    }
    else
    {
        // string is subline

        std::vector<std::string> x = split(s, ':');
        if (x.size() == 2)
        {
            (*j)[stripString(x.at(0))] = stripString(x.at(1));
        }
    }

    return nitems * size;
}

nlohmann::json API::get(std::string url, nlohmann::json http_header)
{
    json main_json;
    struct curl_slist *http_headers = NULL;
    CURL *curl = curl_easy_init();

    if (http_header != 0)
    {

        for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
        {
            std::string header_line = it.key();
            header_line += " : ";
            header_line += it.value();
            http_headers = curl_slist_append(http_headers, header_line.c_str());
        }

        if (http_headers != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
        }
    }
    string sx;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);

    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
}

nlohmann::json API::Delete(std::string url, nlohmann::json http_header)
{

    nlohmann::json main_json;

    CURL *curl = curl_easy_init();
    struct curl_slist *http_headers = NULL;

    for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += " :";
        header_line += it.value();
        http_headers = curl_slist_append(http_headers, header_line.c_str());
    }

    if (http_headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
    }

    string sx;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
};

nlohmann::json API::option(std::string url, nlohmann::json http_header)
{
    json main_json;
    struct curl_slist *http_headers = NULL;
    CURL *curl = curl_easy_init();

    if (http_header != 0)
    {

        for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
        {
            std::string header_line = it.key();
            header_line += " : ";
            header_line += it.value();
            http_headers = curl_slist_append(http_headers, header_line.c_str());
        }

        if (http_headers != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
        }
    }
    string sx;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");

    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
}
nlohmann::json API::head(std::string url, nlohmann::json http_header)
{
    json main_json;
    struct curl_slist *http_headers = NULL;
    CURL *curl = curl_easy_init();

    if (http_header != 0)
    {

        for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
        {
            std::string header_line = it.key();
            header_line += " : ";
            header_line += it.value();
            http_headers = curl_slist_append(http_headers, header_line.c_str());
        }

        if (http_headers != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
        }
    }
    string sx;
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);

    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
}
nlohmann::json API::post(std::string url, nlohmann::json data, nlohmann::json http_header)
{

    nlohmann::json main_json;

    CURL *curl = curl_easy_init();
    struct curl_slist *http_headers = NULL;

    for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += " :";
        header_line += it.value();
        http_headers = curl_slist_append(http_headers, header_line.c_str());
    }

    if (http_headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
    }

    std::string post_field_data = "";
    for (json::iterator it = data.begin(); it != data.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += "=";
        header_line += it.value();
        header_line += "&";
        post_field_data.append(header_line);
    }
    post_field_data.erase(post_field_data.end() - 1);

    if (!post_field_data.empty())
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_field_data.c_str());
    }

    string sx;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
};
nlohmann::json API::post(std::string url, std::string data, nlohmann::json http_header)
{

    nlohmann::json main_json;

    CURL *curl = curl_easy_init();
    struct curl_slist *http_headers = NULL;

    for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += " :";
        header_line += it.value();
        http_headers = curl_slist_append(http_headers, header_line.c_str());
    }

    if (http_headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
    }

    std::string post_field_data = "";

    if (!data.empty())
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    string sx;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
};
nlohmann::json API::put(std::string url, std::string data, nlohmann::json http_header)
{

    nlohmann::json main_json;

    CURL *curl = curl_easy_init();
    struct curl_slist *http_headers = NULL;

    for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += " :";
        header_line += it.value();
        http_headers = curl_slist_append(http_headers, header_line.c_str());
    }

    if (http_headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
    }

    if (!data.empty())
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    string sx;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
};
nlohmann::json API::patch(std::string url, std::string data, nlohmann::json http_header)
{

    nlohmann::json main_json;

    CURL *curl = curl_easy_init();
    struct curl_slist *http_headers = NULL;

    for (json::iterator it = http_header.begin(); it != http_header.end(); ++it)
    {
        std::string header_line = it.key();
        header_line += " :";
        header_line += it.value();
        http_headers = curl_slist_append(http_headers, header_line.c_str());
    }

    if (http_headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
    }

    if (!data.empty())
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    string sx;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &main_json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sx);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res = curl_easy_perform(curl);

    main_json["Error"] = true;
    if (res != CURLE_OK)
    {
        main_json["data"] = 0;
    }
    else
    {
        main_json["Error"] = false;
        try
        {
            main_json["data"] = json::parse(sx);
        }
        catch (nlohmann::detail::parse_error &pe)
        {
            main_json["data"] = sx;
        }
    }
    curl_easy_cleanup(curl);
    return main_json;
};

nlohmann::json fetch(std::string url, std::string method, std::string data, nlohmann::json headers)
{
    if (method.compare("POST") == 0)
    {

        return API::post(url, data, headers);
    }
    else if (method.compare("PUT") == 0)
    {
        return API::put(url, data, headers);
    }
    else if (method.compare("DELETE") == 0)
    {
        return API::Delete(url, headers);
    }
    else if (method.compare("OPTION") == 0)
    {
        return API::option(url, headers);
    }
    else if (method.compare("PATCH") == 0)
    {
        return API::patch(url, data, headers);
    }

    else if (method.compare("HEAD") == 0)
    {
        return API::head(url, headers);
    }
    else
    {
        try
        {
            json datax = json::parse(data);
            std::string murl = url;
            if (datax != 0)
            {
                murl += "?";
                for (json::iterator it = datax.begin(); it != datax.end(); ++it)
                {
                    std::string header_line = it.key();
                    header_line += "=";
                    header_line += it.value();
                    header_line += "&";
                    murl.append(header_line);
                }
                murl.erase(murl.end() - 1);
            }

            return API::get(murl, headers);
        }
        catch (std::exception &e)
        {

            return API::get(url, headers);
        }
    }
}