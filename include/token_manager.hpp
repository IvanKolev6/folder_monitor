#ifndef TOKEN_MANAGER_HPP
#define TOKEN_MANAGER_HPP

#include "config_manager.hpp"
#include <string>

class TokenManager {
public:
    TokenManager(const Config& config);

    std::string getAccessToken();
    int getHomeFolderID();

private:
    Config config;
    std::string access_token;
    int home_folder_id;

    void authenticate();
    void fetchUserInfo();
};

#endif
