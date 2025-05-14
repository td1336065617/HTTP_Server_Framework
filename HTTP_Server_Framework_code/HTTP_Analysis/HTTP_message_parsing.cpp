//
// Created by fspst on 23-6-13.
//
#include "HTTP_Analysis.h"

namespace Epoll_server {
    HTTP_request_data HTTP_Analysis::HTTP_message_parsing(int acceptbj, std::string mess) {
        HTTP_request_data http_request_value;
        try {
            
            string http_request_str = mess;

            int i = 0;

            http_request_value.acceptbj = acceptbj;

            if (http_request_str[http_request_str.length() - 1] != '\n') {
                http_request_str += "\r\n";
            }

            while (i < (int) http_request_str.length()) {
                int end_i = http_request_str.find('\n', i);

                if (end_i == -1) {
                    cout << "请求头无回车符，请求头可能出错";
                    break;
                }
                string s;
                if (http_request_str.find('\r', i) != http_request_str.npos)
                    s = http_request_str.substr(i, end_i - i - 1);
                else
                    s = http_request_str.substr(i, end_i - i);

                if (s.find(" ") != s.npos && s.find('{') == s.npos) {
                    int heard = 0;
                    int list = s.find(" ");
                    string s1, s2;
                    s1 = s.substr(heard, list);
                    list++;
                    s2 = s.substr(list, end_i - list);

                    if (s1[s1.length() - 1] == ':') {
                        s1.erase(s1.length() - 1);
                    }

                    http_request_value.http_value[s1] = s2;
                } else if (s.find('=') != s.npos || s.find('{') != s.npos) {
                    http_request_value.http_value["DATA"] = s;
                } else if (!(s == "\r\n" || s == "\n" || s == "")) {
                    // cout << s << '\n';
                    i = end_i + 1;
                    continue;
                }

                i = end_i + 1;
            }
            cout<<1<<endl;
            if (http_request_value.http_value.find("GET") != http_request_value.http_value.end()) {
                int j = http_request_value.http_value["GET"].find(" ");
                int jq = http_request_value.http_value["GET"].find("?");
                
                if (jq != -1) {
                    http_request_value.url = http_request_value.http_value["GET"].substr(0, jq);
                    http_request_value.http_value["DATA"] = http_request_value.http_value["GET"].substr(jq + 1, j - jq-1);
                } else {
                    http_request_value.url = http_request_value.http_value["GET"].substr(0, j);
                }

                http_request_value.Request_http_type = http_request_value.http_value["GET"].substr(j + 1,http_request_value.http_value["GET"].length() -1 - j);
            } else if (http_request_value.http_value.find("POST") != http_request_value.http_value.end()) {
                int j = http_request_value.http_value["POST"].find(" ");
                http_request_value.url = http_request_value.http_value["POST"].substr(0, j);
                http_request_value.Request_http_type = http_request_value.http_value["POST"].substr(j + 1,http_request_value.http_value["POST"].length() -1 - j);
            }
            int x = http_request_value.url.rfind('.');
            int y = http_request_value.url.rfind('/');

            if (y == -1 || (http_request_value.url[http_request_value.url.length() - 1] != '/' && x < y)) {
                http_request_value.url += '/';
            }
            if (http_request_value.url[http_request_value.url.length() - 1] == '/')
            {
                http_request_value.url += "index.html";
                http_request_value.Location=http_request_value.url;
                
            }
            if (http_request_value.http_value.find("If-Modified-Since:") != http_request_value.http_value.end()) {
                http_request_value.HTTP_If_Modified_Since = http_request_value.http_value["If-Modified-Since:"];
            }

            if (http_request_value.http_value.find("DATA") != http_request_value.http_value.end()) //判断请求头内是否包含传输的数据
                Data_spliti(http_request_value.http_value["DATA"], &http_request_value);

            if (http_request_value.http_value.find("Cookie") != http_request_value.http_value.end()) {
                http_request_value.HTTP_Cookie = http_request_value.http_value["Cookie"];
                HTTP_Cookie_value_spliti(&http_request_value);
            }

        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        return http_request_value;
    }
}