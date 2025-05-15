//
// Created by fspst on 23-6-16.
//

#pragma once
#include "string"
namespace Epoll_server {
    class Epoll_request {
    public:
        std::string post_url(std::string url,std::string post_str) ;
        std::string get_url(std::string url);
        int set_cookie(std::string cookie);
    private:
        std::string cookie;
        static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp);
    };
}