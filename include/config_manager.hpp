#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>

struct Config {
    std::string watch_folder;
    std::string api_base_url;
    std::string username;
    std::string password;
    std::string upload_strategy; 
};

class ConfigManager {
public:
    static Config loadConfig(const std::string& config_path);
};

#endif // CONFIG_MANAGER_HPP
