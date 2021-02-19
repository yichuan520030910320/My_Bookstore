cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code
        BookStore.h
        BasicFunction.cpp
        BasicFileManager.cpp
        UserManager.cpp
        BookManager.cpp
        blockchain.cpp
        blockchain.h
        UserManager.h
        main.cpp
        )