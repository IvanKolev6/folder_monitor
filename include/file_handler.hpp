#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "file_uploader.hpp"

void handleNewFileFromWatcher(FileUploader& uploader, const std::string& file_path);

#endif // FILE_HANDLER_HPP
