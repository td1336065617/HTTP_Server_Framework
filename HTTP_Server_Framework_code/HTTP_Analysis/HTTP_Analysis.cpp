//
// Created by fspst on 23-6-13.
//

#include "HTTP_Analysis.h"

namespace Epoll_server {
    HTTP_Analysis::HTTP_Analysis() {
        ifstream insrc;
        insrc.open("../src/urlencode",ios_base::binary);
        string s1, s2;

        while ((getline(insrc, s1)) && (getline(insrc, s2))) {
            urlencode urlencode1;
            urlencode1.s1 = s1;
            urlencode1.s2 = s2;
            urlencode_str.push_back(urlencode1);
        }

        insrc.close();
    }

    HTTP_Analysis::~HTTP_Analysis() {

    }
} // Epoll_server