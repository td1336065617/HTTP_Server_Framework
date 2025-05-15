//
// Created by fspst on 23-6-12.
//
#pragma once
#include "../xt_heard/xt_heard.h"
#include "../HTTP_Analysis/HTTP_Analysis.h"
#include "../Thread_Pool/Thread_Pool_http_server.h"
#include "../Epoll_request/Epoll_request.h"
#include "../HTTP_DATA/HTTP_response_data.h"

namespace Epoll_server {
    using namespace std;
    class Epoll_server {
    public:
        Epoll_server();

        virtual ~Epoll_server();
        void set_Thread_Poll(int maxcount, int mincount, int waittime){thread_poll.set_Thread_Pool_http_server(maxcount,mincount,waittime);};
        void set_server(string ip, int post);//请先设置服务器参数  函数体在server.cpp
        void start_server(); // 函数体在server.cpp
        void setBootServerUrl(const string &bootServerUrl);
    protected:
        unordered_map<string, string> HTTP_Content_type_dictionary;         //这个哈希表记录了文件与其对于的响应头Content_type
        string The_default_directory;                                      // web目录
        string GMT_time_data_format = "%a, %d %b %Y %H:%M:%S %Z";          // GMT时间转换的模板
        int HTTP_syn_response(HTTP_request_data &httpRequestData,HTTP_response_data &httpResponseData);
        void HTTP_data_response(int clientbj,HTTP_response_data http_response1);
        void HTTP_file_response(int clientbj,HTTP_response_data http_response1);
        int serverbj;
        int bindbj;
        int listenbj;
        int epollbj;
        string BOOT_server_url;
        epoll_event listen_serverbj;
        epoll_event es[2048];
        mutex recv_number_mtx,recv_fd_mtx,recv_fd_map_mtx;
        queue<int> recv_fd;
        map<int,int>recv_number;
        void epoll_del(int fd);
        map<int,int>recv_fd_map;
        Thread_Pool_http_server thread_poll;
        Epoll_request epollRequest;
        void SIGPIPE_go_west(int go_west);//处理相关异常 函数体在server.cpp
        int epoll_recv(int fd, string &rq);//读取传输的数据 函数体在server.cpp
        int epoll_accept();  //接入入链接请求 函数体在server.cpp
        void epoll_task();//接入请求后数据读取处理返回等执行任务的中控函数
        void epoll_task_Bread();
        //返回机制需要更改
        int epoll_response(int clientbj,HTTP_response_data httpResponseData);//根据请求数据进行响应。实际上是对go-cqhttp http发出请求
        virtual int Task_distribution_center(HTTP_request_data httpRequestData, HTTP_response_data &httpResponseData)=0;//如果需要对HTTP请求的数据进行处理，继承后重写任务分配中心
    };

} // Epoll_server