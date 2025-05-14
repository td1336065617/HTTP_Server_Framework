//
// Created by fspst on 23-6-13.
//
#include "HTTP_Analysis.h"
#include"nlohmann/json.hpp"

using namespace nlohmann;
namespace Epoll_server {
    void HTTP_Analysis::Data_spliti(std::string datastr, Epoll_server::HTTP_request_data *http_request_value) {
        try {
            if (http_request_value->http_value["Content-Type"] == "application/json") {
                //cout<<"JSON\n";
                json j1;
                j1 = json::parse(datastr);;

                for (auto &x: j1.items()) {
                    //std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';

                    if (x.value().is_string()) {
                        http_request_value->http_data_value[x.key()] = x.value();
                    } else
                        http_request_value->http_data_value[x.key()] = x.value().dump();
                }

                // cout<<"JSON\n";
                return;
            }

            int i = 0, end_i = 0, fg = 0;
            int len = datastr.length();

            while (i < len) {
                fg = datastr.find("=", i);

                if (fg == -1) {
                    cout << "get或post格式错误";
                    break;
                }

                end_i = datastr.find("&", fg);

                if (end_i == -1 && fg != -1) {
                    end_i = len; //没有-1是因为下面本来就会排除&
                }

                string s1, s2;
                s1 = datastr.substr(fg + 1, end_i - 1 - fg);
                s2 = datastr.substr(i, fg - i);
                server_urlencode(&s2);
                server_urlencode(&s1);
                http_request_value->http_data_value[s2] = s1;
                i = end_i + 1;
            }

            cout << "data处理结束";
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
}