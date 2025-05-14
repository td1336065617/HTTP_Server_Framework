//
// Created by fspst on 23-6-13.
//
#include "Epoll_server.h"
namespace Epoll_server {
    void  Epoll_server::epoll_task() {

        //首先数据读取
        int fd;
        recv_fd_mtx.lock();
        if (recv_fd.empty()) {
            recv_fd_mtx.unlock();
            return ;
        }
        fd = recv_fd.front();
        recv_fd.pop();
        recv_fd_mtx.unlock();
        string mess;
        std::cout<<"测试:"<<fd<<endl;
        int Overtime=0;
        while (1)
        {
            int recvbj = epoll_recv(fd,mess);
            if (recvbj == -1)
            {
                break;
            }
            if (recvbj==1)
            {
                Overtime=0;
                recv_number_mtx.lock();
                recv_number[fd]--;
                if(recv_number[fd]==0&&(mess.find("POST")!=mess.npos&&mess[mess.length()-1]=='}')||(mess.find("GET")!=mess.npos)&&mess.npos&&mess[mess.length()-1]=='\n') {
                    recv_number_mtx.unlock();
                    break;
                }
                recv_number_mtx.unlock();
            }
            if (recvbj == -2)
            {
                Overtime++;
                //cout<<Overtime<<endl;
                if(Overtime>10)
                {
                    break;
                }
                usleep(20000);//有数据但是还没写入缓冲区，睡眠20毫秒等一下看看能不能读到 如果连续200ms以上没读到视为丢包
            }
        }
        //cout<<mess<<endl;
        std::cout<<mess.size()<<endl;
        HTTP_Analysis httpAnalysis;
        HTTP_request_data httpRequestData = httpAnalysis.HTTP_message_parsing(fd, mess);
        //数据返回
       // cout<<httpRequestData.http_value["Host"]<<endl;
        HTTP_response_data httpResponseData;
        HTTP_syn_response(httpRequestData,httpResponseData);
        //cout<<httpResponseData<<endl;
        Task_distribution_center(httpRequestData,httpResponseData);//任务处理。
        
        string re_mess;
        //处理完成 返回运行结果。
        epoll_response(fd,httpResponseData);
        //任务完成 套接字关闭
        epoll_del(fd);
      /*  if(httpResponseData.code)
            re_mess=epollRequest.post_url(BOOT_server_url,httpResponseData.Endpoints,httpResponseData.POST_Json_Data());
        */
      cout<<re_mess;
    }
}