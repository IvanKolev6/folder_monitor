#include "folder_watcher.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <unordered_set>
#include <fstream>

namespace fs = std::filesystem;

FolderWatcher::FolderWatcher(const Config& cfg) : config(cfg) {}

void FolderWatcher::monitor() {
    std::unordered_set<std::string> known_files;

    // Load existing files
    for (const auto& entry : fs::directory_iterator(config.watch_folder)) {
        known_files.insert(entry.path().string());
    }

    while (true) {
        for (const auto& entry : fs::directory_iterator(config.watch_folder)) {
            std::string file_path = entry.path().string();

            if (known_files.find(file_path) == known_files.end()) {
                std::cout << "New file detected: " << file_path << std::endl;

                std::ofstream log(config.log_file, std::ios::app);
                log << "Detected: " << file_path << std::endl;
                log.close();

                if (config.delete_files) {
                    fs::remove(file_path);
                    std::cout << "Deleted: " << file_path << std::endl;
                }

                known_files.insert(file_path);
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
