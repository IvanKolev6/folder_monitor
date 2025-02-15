#ifndef DIRECT_UPLOAD_STRATEGY_HPP
#define DIRECT_UPLOAD_STRATEGY_HPP

#include "upload_strategy.hpp"
#include "httplib.h"
#include <memory>

class DirectUploadStrategy : public UploadStrategy {
    public:
        DirectUploadStrategy(const std::string& config_url);
        bool upload(const std::string& file_path, const std::string& folder_id, const std::string& token) override;
    
    private:
        std::unique_ptr<httplib::Client> cli;
    };

#endif