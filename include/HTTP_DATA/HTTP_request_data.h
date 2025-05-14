//
// Created by fspst on 23-6-13.
//
#pragma once
#include "../xt_heard/xt_heard.h"

namespace Epoll_server {

    using namespace std;
    class HTTP_request_data {
    public:
        int acceptbj = 0;                              //请求的套接子的描述符
        string url = "";                               //请求的文件的本地url
        string Location="";
        string Type = "";                              //请求的文件的类型
        string Request_type = "";                      //请求类型
        string HTTP_Cookie = "";                       //Cookie
        string Request_http_type = "";                 //请求头的http类型
        unordered_map<string, string> http_value;      //请求头分割后存在这里
        unordered_map<string, string> http_data_value; //分解后的post or get数据都在里面
        unordered_map<string, string> HTTP_Cookie_value;//分解后的cooike;
        string HTTP_If_Modified_Since;                 //服务器缓存文件的最后修改时间

    void set_requst_initialize();
        string POST_Json_Data();
    };
}