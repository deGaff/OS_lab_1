cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp safe_input.cpp safe_input.h menu.cpp menu.h drive_manager.cpp drive_manager.h directory_manager.cpp directory_manager.h file_manager.cpp file_manager.h attribute_manager.cpp attribute_manager.h)
