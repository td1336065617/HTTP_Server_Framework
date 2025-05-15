//
// Created by fsptd on 25-5-15.
//
#pragma once
#include "Epoll_request.h"
namespace Epoll_server {
    int Epoll_request::set_cookie(std::string cookie) {
        this->cookie = cookie;
        return 1;
    }

}