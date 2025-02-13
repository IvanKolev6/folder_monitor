#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>

struct Config {
    std::string watch_folder;
    std::string log_file;
    bool delete_files;
};

class ConfigManager {
public:
    static Config loadConfig(const std::string& config_path);
};

#endif // CONFIG_MANAGER_HPP
