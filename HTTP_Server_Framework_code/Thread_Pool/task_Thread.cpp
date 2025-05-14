#include "Thread_Pool_http_server.h"
void *Thread_Pool_http_server::task_Thread(void *arg)
{
    try
    {

        pthread_detach(pthread_self());
        Thread_Pool_http_server *thread_pool = (Thread_Pool_http_server *)arg;
        timespec wait_timespec;
        clock_gettime(CLOCK_REALTIME, &wait_timespec);
        wait_timespec.tv_sec += thread_pool->wait_time;

        while (true)
        {
            //cout<<pthread_self()<<std::endl;
            if (!thread_pool->task_queue.empty())
            {
                //cout<<pthread_self()<<"开始干活"<<std::endl;
                thread_pool->task_queue_task.lock();
                if (thread_pool->task_queue.empty()) //防止多条线程都被锁卡在前面，防止队列清空了还front()
                {
                    thread_pool->task_queue_task.unlock();
                    continue;
                }
                Epoll_server::task t = thread_pool->task_queue.front();
                thread_pool->task_queue.pop();
                thread_pool->task_queue_task.unlock();

                thread_pool->wait_count_mtx.lock();
                thread_pool->wait_count--;
                thread_pool->wait_count_mtx.unlock();

                thread_pool->existing_count_mtx.lock();
               // cout<<"目前有池子："<<thread_pool->existing_count<<"池子还剩下:"<< thread_pool->wait_count<<std::endl;
                thread_pool->existing_count_mtx.unlock();

                t.run();


                //cout<<"干完了 休息100ms"<<std::endl;
                //sleep(10);
                thread_pool->wait_count_mtx.lock();
                thread_pool->wait_count++;
                thread_pool->wait_count_mtx.unlock();
            }
            else
            {
                if (thread_pool->xiaohuibiaoji)
                {
                    thread_pool->existing_count_mtx.lock();
                    thread_pool->existing_count--;
                    thread_pool->existing_count_mtx.unlock();
                    pthread_exit(NULL);
                }

                int bj;
                bj=thread_pool->thread_pool_sem.waitsem(wait_timespec);
                if(bj!=-1)
                {
                    cout<<"任务来了 被唤醒了"<<"剩余任务"<<thread_pool->thread_pool_sem.getsem()<<std::endl;
                }
                thread_pool->wait_count_mtx.lock();
                thread_pool->existing_count_mtx.lock();
                cout<<"现有线程"<<thread_pool->existing_count<<std::endl;
                cout<<"没事干的"<<thread_pool->wait_count<<std::endl;
                if (bj == -1 && errno == ETIMEDOUT && thread_pool->existing_count > thread_pool->mincount)
                {
                    thread_pool->wait_count--;
                    thread_pool->existing_count--;
                    cout<<"裁员开始 还有线程:"<<thread_pool->existing_count<< std::endl;
                    thread_pool->wait_count_mtx.unlock();
                    thread_pool->existing_count_mtx.unlock();
                    pthread_exit(NULL);
                }else
                {
                    thread_pool->wait_count_mtx.unlock();
                    thread_pool->existing_count_mtx.unlock();
                }

                clock_gettime(CLOCK_REALTIME, &wait_timespec);
                wait_timespec.tv_sec += thread_pool->wait_time;
            }
        }

        pthread_exit(NULL);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
