#ifndef ENDPOINT_MANAGER_HPP
#define ENDPOINT_MANAGER_HPP 

#include <string>

class EndpointManager {
    public:
        static std::string getToken() { return "/token"; }
        static std::string getUserInfo() { return "/users/self"; }
        static std::string getUploadEndpoint(const std::string& folder_id) { return "/folders/" + folder_id + "/files"; }
};

#endif // ENDPOINT_MANAGER_HPP