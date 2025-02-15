#ifndef FILE_UPLOADER_HPP
#define FILE_UPLOADER_HPP

#include "upload_strategy.hpp"
#include "token_manager.hpp"

class FileUploader {
public:
    FileUploader(TokenManager& tm, std::unique_ptr<UploadStrategy> strat);

    bool uploadFile(const std::string& file_path);
    int handleNewFile(const std::string& file_path);

private:
    TokenManager& token_manager;
    std::unique_ptr<UploadStrategy> strategy; 
};


#endif
