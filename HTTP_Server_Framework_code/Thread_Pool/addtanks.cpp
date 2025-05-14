#include "Thread_Pool_http_server.h"
int Thread_Pool_http_server::addtanks(void (Epoll_server::Epoll_server::*pf)(), Epoll_server::Epoll_server *server)
{
    try
    {
        Epoll_server::task task1;
        task1.set(pf, server);
        //cout<<"任务生成完成"<<std::endl;
        task_mtx.lock();
        task_queue.push(task1);
        task_mtx.unlock();
        thread_pool_sem.addsem();
        //cout<<"add后:"<<thread_pool_sem.getsem()<<std::endl;
        wait_count_mtx.lock();
        existing_count_mtx.lock();
        if (wait_count == 0&&existing_count<maxcount)
        {
            existing_count_mtx.unlock();
            wait_count_mtx.unlock();
            //cout<<"线程池空了 开始添加"<<std::endl;
            addThread_pool();
        }else{
            existing_count_mtx.unlock();
            wait_count_mtx.unlock();
        }

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
