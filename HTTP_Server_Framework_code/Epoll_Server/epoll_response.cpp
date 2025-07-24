//
// Created by fspst on 23-6-13.
//
#include "Epoll_server.h"

namespace Epoll_server {
    int Epoll_server::epoll_response(int clientbj, HTTP_response_data httpResponseData) {
        try {
            //cout << "HTTP_response开始\r\n";
            sigset(SIGPIPE, SIG_IGN); // 忽略SIGPIPE信号，防止程序因连接断开而崩溃
            if (httpResponseData.file_or_data)
                httpResponseData.HTTP_Content_Length = to_string(httpResponseData.http_response_data_value.length());
                // 如果是数据响应，设置内容长度为数据长度
            else
                httpResponseData.HTTP_Content_Length = to_string(httpResponseData.HTTP_Content_Length_size);
            // 如果是文件响应，使用预设的内容长度
            httpResponseData.set_http_response_value(); // 构造HTTP响应头
            httpResponseData.http_response_value += "\r\n"; // 添加响应头结束符
            int s = 0, send_out_size = 0, buf_size = httpResponseData.http_response_value.length();
            while (send_out_size < buf_size) {
                s = send(clientbj, httpResponseData.http_response_value.c_str() + send_out_size, buf_size - send_out_size, MSG_NOSIGNAL); // 发送HTTP响应头

                if (s == -1) {
                    if (errno == EINTR) //如果只是信号中断了不用管
                    {
                        cout << "信号中断\r\n";
                        break;
                    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        //不用管 就是一次性发不完
                    } else {
                        cout << "sendfile error" << strerror(errno) << "\r\n";
                        break; //不知道什么错了 输出原因然后跑路
                    }
                }

                send_out_size += s;
            }
            if (s == -1) {
                cout << "send error\r\n";
                return 0;
            }
            if (httpResponseData.file_or_data) {
                HTTP_data_response(clientbj, httpResponseData); // 处理数据响应
            } else {
                HTTP_file_response(clientbj, httpResponseData); // 处理文件响应
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        return 0;
    }

    void Epoll_server::HTTP_data_response(int clientbj, HTTP_response_data http_response1) {
        try {
            sigset(SIGPIPE, SIG_IGN); // 忽略SIGPIPE信号
            int s = 0, send_out_size = 0, buf_size = http_response1.http_response_data_value.length();
            while (send_out_size < buf_size) {
                s = send(http_response1.acceptbj, http_response1.http_response_data_value.c_str() + send_out_size, buf_size - send_out_size,
                         MSG_NOSIGNAL); // 发送HTTP响应数据

                if (s == -1) {
                    if (errno == EINTR) //如果只是信号中断了不用管
                    {
                        cout << "信号中断\r\n";
                        continue; // 信号中断应继续尝试发送
                    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // 非阻塞模式下发送未完成，应继续尝试发送
                        continue;
                    } else {
                        cout << "send error: " << strerror(errno) << "\r\n";
                        break; // 其他错误则退出循环
                    }
                }

                send_out_size += s;
            }
            if (s == -1) {
                cout << "send error\r\n";
                close(http_response1.acceptbj);
                return;
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }

    void Epoll_server::HTTP_file_response(int clientbj, HTTP_response_data http_response1) {
        try {
            sigset(SIGPIPE, SIG_IGN); // 忽略SIGPIPE信号
            char charurl[200] = {0};
            strcpy(charurl, http_response1.Resource_path.c_str()); // 复制文件路径
            int f = open(charurl, O_RDONLY); // 打开文件
            // cout << f << "\r\n";
            if (f == -1) {
                cout << "open error\r\n";
                close(http_response1.acceptbj);
                close(f);
                return;
            }

            //cout << s << "\r\n";
            //cout << "发送的文件的大小:" << http_response1.HTTP_Content_Length_size * 2 << std::endl;
            //cout << "response:" << http_response1.acceptbj << std::endl;
            off_t fp_out = 0;

            while (fp_out < http_response1.HTTP_Content_Length_size) {
                int sendfilebj = sendfile(clientbj, f, &fp_out, http_response1.HTTP_Content_Length_size - fp_out);
                // 使用sendfile发送文件，每次发送剩余的字节数

                // cout << "sendfile\r\n";
                if (sendfilebj == -1) {
                    if (errno == EINTR) //如果只是信号中断了不用管
                    {
                        cout << "信号中断\r\n";
                        continue; // 信号中断应继续尝试发送
                    } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // 非阻塞模式下发送未完成，应继续尝试发送
                        continue;
                    } else {
                        cout << "sendfile error" << strerror(errno) << "\r\n";
                        break; // 其他错误则退出循环
                    }
                } else if (sendfilebj == 0) {
                    // sendfile返回0表示没有更多数据可发送，正常结束
                    break;
                }
                // 更新已发送的字节数
                fp_out += sendfilebj;
            }
            int closebj;
            closebj = close(f); // 关闭文件描述符

            if (closebj == -1)
                cout << "close关闭f失败" << "\r\n";
            // Broken pipe
            // cout << "HTTP_response_taskThread\r\n";
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}
