//
// Created by fspst on 23-5-7.
//
#include "Thread_Pool_sem.h"

Thread_Pool_sem::Thread_Pool_sem()
{
    try
    {
        sem_init(&thread_pool_sem, 0, 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Thread_Pool_sem::~Thread_Pool_sem()
{
    try
    {
        sem_destroy(&thread_pool_sem);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
int Thread_Pool_sem::addsem()
{
    return sem_post(&thread_pool_sem);
};
int Thread_Pool_sem::waitsem(timespec wait_time)
{
    return sem_timedwait(&thread_pool_sem, &wait_time);
};
int Thread_Pool_sem::waitsem()
{
    return sem_wait(&thread_pool_sem);
};
int Thread_Pool_sem::reducesem()
{
    return sem_wait(&thread_pool_sem);
}
int  Thread_Pool_sem::getsem()
{
    int i;
    sem_getvalue(&thread_pool_sem, &i);
    return i;
};
