#include <iostream>
#include <functional>

#include "config_manager.hpp"
#include "token_manager.hpp"
#include "file_uploader.hpp"
#include "upload_strategy.hpp"
#include "directory_watcher.hpp"

void handleNewFileFromWatcher(FileUploader& uploader, const std::string& file_path) {
    uploader.handleNewFile(file_path); 
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    Config config = ConfigManager::loadConfig(argv[1]);

    TokenManager token_manager(config);

    std::unique_ptr<UploadStrategy> upload_strategy = UploadStrategy::create(config.upload_strategy, config.api_base_url);
    if (!upload_strategy) {
        std::cerr << "Invalid upload strategy type: " << config.upload_strategy << std::endl;
        return 1;
    }

    FileUploader uploader(token_manager, std::move(upload_strategy));

    DirectoryWatcher watcher(config.watch_folder);

    watcher.startWatching(std::bind(handleNewFileFromWatcher, std::ref(uploader), std::placeholders::_1));
    

    return 0;
}
