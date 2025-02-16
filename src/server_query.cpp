#include "server_query.hpp"
#include <iostream>

ServerQuery::ServerQuery(const std::string& base_url) : base_url(base_url), curl(curl_easy_init()) {
    if (!curl) {
        std::cerr << "Error initializing curl." << std::endl;
    }
}

ServerQuery::~ServerQuery() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t ServerQuery::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

std::string ServerQuery::get(const std::string& endpoint, const std::string& token) {
    return request(endpoint, "GET", "", token);
}

std::string ServerQuery::post(const std::string& endpoint, const std::string& data, const std::string& token) {
    return request(endpoint, "POST", data, token);
}

std::string ServerQuery::request(const std::string& endpoint, const std::string& method, const std::string& data, const std::string& token) {
    if (!curl) {
        std::cerr << "Curl initialization failed!" << std::endl;
        return "";
    }

    std::string url = base_url + endpoint;
    std::string response_string;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    
    if (method == "POST" || method == "PUT") {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    struct curl_slist* headers = NULL;
    if (!token.empty()) {
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Request failed! Curl Error: " << curl_easy_strerror(res) << std::endl;
    }

    curl_slist_free_all(headers);
    return response_string;
}


bool ServerQuery::uploadFile(const std::string& endpoint, const std::string& file_path, const std::string& token) {
    if (!curl) {
        std::cerr << "Curl initialization failed!" << std::endl;
        return false;
    }

    std::cout << "Uploading file: " << file_path << std::endl;
    std::cout << "Endpoint: " << endpoint << std::endl;
    std::cout << "Token : " << token << std::endl;

    std::string url = base_url + endpoint;
    curl_mime *mime;
    curl_mimepart *field;

    // Initialize mime data for multipart form
    mime = curl_mime_init(curl);
    if (!mime) {
        std::cerr << "Error initializing mime." << std::endl;
        return false;
    }

    // Add the file part to the mime data
    field = curl_mime_addpart(mime);
    if (!field) {
        std::cerr << "Error adding mime part." << std::endl;
        curl_mime_free(mime);
        return false;
    }
    
    curl_mime_filedata(field, file_path.c_str());
    curl_mime_type(field, "application/octet-stream");  // Can change depending on the file type
    curl_mime_name(field, "file");  // This is the field name that the server expects

    // Add Authorization header if token is provided
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: multipart/form-data");

    if (!token.empty()) {
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
    }

    // Set curl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);  // Set MIMEPOST for multipart form-data
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Perform the file upload request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "File upload failed! Curl Error: " << curl_easy_strerror(res) << std::endl;
        curl_slist_free_all(headers);
        curl_mime_free(mime);
        return false;
    }

    // Check server response for authorization issues or other errors
    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200) {
        std::cerr << "Server returned error. Response Code: " << response_code << std::endl;
        curl_slist_free_all(headers);
        curl_mime_free(mime);
        return false;
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_mime_free(mime);
    std::cout << "File uploaded successfully!" << std::endl;
    return true;
}
