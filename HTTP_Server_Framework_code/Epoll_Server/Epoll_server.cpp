//
// Created by fspst on 23-6-12.
//

#include "Epoll_server.h"

namespace Epoll_server {
    void Epoll_server::SIGPIPE_go_west(int go_west) {
        try {
            sigset_t SIGPIPE_go_west_signal;
            sigemptyset(&SIGPIPE_go_west_signal);
            sigaddset(&SIGPIPE_go_west_signal, go_west);
            pthread_sigmask(SIG_BLOCK, &SIGPIPE_go_west_signal, NULL);
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }

    Epoll_server::Epoll_server() {
        The_default_directory="";
        ifstream insrc;
        string s;
        insrc.open("../src/src_Content-Type");
        while (insrc >> s)
        {
            string s1, s2;
            int fg = s.find(':');
            s1 = s.substr(0, fg);
            s2 = s.substr(fg + 1, s.length() - fg - 1);
            HTTP_Content_type_dictionary[s1] = s2;
        }

        insrc.close();
    }

    Epoll_server::~Epoll_server() {

    }

} // Epoll_server