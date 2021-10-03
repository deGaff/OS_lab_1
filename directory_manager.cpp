//
// Created by d3Gaff on 02.10.2021.
//
#include <iostream>
#include "directory_manager.h"

bool get_path(TCHAR* path) {
    std::cout << "Enter path" << std::endl;
    std::cin.getline(path, BUFF);
    if(path[0] == 0) {
        std::cout << "Empty path. Aborting" << std::endl;
        return false;
    }
    return true;
}

void create_dir() {
    TCHAR path[BUFF];
    if(!get_path(path)) return;
    if(CreateDirectory(path, nullptr))
        std::cout << "Directory " << path << " created successfully" << std::endl;
    else
        std::cout << "Error: " << GetLastError() << std::endl;
}

void delete_dir() {
    TCHAR path[BUFF];
    if(!get_path(path)) return;
    if(RemoveDirectory(path))
        std::cout << "Directory " << path << " deleted successfully" << std::endl;
    else
        std::cout << "Error: " << GetLastError() << std::endl;
}