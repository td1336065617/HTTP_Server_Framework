//
// Created by fspst on 23-6-13.
//
#include "Epoll_server.h"

namespace Epoll_server {
    void Epoll_server::epoll_del(int fd) {
        recv_fd_map_mtx.lock();
        recv_fd_map.erase(fd);
        recv_fd_map_mtx.unlock();
        recv_number_mtx.lock();
        recv_number[fd]=0;
        recv_number_mtx.unlock();
        epoll_event client_bj_event;
        client_bj_event.data.fd = fd;
        client_bj_event.events = (EPOLLIN | EPOLLET);
        if (-1 == epoll_ctl(epollbj, EPOLL_CTL_DEL, fd, &client_bj_event)) {
            cout << "epoll_ctl error\r\n";
        }
        close(fd);
    }
}