#include "Thread_Pool_http_server.h"
void Thread_Pool_http_server::set_Thread_Pool_http_server(int maxcount, int mincount, int waittime)
{
    try
    {
        this->maxcount = maxcount;
        this->mincount = mincount;
        this->wait_time = waittime;

        for (int i = 0; i < mincount; i++)
        {
            addThread_pool();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
Thread_Pool_http_server::~Thread_Pool_http_server()
{
}
