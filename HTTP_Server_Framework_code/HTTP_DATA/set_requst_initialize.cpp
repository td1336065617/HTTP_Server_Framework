//
// Created by fspst on 23-6-13.
//
#include "HTTP_request_data.h"
#include "../xt_heard/xt_heard.h"
#include"nlohmann/json.hpp"

using namespace nlohmann;
namespace Epoll_server {
    void HTTP_request_data::set_requst_initialize() {
    }

    string HTTP_request_data::POST_Json_Data() {
        json response_json = json(http_data_value);
        return response_json.dump();
    }
}