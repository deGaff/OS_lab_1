//
// Created by d3Gaff on 01.10.2021.
//
#include <windows.h>
#include <vector>
#include "menu.h"

#ifndef UNTITLED_DRIVE_MANAGE_H
#define UNTITLED_DRIVE_MANAGE_H

#define BUFF 256
#define FILE_SUPPORTS_BLOCK_REFCOUNTING 0x08000000
#define FILE_DAX_VOLUME 0x20000000
static const DWORD sys_flags[] = {FILE_CASE_PRESERVED_NAMES,
                     FILE_CASE_SENSITIVE_SEARCH,
                     FILE_DAX_VOLUME,
                     FILE_FILE_COMPRESSION,
                     FILE_NAMED_STREAMS,
                     FILE_PERSISTENT_ACLS,
                     FILE_READ_ONLY_VOLUME,
                     FILE_SEQUENTIAL_WRITE_ONCE,
                     FILE_SUPPORTS_ENCRYPTION,
                     FILE_SUPPORTS_EXTENDED_ATTRIBUTES,
                     FILE_SUPPORTS_HARD_LINKS,
                     FILE_SUPPORTS_OBJECT_IDS,
                     FILE_SUPPORTS_OPEN_BY_FILE_ID,
                     FILE_SUPPORTS_REPARSE_POINTS,
                     FILE_SUPPORTS_SPARSE_FILES,
                     FILE_SUPPORTS_TRANSACTIONS,
                     FILE_SUPPORTS_USN_JOURNAL,
                     FILE_UNICODE_ON_DISK,
                     FILE_VOLUME_IS_COMPRESSED,
                     FILE_VOLUME_QUOTAS,
                     FILE_SUPPORTS_BLOCK_REFCOUNTING};

menu make_drives_menu();

void use_GetLogicalDrives();

std::vector<char> LogicalDrives();

std::string get_string_flag(DWORD flag);
void print_system_flags(DWORD in);


void get_drive_type();
void get_volume_info();
void get_disk_free();


#endif //UNTITLED_DRIVE_MANAGE_H
