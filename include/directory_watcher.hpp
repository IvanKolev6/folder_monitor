#ifndef DIRECTORY_WATCHER_HPP
#define DIRECTORY_WATCHER_HPP

#include <string>
#include <functional>

class DirectoryWatcher {
public:
    explicit DirectoryWatcher(const std::string& folder_path);

    void startWatching(const std::function<void(const std::string&)>& onFileDetected);

private:
    std::string folder_path;
};

#endif
