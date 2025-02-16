#include "token_manager.hpp"
#include "server_query.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

using json = nlohmann::json;

TokenManager::TokenManager(const Config& cfg) : config(cfg), home_folder_id(-1), server_query(std::make_unique<ServerQuery>(cfg.api_base_url)) {
    authenticate();
    fetchUserInfo();
}

void TokenManager::authenticate() {
    std::string endpoint = "/token";
    std::string post_fields = "grant_type=password&username=" + config.username + "&password=" + config.password;

    std::string response = server_query->post(endpoint, post_fields, "");

    auto json_response = json::parse(response);

    if (json_response.contains("access_token")) {
        access_token = json_response["access_token"].get<std::string>();
        std::cout << "Access Token: " << access_token << std::endl;
    } else {
        throw std::runtime_error("Invalid JSON response from server.");
    }
}

void TokenManager::fetchUserInfo() {
    std::string endpoint = "/users/self";
    std::string response = server_query->get(endpoint, access_token);

    auto json_response = json::parse(response);

    if (json_response.contains("homeFolderID")) {
        home_folder_id = json_response["homeFolderID"].get<int>();
        std::cout << "Home Folder ID: " << home_folder_id << std::endl;
    } else {
        throw std::runtime_error("Invalid JSON response or missing homeFolderID.");
    }
}

std::string TokenManager::getAccessToken() {
    return access_token;
}

int TokenManager::getHomeFolderID() {
    return home_folder_id;
}