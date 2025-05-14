//
// Created by fspst on 23-6-13.
//
#include "HTTP_Analysis.h"

namespace Epoll_server {
    void HTTP_Analysis::server_urlencode(std::string *str_value) {
        try {
            for (int i = 0; i < (int) urlencode_str.size(); i++) {
                for (int bj = str_value->find(urlencode_str[i].s1);
                    bj != -1; bj = str_value->find(urlencode_str[i].s1)) {
                    if (bj != -1) {
                        str_value->replace(bj, urlencode_str[i].s1.length(), urlencode_str[i].s2);
                        bj++;
                    }
                }
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}