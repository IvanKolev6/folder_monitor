#include "config_manager.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

Config ConfigManager::loadConfig(const std::string& config_path) {
    std::ifstream file(config_path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + config_path);
    }

    // Check if the file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("Config file is empty: " + config_path);
    }

    json config_json;
    try {
        file >> config_json;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }

    Config config;
    //config.watch_folder = config_json["watch_folder"].get<std::string>();
    config.watch_folder = "/app/bin/watched_folder";
    config.api_base_url = config_json["api_base_url"].get<std::string>();
    config.username = config_json["username"].get<std::string>();
    config.password = config_json["password"].get<std::string>();
    //config.upload_strategy = config_json["upload_strategy"].get<std::string>();
    config.upload_strategy = "direct";

    std::cout << "Config Loaded: Watching " << config.watch_folder << std::endl;

    return config;
}
