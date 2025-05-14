//
// Created by fspst on 23-5-7.
//

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
class HTTP_server;
class Thread_Pool_sem
{
private:
    sem_t thread_pool_sem;

public:
    Thread_Pool_sem();
    ~Thread_Pool_sem();
    int addsem();//增加信号量
    int waitsem(timespec wait_time);//记时等待信号
    int waitsem();//不记时等待；
    int reducesem();//减少信号量
    int getsem();//获取信号量的值
};