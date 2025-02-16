#include "file_handler.hpp"

void handleNewFileFromWatcher(FileUploader& uploader, const std::string& file_path) {
    uploader.handleNewFile(file_path); 
}
