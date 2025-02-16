#include "direct_upload_strategy.hpp"
#include "server_query.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

DirectUploadStrategy::DirectUploadStrategy(const std::string& config_url)
    : base_uri(config_url), server_query(std::make_unique<ServerQuery>(config_url)) {}

bool DirectUploadStrategy::upload(const std::string& file_path, const std::string& folder_id, const std::string& token) {
    try {
        // Prepare the upload URL
        std::string endpoint = "/folders/" + folder_id + "/files";

        // Perform the upload
        bool response = server_query->uploadFile(endpoint, file_path, token);

        // Log the result
        std::cout << "File upload: " << (response ? "Successfully" : "Failed") << std::endl;
        return response;

    } catch (const std::exception& e) {
        std::cerr << "Standard Exception: " << e.what() << std::endl;
        return false;
    }
}
