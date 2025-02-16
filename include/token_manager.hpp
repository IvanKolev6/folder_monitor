#ifndef TOKEN_MANAGER_HPP
#define TOKEN_MANAGER_HPP

#include "config_manager.hpp"
#include "server_query.hpp"
#include <string>
#include <memory>

class TokenManager {
public:
    TokenManager(const Config& config);

    std::string getAccessToken();
    int getHomeFolderID();

private:
    Config config;
    std::string access_token;
    int home_folder_id;
    std::unique_ptr<ServerQuery> server_query;

    void authenticate();
    void fetchUserInfo();
};

#endif // TOKEN_MANAGER_HPP
