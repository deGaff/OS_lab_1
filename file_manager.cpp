//
// Created by d3Gaff on 02.10.2021.
//


#include "file_manager.h"
#include "menu.h"

bool get_name(TCHAR* name) {
    std::cout << "Enter name" << std::endl;
    std::cin.getline(name, BUFF);
    if(name[0] == 0) {
        std::cout << "Empty name. Aborting" << std::endl;
        return false;
    }
    return true;
}

void create_file() {
    TCHAR name[BUFF];
    if(!get_name(name)) return;
    if(CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ
    | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL, NULL)!=INVALID_HANDLE_VALUE)
        std::cout << "File " << name << " was created successfully" << std::endl;
    else
        std::cout << "Error: " << GetLastError() << std::endl;
}

void copy_file() {
    TCHAR from[BUFF],
            to[BUFF];
    std::cout << "Copy from:" << std::endl;
    bool input = get_name(from);
    if(input) {
        std::cout << "Copy to:" << std::endl;
        input = get_name(to);
    }
    if(input) {
        if(!CopyFile(from, to, true)) {
            DWORD err = GetLastError();
            if(err == ERROR_FILE_EXISTS || err == ERROR_ALREADY_EXISTS) {
                char ch;
                do {
                    std::cout << "File already exists, rewrite? -- [Y]es|[N]o" << std::endl;
                    if(!(safestream >> ch)|| (ch != 'Y' && ch != 'N')) {
                        std::cout << "Invalid input: ";
                        if(!safestream) std::cout << safestream.get_state();
                        else std::cout << "put in either \'Y\' or \'N\'";
                        std::cout << std::endl;
                        pause();
                    }
                }while(!safestream || (ch != 'Y' && ch != 'N'));
                if(ch == 'N') {
                    std::cout << "No file was copied. Abort" << std::endl;
                    return;
                }
                if(!CopyFile(from, to, false)) {
                    std::cout << "Error: " << GetLastError() << std::endl;
                    return;
                }
            }
            else {
                std::cout << "Error: " << GetLastError() << std::endl;
                return;
            }
        }
        std::cout << "File " << from << " was copied as " << to <<
                  " successfully" << std::endl;
    }
}

void move_file() {
    TCHAR from[BUFF],
            to[BUFF];
    std::cout << "Move from:" << std::endl;
    bool input = get_name(from);
    if(input) {
        std::cout << "Move to:" << std::endl;
        input = get_name(to);
    }
    if(input) {
        if(!MoveFile(from, to)) {
            DWORD err = GetLastError();
            if(err == ERROR_FILE_EXISTS || err == ERROR_ALREADY_EXISTS) {
                char ch;
                do {
                    std::cout << "File already exists, rewrite? -- [Y]es|[N]o" << std::endl;
                    if(!(safestream >> ch)|| (ch != 'Y' && ch != 'N')) {
                        std::cout << "Invalid input: ";
                        if(!safestream) std::cout << safestream.get_state();
                        else std::cout << "put in either \'Y\' or \'N\'";
                        std::cout << std::endl;
                        pause();
                    }
                }while(!safestream || (ch != 'Y' && ch != 'N'));
                if(ch == 'N') {
                    std::cout << "No file was moved. Abort" << std::endl;
                    return;
                }
                if(!MoveFileEx(from, to, MOVEFILE_REPLACE_EXISTING)) {
                    std::cout << "Error: " << GetLastError() << std::endl;
                    return;
                }
            }
            else {
                std::cout << "Error: " << GetLastError() << std::endl;
                return;
            }
        }
        std::cout << "File " << from << " moved to " << to <<
                  " successfully" << std::endl;
    }
}