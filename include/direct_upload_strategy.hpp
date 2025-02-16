#ifndef DIRECT_UPLOAD_STRATEGY_HPP
#define DIRECT_UPLOAD_STRATEGY_HPP

#include "upload_strategy.hpp"
#include "server_query.hpp"
#include <memory>
#include <string>

class DirectUploadStrategy : public UploadStrategy {
public:
    DirectUploadStrategy(const std::string& config_url);
    bool upload(const std::string& file_path, const std::string& folder_id, const std::string& token) override;

private:
    std::string base_uri;
    std::unique_ptr<ServerQuery> server_query;
};

#endif // DIRECT_UPLOAD_STRATEGY_HPP
