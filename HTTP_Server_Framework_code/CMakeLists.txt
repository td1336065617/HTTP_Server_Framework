cmake_minimum_required(VERSION 3.31)
project(HTTP_Server_Framework)

set(CMAKE_CXX_STANDARD 20)

add_library(HTTP_Server_Framework SHARED HTTP_Server_Framework.h
        Epoll_request/Epoll_request.cpp
        Epoll_request/Epoll_request.h
        Epoll_Server/epoll_del.cpp
        Epoll_Server/epoll_response.cpp
        Epoll_Server/Epoll_server.cpp
        Epoll_Server/Epoll_server.h
        Epoll_Server/epoll_task.cpp
        Epoll_Server/epoll_task_Bread.cpp
        Epoll_Server/HTTP_syn_response.cpp
        Epoll_Server/server.cpp
        Epoll_Server/Task_distribution_center.cpp
        HTTP_Analysis/Data_spliti.cpp
        HTTP_Analysis/HTTP_Analysis.cpp
        HTTP_Analysis/HTTP_Analysis.h
        HTTP_Analysis/HTTP_Cookie_value_spliti.cpp
        HTTP_Analysis/HTTP_message_parsing.cpp
        HTTP_Analysis/server_urlencode.cpp
        HTTP_DATA/HTTP_request_data.h
        HTTP_DATA/HTTP_response_data.cpp
        HTTP_DATA/HTTP_response_data.h
        HTTP_DATA/set_requst_initialize.cpp
        Thread_Pool/addtanks.cpp
        Thread_Pool/addThread_pool.cpp
        Thread_Pool/task_Thread.cpp
        Thread_Pool/Thread_Pool_http_server.cpp
        Thread_Pool/Thread_Pool_http_server.h
        Thread_Pool_sem/Thread_Pool_sem.cpp
        Thread_Pool_sem/Thread_Pool_sem.h
        time/time_cl.cpp
        time/time_cl.h
        Time_data/Time_data.cpp
        Time_data/Time_data.h
        xt_heard/xt_heard.h
        HTTP_Server_Framework.h
        Epoll_request/set_cookie.cpp)
target_link_libraries(HTTP_Server_Framework /lib/x86_64-linux-gnu/libcrypto++.a ${CMAKE_SOURCE_DIR}/lib/libws2_32.a -lmysqlclient -lcurl)
