cmake_minimum_required(VERSION 3.31)
project(ac_nowcoder_rankings)

set(CMAKE_CXX_STANDARD 20)

add_executable(ac_nowcoder_rankings main.cpp
        ac_nowcoder_rankings_server/ac_nowcoder_rankings_server.cpp
        ac_nowcoder_rankings_server/ac_nowcoder_rankings_server.h
        ac_nowcoder_rankings_crawler/ac_nowcoder_rankings_crawler.cpp
        ac_nowcoder_rankings_crawler/ac_nowcoder_rankings_crawler.h)
target_include_directories(ac_nowcoder_rankings PRIVATE include)
target_link_directories(ac_nowcoder_rankings PRIVATE lib)
target_link_libraries(ac_nowcoder_rankings PRIVATE libHTTP_Server_Framework.so)