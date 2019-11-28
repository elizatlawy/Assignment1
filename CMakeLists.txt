cmake_minimum_required(VERSION 3.10.2)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment1 src/Main.cpp src/Watchable.cpp src/User.cpp src/Action.cpp src/Session.cpp)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Weffc++ -std=c++11 -Wextra")
