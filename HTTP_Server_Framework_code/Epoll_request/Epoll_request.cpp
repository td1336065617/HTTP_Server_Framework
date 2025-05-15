//
// Created by fspst on 23-6-16.
//
#include <curl/curl.h>
#include <string>
#include "Epoll_request.h"
namespace Epoll_server {

    size_t Epoll_request::WriteCallback(char *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string *) userp)->append((char *) contents, size * nmemb);
        return size * nmemb;
    }

    std::string Epoll_request::get_url(std::string url,std::string cookie) {

        std::string mess;
        CURL *curl;
        CURLcode res;
        FILE *fptr;
        curl = curl_easy_init();
        std::string re_url = url;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
            curl_easy_setopt(curl, CURLOPT_URL, re_url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0");
            headers = curl_slist_append(headers, "Accept: */*");
            headers = curl_slist_append(headers, "Host: ac.nowcoder.com");
            headers = curl_slist_append(headers, "Connection: keep-alive");
            headers = curl_slist_append(headers, ("cookie: "+cookie).c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            //curl_easy_perform(curl);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mess);
            curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
        return mess;
    }

    std::string Epoll_request::post_url(std::string url, std::string post_str,std::string cookie) {
        std::string mess;
        CURL *curl;
        CURLcode res;
        FILE *fptr;
        curl = curl_easy_init();
        std::string re_url = url;
        //cout<<post_str<<endl;
        if (curl) {

            curl_easy_setopt(curl, CURLOPT_HEADER, 0);
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_URL, re_url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_str.c_str());
            struct curl_slist *headers = NULL;
            std::string Content_Length = "Content-Length: " + std::to_string(post_str.length());
            std::string Content_Type = "Content-Type: application/json";
            headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0");
            headers = curl_slist_append(headers, "Accept: */*");
            headers = curl_slist_append(headers, ("Host: "+url).c_str());
            headers = curl_slist_append(headers, "Connection: keep-alive");
            headers = curl_slist_append(headers, ("cookie: "+cookie).c_str());
            headers = curl_slist_append(headers, Content_Length.c_str());
            headers = curl_slist_append(headers, Content_Type.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            //curl_easy_perform(curl);
            //获取数据
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mess);
            curl_easy_perform(curl);
        }

        //cout<<mess<<endl;
        curl_easy_cleanup(curl);
        return mess;
    }
}