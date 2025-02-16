#ifndef SERVER_QUERY_HPP
#define SERVER_QUERY_HPP

#include <string>
#include <curl/curl.h>

class ServerQuery {
public:
    ServerQuery(const std::string& base_url);
    ~ServerQuery();

    std::string post(const std::string& endpoint, const std::string& data, const std::string& token);
    std::string get(const std::string& endpoint, const std::string& token);
    bool uploadFile(const std::string& endpoint, const std::string& file_path, const std::string& token);


private:
    std::string base_url;
    CURL* curl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
};

#endif // SERVER_QUERY_HPP
