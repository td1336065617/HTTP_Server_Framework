//
// Created by fspst on 23-6-12.
//
#include "Epoll_server.h"
namespace Epoll_server {
    void Epoll_server::set_server(std::string ip, int post) {
        SIGPIPE_go_west(SIGPIPE);
        sockaddr_in servervalue;
        bzero(&servervalue, sizeof(servervalue));
        servervalue.sin_family = AF_INET;
        servervalue.sin_port = htons(post); //创建服务端口
        if (ip == "")
            servervalue.sin_addr.s_addr = INADDR_ANY; //没有指定ip就默认ip
        else
            servervalue.sin_addr.s_addr = inet_addr(ip.c_str()); //默认本机ip

        serverbj = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
        cout << "server创建成功" << serverbj << "\r\n";

        if (serverbj == -1)
            cout << "server error\r\n";

        int flags = fcntl(serverbj, F_GETFL, 0);
        fcntl(serverbj, F_SETFL, flags | O_NONBLOCK);
        bindbj = bind(serverbj, (struct sockaddr *) &servervalue, sizeof(servervalue)); //对套接字进行地址和端口的绑定
        cout << "bind绑定成功" << bindbj << "\r\n";
        if (bindbj == -1)
            cout << "bind error\r\n";
        listenbj = listen(serverbj, 1e6); //对端口进行监听并接受连接 参数2规定最大连接数
        cout << "listen开始监听端口:" << listenbj << "\r\n";
       /* int buffsize = 100*1024;
        setsockopt(serverbj, SOL_SOCKET, SO_RCVBUF, &buffsize, sizeof(char));//扩张缓冲区，一次post一般传输20MB
       */
        if (listenbj == -1)
            cout << "listen error\r\n";
    }

    void Epoll_server::start_server() {
        epollbj = epoll_create(1);
        if (epollbj == -1) {
            cout << "epoll_create error.\r\n";
        }
        epoll_event listen_serverbj;
        listen_serverbj.data.fd = serverbj;
        listen_serverbj.events = (EPOLLIN | EPOLLET);
        int epoll_ctl_bj = epoll_ctl(epollbj, EPOLL_CTL_ADD, serverbj, &listen_serverbj);
        if (-1 == epoll_ctl_bj) {
            std::cout << "epoll_create error." << std::endl;
        }
        while (1) {
            int listen_nume = epoll_wait(epollbj, es, 2048, 5000);
            if (listen_nume < 0) {
                if (errno == EINTR) //只是信号中断了不用管
                {
                    continue;
                }
                break;;
            } else if (listen_nume == 0) {
                continue;
            }
            for (int i = 0; i < listen_nume; i++) {
                if (es[i].data.fd == serverbj) {
                    int acceptbj = 0;

                    while (acceptbj != -1) {
                        acceptbj = epoll_accept();
                        if (acceptbj != -1) {
                            // cout << "有链接接入" << std::endl;
                            epoll_event client_bj_event;
                            client_bj_event.data.fd = acceptbj;
                            client_bj_event.events = (EPOLLIN | EPOLLET);
                            if (-1 == epoll_ctl(epollbj, EPOLL_CTL_ADD, acceptbj, &client_bj_event)) {
                                cout << "epoll_ctl error\r\n";
                            }
                        }
                    }
                } else if (es[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                } else if (es[i].events & EPOLLIN) {
                    cout << "数据读入信号发生 添加任务到线程池"<<es[i].data.fd << endl;
                    recv_number_mtx.lock();
                    recv_number[es[i].data.fd]++;
                    recv_number_mtx.unlock();
                    
                    recv_fd_map_mtx.lock();
                    if(recv_fd_map.find(es[i].data.fd)==recv_fd_map.end()) {
                        recv_fd_mtx.lock();
                        recv_fd.push(es[i].data.fd);
                        recv_fd_mtx.unlock();
                        recv_fd_map[es[i].data.fd]++;
                        thread_poll.addtanks(&Epoll_server::epoll_task, this);;
                    }
                    recv_fd_map_mtx.unlock();

                }
            }
        }
    }

    int Epoll_server::epoll_recv(int fd, string &rq) {
        try {
            char request[100*1024+1] = {0};
            int bj = recv(fd, request, sizeof(char)*100*1024, 0);
            if (bj == -1 && errno != EAGAIN || bj == 0) {
                return -1;
            }
            string str = request;
            rq += str;
            if(request[0]=='\0') return -2;
            //cout<<"epoll_recv:"<<request<<std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }

        return 1;
    }

    int Epoll_server::epoll_accept() {
        int acceptbj = 0;

        try {
            sockaddr_in connectsockaddr;
            socklen_t connectsocklen_t = sizeof(connectsockaddr);
            acceptbj = accept(serverbj, (struct sockaddr *) &connectsockaddr, &connectsocklen_t);

            /*int buffsize = 20*1024*1024;
            setsockopt(serverbj, SOL_SOCKET, SO_RCVBUF, &buffsize, sizeof(int));//扩张缓冲区*/
            if (acceptbj == -1) {
                //cout << "accept error\r\n";
                return -1;
            }

            int flags = fcntl(acceptbj, F_GETFL, 0);
            fcntl(acceptbj, F_SETFL, flags | O_NONBLOCK);
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }

        return acceptbj;
    }

    void Epoll_server::setBootServerUrl(const string &bootServerUrl) {
        BOOT_server_url = bootServerUrl;
    }
};