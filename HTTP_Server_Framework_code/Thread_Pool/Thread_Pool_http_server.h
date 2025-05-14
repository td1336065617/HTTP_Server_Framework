#pragma once
#include <stdio.h>
#include <fstream>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <map>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <mutex>
#include <condition_variable>
#include <sys/epoll.h>
#include <signal.h>
#include <semaphore.h>
#include "../Thread_Pool_sem/Thread_Pool_sem.h"
using std::mutex;
using std::condition_variable;
using std::queue;
using std::cout;
namespace Epoll_server{
    class Epoll_server;
    class task
    {
    private:
        void (Epoll_server::*pf)()=NULL;
        Epoll_server *http_server=NULL;
    public:
        task(){};
        ~task(){};
        void run()
        {
            ((*http_server).*pf)();
        }
        void set(void (Epoll_server::*qf)(),Epoll_server *httpserver)
        {
            pf = qf;
            http_server=httpserver;
        }
    };
}
class Thread_Pool_http_server
{
private:
    int xiaohuibiaoji=false;
    int maxcount=0;                        //最大线程数（最多能征兵多少）
    int mincount=0;                        //最小维持线程数（常备军）
    int existing_count=0;                  //现有工作线程
    int wait_count=0;                      //等待线程数
    int wait_time=0;                       //等待时间
    int addThread_pool();                //增加线程
    Thread_Pool_sem thread_pool_sem;     //信号量
    static void *task_Thread(void *arg); //执行任务
    mutex task_mtx, existing_count_mtx, wait_count_mtx, task_conn_mtx, task_queue_task;
    condition_variable task_conn;
    queue<Epoll_server::task> task_queue;
public:
    int addtanks(void (Epoll_server::Epoll_server::*pf)(), Epoll_server::Epoll_server *server); //添加任务
    void setxiaohui(int xiaohuibiaoji){this->xiaohuibiaoji=xiaohuibiaoji;}
    int get_existing_count(){return existing_count;}
    void thread_pool_sem_close(){for(int i=0;i<existing_count;i++)thread_pool_sem.addsem();}
    Thread_Pool_http_server(){};
    void set_Thread_Pool_http_server(int maxcount, int mincount, int waittime);
    ~Thread_Pool_http_server();
};