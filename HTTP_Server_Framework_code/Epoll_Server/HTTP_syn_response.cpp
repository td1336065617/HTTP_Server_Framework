//
// Created by fspst on 23-10-28.
//
#include "Epoll_server.h"
namespace Epoll_server{

    int Epoll_server::HTTP_syn_response(HTTP_request_data &httpRequestData, HTTP_response_data &httpResponseData) {
        try
        {
            httpResponseData.value = true;
            httpResponseData.acceptbj = httpRequestData.acceptbj;
            httpResponseData.http_data_value = httpRequestData.http_data_value;
            httpResponseData.HTTP_Cookie = httpRequestData.HTTP_Cookie;
            httpResponseData.HTTP_Cookie_value = httpRequestData.HTTP_Cookie_value;
            httpResponseData.http_value = httpRequestData.http_value;
            httpResponseData.HTTP_Connection = "close";
            httpResponseData.HTTP_Server = "fspst-server";
            httpResponseData.host = httpRequestData.http_value["Host"];
            httpResponseData.Location=httpRequestData.Location;
            if (httpResponseData.Location!="")
            {
                httpResponseData.HTTP_Status_Code = "HTTP/1.1 301 Moved Permanently";
                return 0;
            }
            if (httpRequestData.url != "")//如果不是标准请求头 不存在申请的文件地址 则不对数据预先处理 移交给用户自行处理
            {
                int i = httpRequestData.url.rfind('.');
                string testtype = "";
                if (i != -1)
                    testtype = httpRequestData.url.substr(i, httpRequestData.url.length() - i);

                if (HTTP_Content_type_dictionary.find(testtype) != HTTP_Content_type_dictionary.end() && i != -1)
                    httpResponseData.HTTP_Content_Type += HTTP_Content_type_dictionary[testtype];
                else
                    httpResponseData.HTTP_Content_Type = HTTP_Content_type_dictionary[".*"];

                httpResponseData.Resource_path = The_default_directory + httpRequestData.url;
                struct stat wjbuf; //存放文件信息
                char timestr[1000];
                struct tm *gmtsj;
                char charurl[200] = {0};
                strcpy(charurl, httpResponseData.Resource_path.c_str());
                i = stat(charurl, &wjbuf);
                httpResponseData.HTTP_Content_Length_size = wjbuf.st_size;

                if (i == -1)
                {
                    httpResponseData.HTTP_Status_Code = "HTTP/1.1 404 Not Found";

                    if (testtype == ".html")
                    {
                        httpResponseData.Resource_path = "../src/404.html";
                        strcpy(charurl, httpResponseData.Resource_path.c_str());
                        i = stat(charurl, &wjbuf);
                        httpResponseData.HTTP_Content_Length_size = wjbuf.st_size;
                    }
                }
                else
                {
                    time_t wj_st_mtime = wjbuf.st_mtim.tv_sec, HTTP_If_Modified_Since_st_time;
                    gmtsj = gmtime(&wj_st_mtime);
                    strftime(timestr, 900, GMT_time_data_format.c_str(), gmtsj);
                    httpResponseData.HTTP_Last_Modified = timestr;
                    httpResponseData.HTTP_Content_Length = std::to_string(httpResponseData.HTTP_Content_Length_size);

                    if (httpRequestData.HTTP_If_Modified_Since != "")
                    {
                        struct tm HTTP_If_Modified_Since_tm;
                        strptime(httpRequestData.HTTP_If_Modified_Since.c_str(), GMT_time_data_format.c_str(), &HTTP_If_Modified_Since_tm);
                        HTTP_If_Modified_Since_st_time = mktime(&HTTP_If_Modified_Since_tm);

                        if (HTTP_If_Modified_Since_st_time == wj_st_mtime)
                        {
                            httpResponseData.HTTP_Status_Code = "HTTP/1.1 304 Not Modified";
                            return 0;
                        }
                        else
                        {
                            httpResponseData.HTTP_Status_Code = "HTTP/1.1 200 ok";
                        }
                    }
                    else
                    {
                        httpResponseData.HTTP_Status_Code = "HTTP/1.1 200 ok";
                    }
                }

                if (testtype == ".html")
                {
                    if (httpResponseData.HTTP_Cache_Control == "")
                        httpResponseData.HTTP_Cache_Control = "10";
                }
                else
                {
                    if (httpResponseData.HTTP_Cache_Control == "")
                        httpResponseData.HTTP_Cache_Control = "21625";
                }
            }
//以下确定是否直接返回
            cout << "HTTP_syn_response yes:" << httpRequestData.url << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return 0;
    }
}