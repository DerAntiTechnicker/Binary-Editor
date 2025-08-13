cmake_minimum_required(VERSION 3.31)
project(Binary_Editor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Binary_Editor
        datei.cpp
        datei.h
        main.cpp
)
