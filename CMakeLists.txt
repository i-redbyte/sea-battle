cmake_minimum_required(VERSION 3.10)

project(SeaBattle VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/Board.cpp
        src/Ship.cpp
        src/AIPlayer.cpp
        src/HumanPlayer.cpp
        )

add_executable(SeaBattle ${SOURCES})
