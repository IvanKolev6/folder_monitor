#include "file_uploader.hpp"
#include <iostream>

FileUploader::FileUploader(TokenManager& tm, std::unique_ptr<UploadStrategy> strat)
    : token_manager(tm), strategy(std::move(strat)) {}


bool FileUploader::uploadFile(const std::string& file_path) {
    if (!strategy) {
        std::cerr << "No valid upload strategy initialized!" << std::endl;
        return false;
    }

    std::string token = token_manager.getAccessToken();
    std::string folder_id = std::to_string(token_manager.getHomeFolderID());
    return strategy->upload(file_path, folder_id, token);
}


int FileUploader::handleNewFile(const std::string& file_path) {
    if (uploadFile(file_path)) {
        std::cout << "Uploaded: " << file_path << std::endl;
        return 0;
    } else {
        std::cerr << "Failed to upload: " << file_path << std::endl;
        return 1;
    }
}
