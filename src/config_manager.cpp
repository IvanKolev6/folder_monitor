#include "config_manager.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config ConfigManager::loadConfig(const std::string& config_path) {
    Config config;
    std::ifstream file(config_path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << config_path << std::endl;
        return config;
    }

    json config_json;
    file >> config_json;

    config.watch_folder = config_json["watch_folder"].get<std::string>();
    config.api_base_url = config_json["api_base_url"].get<std::string>();
    config.username = config_json["username"].get<std::string>();
    config.password = config_json["password"].get<std::string>();
    config.log_file = config_json["log_file"].get<std::string>();
    config.log_file = config_json["upload_strategy"].get<std::string>();

    std::cout << "Config Loaded: Watching " << config.watch_folder << std::endl;

    return config;
}
