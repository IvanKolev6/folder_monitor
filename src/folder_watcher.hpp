#ifndef FOLDER_WATCHER_HPP
#define FOLDER_WATCHER_HPP

#include "config_manager.hpp"

class FolderWatcher {
public:
    explicit FolderWatcher(const Config& config);
    void monitor();
    
private:
    Config config;
};

#endif // FOLDER_WATCHER_HPP
