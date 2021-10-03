//
// Created by d3Gaff on 02.10.2021.
//

#include "attribute_manager.h"
#include <vector>



std::string get_string_attribute(DWORD flag) {
    switch(flag) {
        case FILE_ATTRIBUTE_ARCHIVE                 :   return "FILE_ATTRIBUTE_ARCHIVE";
        case FILE_ATTRIBUTE_COMPRESSED              :   return "FILE_ATTRIBUTE_COMPRESSED";
        case FILE_ATTRIBUTE_DEVICE                  :   return "FILE_ATTRIBUTE_DEVICE";
        case FILE_ATTRIBUTE_DIRECTORY               :   return "FILE_ATTRIBUTE_DIRECTORY";
        case FILE_ATTRIBUTE_ENCRYPTED               :   return "FILE_ATTRIBUTE_ENCRYPTED";
        case FILE_ATTRIBUTE_HIDDEN                  :   return "FILE_ATTRIBUTE_HIDDEN";
        case FILE_ATTRIBUTE_INTEGRITY_STREAM        :   return "FILE_ATTRIBUTE_INTEGRITY_STREAM";
        case FILE_ATTRIBUTE_NORMAL                  :   return "FILE_ATTRIBUTE_NORMAL";
        case FILE_ATTRIBUTE_NOT_CONTENT_INDEXED     :   return "FILE_ATTRIBUTE_NOT_CONTENT_INDEXED";
        case FILE_ATTRIBUTE_NO_SCRUB_DATA           :   return "FILE_ATTRIBUTE_NO_SCRUB_DATA";
        case FILE_ATTRIBUTE_OFFLINE                 :   return "FILE_ATTRIBUTE_OFFLINE";
        case FILE_ATTRIBUTE_READONLY                :   return "FILE_ATTRIBUTE_READONLY";
        case FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS   :   return "FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS";
        case FILE_ATTRIBUTE_RECALL_ON_OPEN          :   return "FILE_ATTRIBUTE_RECALL_ON_OPEN";
        case FILE_ATTRIBUTE_REPARSE_POINT           :   return "FILE_ATTRIBUTE_REPARSE_POINT";
        case FILE_ATTRIBUTE_SPARSE_FILE             :   return "FILE_ATTRIBUTE_SPARSE_FILE";
        case FILE_ATTRIBUTE_SYSTEM                  :   return "FILE_SUPPORTS_USN_JOURNAL";
        case FILE_ATTRIBUTE_TEMPORARY               :   return "FILE_ATTRIBUTE_TEMPORARY";
        default                                     :   return "UNINTENDED_VALUE";
    }
}

void print_attributes(DWORD flag) {
    for (auto attribute : attributes) {
        if(attribute & flag) std::cout << '\t' <<
            get_string_attribute(attribute) << std::endl;
    }
}

void get_file_attr(){
    TCHAR name[BUFF];
    if(get_fname(name)) {
        DWORD dd = GetFileAttributes(name);
        if(dd!=INVALID_FILE_ATTRIBUTES) {
            std::cout << "File " << name << " attributes:" << std::endl;
            print_attributes(dd);
        }
        else {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
    }
}

bool attr_input(DWORD* dd) {
    std::vector<DWORD> attributes_available({FILE_ATTRIBUTE_ARCHIVE,
                                             FILE_ATTRIBUTE_HIDDEN,
                                             FILE_ATTRIBUTE_NORMAL,
                                             FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
                                             FILE_ATTRIBUTE_OFFLINE,
                                             FILE_ATTRIBUTE_READONLY,
                                             FILE_ATTRIBUTE_SYSTEM,
                                             FILE_ATTRIBUTE_TEMPORARY});
    unsigned ch = 0;
    bool oneCh = false;

    do {
        system("cls");
        std::cout << "\tSelect attributes" << std::endl;
        unsigned i = 1;
        for(auto attr : attributes_available) {
            std::cout << i << ". " << get_string_attribute(attr) << std::endl;
            ++i;
        }
        if(oneCh) std::cout << i++ << ". Apply attributes" << std::endl;
        std::cout << i << ". Cancel and exit" << std::endl;
        do {
            if(!(safestream >> ch) || ch < 1 ||
                    ch > attributes_available.size() + ((oneCh) ? 2 : 1)) {
                std::cout << "Invalid input: ";
                if(!safestream) std::cout << safestream.get_state();
                else std::cout << "no choice with that number";
                std::cout << std::endl;
                pause();
            }
        }while(!safestream || ch < 1 ||
               ch > attributes_available.size() + ((oneCh) ? 2 : 1));
        if((!attributes_available.empty()) && ch <= attributes_available.size()) {
            if(!oneCh) oneCh = true;
            *dd |= attributes_available[ch-1];
            attributes_available.erase(attributes_available.begin() + ch-1);
        }
        else if ((!oneCh)||(ch == attributes_available.size()+2)) return false;
        else return true;
    }while(true);
}

void set_file_attr(){
    TCHAR name[BUFF];
    DWORD attr = 0;
    if(attr_input(&attr)) {
        if(get_fname(name)) {
            if(SetFileAttributes(name, attr)) {
                std::cout << "File's " << name << " attributes:" << std::endl;
                print_attributes(attr);
                std::cout << "were set" << std::endl;
            }
            else {
                std::cout << "Error: " << GetLastError() << std::endl;
            }
        }
    }
    else {
        std::cout << "Cancel. Abort" << std::endl;
    }
}

void print_file_name(const FILETIME* f) {
    SYSTEMTIME s;
    if(FileTimeToSystemTime(f, &s)) {
        std::cout << s.wYear << '.' << s.wMonth << '.' << s.wDay
        << ' ' << s.wDayOfWeek << ' ' << s.wHour << ':'
        << s.wMinute << ':' << s.wMilliseconds << std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
}

void get_file_info(){
    TCHAR name[BUFF];
    if(get_fname(name)) {
        HANDLE h = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, 0, NULL);
        if(h!=INVALID_HANDLE_VALUE) {
            BY_HANDLE_FILE_INFORMATION info;
            if(GetFileInformationByHandle(h, &info)) {
                std::cout << "File " << name << " info:" << std::endl <<
                "Attributes: " << std::endl;
                print_attributes(info.dwFileAttributes);
                std::cout << "Volume serial number: " << info.dwVolumeSerialNumber << std::endl
                << "Creation time: "; print_file_name(&info.ftCreationTime);
                std::cout << "Last access time: "; print_file_name(&info.ftLastAccessTime);
                std::cout << "Last write time: "; print_file_name(&info.ftLastWriteTime);
                std::cout << "File size: "<<
                (static_cast<long long>(info.nFileSizeHigh) << 32)
                             + static_cast<long long>(info.nFileSizeLow) << '\n';
                std::cout << "Number of links: " << info.nNumberOfLinks << '\n';
                std::cout << "Unique identifier: "
                          << (static_cast<long long>(info.nFileIndexHigh) << 32)
                             + static_cast<long long>(info.nFileIndexLow) << '\n';
                CloseHandle(h);
                return;
            }
        }
        std::cout << "Error " << GetLastError() << std::endl;
    }
}
void get_file_time(){
    TCHAR name[BUFF];
    if(get_fname(name)) {
        HANDLE h = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, 0, NULL);
        if(h!=INVALID_HANDLE_VALUE) {
            BY_HANDLE_FILE_INFORMATION info;
            if(GetFileInformationByHandle(h, &info)) {
                std::cout << "File " << name <<  " time:" << std::endl
                << "Creation time: "; print_file_name(&info.ftCreationTime);
                std::cout << "Last access time: "; print_file_name(&info.ftLastAccessTime);
                std::cout << "Last write time: "; print_file_name(&info.ftLastWriteTime);
                CloseHandle(h);
                return;
            }
        }
        std::cout << "Error " << GetLastError() << std::endl;
    }
}
void set_file_time(){
    TCHAR name[BUFF];
    if(get_fname(name)) {
        HANDLE h = CreateFile(name, GENERIC_WRITE | GENERIC_READ,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  nullptr, OPEN_EXISTING, 0, NULL);
        if(h!=INVALID_HANDLE_VALUE) {
            SYSTEMTIME s;
            FILETIME create, access, write;
            GetSystemTime(&s);
            if(SystemTimeToFileTime(&s, &create) &&
                    SystemTimeToFileTime(&s, &access) &&
                    SystemTimeToFileTime(&s, &write)) {
                std::cout << "File " << name <<  " time was set:" << std::endl
                          << "Creation time: "; print_file_name(&create);
                std::cout << "Last access time: "; print_file_name(&access);
                std::cout << "Last write time: "; print_file_name(&write);
                CloseHandle(h);
                return;
            }
        }
        std::cout << "Error " << GetLastError() << std::endl;
    }
}

bool get_fname(TCHAR* name) {
    std::cout << "Enter file name" << std::endl;
    std::cin.getline(name, BUFF);
    if (name[0] == 0) {
        std::cout << "Empty name. Aborting" << std::endl;
        return false;
    }
    return true;
}