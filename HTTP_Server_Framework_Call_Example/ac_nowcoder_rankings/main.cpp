#include <iostream>
#include "ac_nowcoder_rankings_server/ac_nowcoder_rankings_server.h"
int main() {
    HTTP_Server_Framework::HTTP_Server_Framework http_server_framework;
    http_server_framework.set_Thread_Poll(100,5,10);
    http_server_framework.set_server("0.0.0.0",9999);
    //
    http_server_framework.start_server();

}