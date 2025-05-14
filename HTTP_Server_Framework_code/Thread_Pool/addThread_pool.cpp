#include "Thread_Pool_http_server.h"
int Thread_Pool_http_server::addThread_pool()
{
    try
    {
        pthread_t id;
        int ret = pthread_create(&id, NULL, task_Thread, (void *)this);
        //cout<<"创建线程:"<<id<<std::endl;
        //cout<<ret<<std::endl;
        if (ret == -1)
            cout << "task_Thread创建线程失败";
        //cout<<"现有线程"<<existing_count<<std::endl;
        wait_count_mtx.lock();
        //cout<<"现有线程"<<existing_count<<std::endl;
        existing_count_mtx.lock();
        existing_count++;
        wait_count++;
        //cout<<"没事干的"<<wait_count<<std::endl;
        wait_count_mtx.unlock();
        existing_count_mtx.unlock();
        cout<<"现有线程"<<existing_count<<std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
