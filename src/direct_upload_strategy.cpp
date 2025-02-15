#include "direct_upload_strategy.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

DirectUploadStrategy::DirectUploadStrategy(const std::string& config_url) {
    cli = std::make_unique<httplib::Client>(config_url.c_str());
}

bool DirectUploadStrategy::upload(const std::string& file_path, const std::string& folder_id, const std::string& token) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file: " << file_path << std::endl;
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string file_content = buffer.str();

    httplib::Headers headers = {
        {"Authorization", "Bearer " + token},
        {"Content-Type", "application/octet-stream"}
    };

    auto res = cli->Post(("/api/v1/folders/" + folder_id + "/files").c_str(), headers, file_content, "application/octet-stream");

    if (!res || res->status != 200) {
        std::cerr << "Upload failed! HTTP Status: " << (res ? std::to_string(res->status) : "No response") << std::endl;
        return false;
    }

    std::cout << "File uploaded successfully.\n";
    return true;
}
