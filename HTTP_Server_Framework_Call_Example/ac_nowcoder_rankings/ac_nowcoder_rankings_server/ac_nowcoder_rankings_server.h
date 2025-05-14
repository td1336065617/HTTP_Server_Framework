//
// Created by fsptd on 25-5-14.
//
#include "HTTP_Server_Framework/HTTP_Server_Framework.h"
#ifndef AC_NOWCODER_RANKINGS_SERVER_H
#define AC_NOWCODER_RANKINGS_SERVER_H

namespace ac_nowcoder_rankings_server {
    using namespace HTTP_Server_Framework;
class ac_nowcoder_rankings_server :public HTTP_Server_Framework {
    int Task_distribution_center( HTTP_request_data httpRequestData, HTTP_response_data &httpResponseData);//如果需要对HTTP请求的数据进行处理，继承后重写任务分配中心()
};

} // ac_nowcoder_rankings_server

#endif //AC_NOWCODER_RANKINGS_SERVER_H
