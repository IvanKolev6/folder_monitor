#include "upload_strategy.hpp"
#include "direct_upload_strategy.hpp"
#include <iostream>

std::unique_ptr<UploadStrategy> UploadStrategy::create(const std::string& type, const std::string& config_url) {
    if (type == "direct") {
        return std::make_unique<DirectUploadStrategy>(config_url);
    }
    // Add more strategies in the future
    else {
        std::cerr << "Unknown upload strategy type: " << type << std::endl;
        return nullptr;
    }
}

