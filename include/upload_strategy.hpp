#ifndef UPLOAD_STRATEGY_HPP
#define UPLOAD_STRATEGY_HPP

#include <string>
#include <memory>
#include "server_query.hpp"

class UploadStrategy {
public:
    virtual ~UploadStrategy() = default;
    virtual bool upload(const std::string& file_path, const std::string& folder_id, const std::string& token) = 0;

    static std::unique_ptr<UploadStrategy> create(const std::string& type, const std::string& config_url);

};

#endif
