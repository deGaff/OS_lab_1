//
// Created by d3Gaff on 02.10.2021.
//

#ifndef UNTITLED_ATTRIBUTE_MANAGER_H
#define UNTITLED_ATTRIBUTE_MANAGER_H

#include <windows.h>
#include <iostream>
#include "menu.h"
#define BUFF 256
#define FILE_ATTRIBUTE_INTEGRITY_STREAM 0x8000
#define FILE_ATTRIBUTE_NO_SCRUB_DATA 0x20000
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x400000
#define FILE_ATTRIBUTE_RECALL_ON_OPEN 0x40000



static const DWORD attributes[] = {
        FILE_ATTRIBUTE_ARCHIVE,
        FILE_ATTRIBUTE_COMPRESSED,
        FILE_ATTRIBUTE_DEVICE,
        FILE_ATTRIBUTE_DIRECTORY,
        FILE_ATTRIBUTE_ENCRYPTED,
        FILE_ATTRIBUTE_HIDDEN,
        FILE_ATTRIBUTE_INTEGRITY_STREAM,
        FILE_ATTRIBUTE_NORMAL,
        FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
        FILE_ATTRIBUTE_NO_SCRUB_DATA,
        FILE_ATTRIBUTE_OFFLINE,
        FILE_ATTRIBUTE_READONLY,
        FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS,
        FILE_ATTRIBUTE_RECALL_ON_OPEN,
        FILE_ATTRIBUTE_REPARSE_POINT,
        FILE_ATTRIBUTE_SPARSE_FILE,
        FILE_ATTRIBUTE_SYSTEM,
        FILE_ATTRIBUTE_TEMPORARY,
};




std::string get_string_attribute(DWORD flag);

void get_file_attr();
void set_file_attr();
void get_file_info();
void get_file_time();
void set_file_time();

bool attr_input(DWORD* dd);
bool get_fname(TCHAR* name);

#endif //UNTITLED_ATTRIBUTE_MANAGER_H
