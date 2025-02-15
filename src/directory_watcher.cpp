#include "directory_watcher.hpp"
#include <filesystem>
#include <thread>
#include <chrono>
#include <iostream>
#include <set>

namespace fs = std::filesystem;

DirectoryWatcher::DirectoryWatcher(const std::string& path) : folder_path(path) {}

void DirectoryWatcher::startWatching(const std::function<void(const std::string&)>& onFileDetected) {
    std::set<std::string> known_files;

    // Pre-load existing files
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            known_files.insert(entry.path().string());
        }
    }

    std::cout << "Watching folder: " << folder_path << std::endl;

    while (true) {
        for (const auto& entry : fs::directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
                const std::string file_path = entry.path().string();

                if (known_files.find(file_path) == known_files.end()) {
                    known_files.insert(file_path);
                    std::cout << "New file detected: " << file_path << std::endl;
                    onFileDetected(file_path);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Adjust polling interval
    }
}
