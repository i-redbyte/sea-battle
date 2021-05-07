cmake_minimum_required(VERSION 3.17)
project(sea_battle)
find_package (Threads)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_definitions(
        -DSERVER_EXAMPLE
        #        -DCLIENT_EXAMPLE
)

add_executable(sea_battle
        client_example.cpp
        server_example.cpp
        src/tcp_client.cpp
        src/tcp_server.cpp
        src/client.cpp)

target_link_libraries (sea_battle ${CMAKE_THREAD_LIBS_INIT})
#
#add_executable(sea_battle main.cpp)