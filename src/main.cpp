#include <iostream>
#include "config_manager.hpp"
#include "folder_watcher.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    Config config = ConfigManager::loadConfig(argv[1]);

    FolderWatcher watcher(config);
    watcher.monitor();

    return 0;
}
