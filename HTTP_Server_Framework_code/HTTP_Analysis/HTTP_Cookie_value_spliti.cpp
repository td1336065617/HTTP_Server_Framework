//
// Created by fspst on 23-6-13.
//
#include "HTTP_Analysis.h"

namespace Epoll_server {
    void HTTP_Analysis::HTTP_Cookie_value_spliti(Epoll_server::HTTP_request_data *http_request_value) {
        string cookie_str = http_request_value->HTTP_Cookie;
        try {
            int i = 0, end_i = 0, fg = 0;
            int len = cookie_str.length();

            while (i < len) {
                fg = cookie_str.find("=", i);

                if (fg == -1) {
                    cout << "cookie格式错误";
                    break;
                }
                end_i = cookie_str.find(";", fg);

                if (end_i == -1 && fg != -1) {
                    end_i = len; //没有-1是因为下面本来就会排除&
                }

                string s1, s2;
                s1 = cookie_str.substr(fg + 1, end_i - 1 - fg);
                s2 = cookie_str.substr(i, fg - i);
                server_urlencode(&s2);
                server_urlencode(&s1);
                http_request_value->HTTP_Cookie_value[s2] = s1;
                i = end_i + 1;
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}