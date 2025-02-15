#include "token_manager.hpp"
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

TokenManager::TokenManager(const Config& cfg) : config(cfg), home_folder_id(-1) {
    authenticate();
    fetchUserInfo();
}

void TokenManager::authenticate() {
    httplib::Client cli(config.api_base_url.c_str());

    std::string post_fields = "grant_type=password&username=" + config.username + "&password=" + config.password;

    auto res = cli.Post("/token", post_fields, "application/x-www-form-urlencoded");

    if (!res || res->status != 200) {
        throw std::runtime_error("Authentication failed! HTTP Status: " + (res ? std::to_string(res->status) : "No response"));
    }

    auto json_response = json::parse(res->body);
    access_token = json_response["access_token"].get<std::string>();
}

void TokenManager::fetchUserInfo() {
    httplib::Client cli(config.api_base_url.c_str());

    httplib::Headers headers = {
        {"Authorization", "Bearer " + access_token}
    };

    auto res = cli.Get("/users/self", headers);

    if (!res || res->status != 200) {
        throw std::runtime_error("Fetching user info failed! HTTP Status: " + (res ? std::to_string(res->status) : "No response"));
    }

    auto json_response = json::parse(res->body);
    home_folder_id = json_response["homeFolderID"];
}

std::string TokenManager::getAccessToken() {
    return access_token;
}

int TokenManager::getHomeFolderID() {
    return home_folder_id;
}
