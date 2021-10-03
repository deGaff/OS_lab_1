//
// Created by d3Gaff on 01.10.2021.
//
#include <iostream>

#include "drive_manager.h"

menu make_drives_menu() {
    auto drives = LogicalDrives();
    menu drives_menu;
    menu drives_actions = {
            std::make_shared<action_menu>("Get drive type", get_drive_type),
            std::make_shared<action_menu>("Get volume info", get_volume_info),
            std::make_shared<action_menu>("Get disk free space", get_disk_free)
    };
    for (auto drive : drives) {
        std::string temp;
        temp.push_back(drive);
        drives_menu.push_back(std::make_shared<view_menu>(temp, drives_actions));
    }
    return drives_menu;
}

void get_drive_type() {
    TCHAR rootpathname[BUFF] = {LAST_CHOSEN[0], ':', '\\'};
    UINT type = GetDriveType(rootpathname);

    std::cout << "Drive " << LAST_CHOSEN << " type is: ";
    switch (type)
    {
        case DRIVE_UNKNOWN:
            std::cout << "DRIVE_UNKNOWN";
            break;
        case DRIVE_NO_ROOT_DIR:
            std::cout << "DRIVE_NO_ROOT_DIR";
            break;
        case DRIVE_REMOVABLE:
            std::cout << "DRIVE_REMOVABLE";
            break;
        case DRIVE_FIXED:
            std::cout << "DRIVE_FIXED";
            break;
        case DRIVE_REMOTE:
            std::cout << "DRIVE_REMOTE";
            break;
        case DRIVE_CDROM:
            std::cout << "DRIVE_CDROM";
            break;
        case DRIVE_RAMDISK:
            std::cout << "DRIVE_RAMDISK";
            break;
        default: std::cout << "UNINTENDED_VALUE";
    }
    std::cout << std::endl;
}

std::string get_string_flag(DWORD flag) {
    switch(flag) {
        case FILE_CASE_PRESERVED_NAMES          :   return "FILE_CASE_PRESERVED_NAMES";
        case FILE_CASE_SENSITIVE_SEARCH         :   return "FILE_CASE_SENSITIVE_SEARCH";
        case FILE_DAX_VOLUME                    :   return "FILE_DAX_VOLUME";
        case FILE_FILE_COMPRESSION              :   return "FILE_FILE_COMPRESSION";
        case FILE_NAMED_STREAMS                 :   return "FILE_NAMED_STREAMS";
        case FILE_PERSISTENT_ACLS               :   return "FILE_PERSISTENT_ACLS";
        case FILE_READ_ONLY_VOLUME              :   return "FILE_READ_ONLY_VOLUME";
        case FILE_SEQUENTIAL_WRITE_ONCE         :   return "FILE_SEQUENTIAL_WRITE_ONCE";
        case FILE_SUPPORTS_ENCRYPTION           :   return "FILE_SUPPORTS_ENCRYPTION";
        case FILE_SUPPORTS_EXTENDED_ATTRIBUTES  :   return "FILE_SUPPORTS_EXTENDED_ATTRIBUTES";
        case FILE_SUPPORTS_HARD_LINKS           :   return "FILE_SUPPORTS_HARD_LINKS";
        case FILE_SUPPORTS_OBJECT_IDS           :   return "FILE_SUPPORTS_OBJECT_IDS";
        case FILE_SUPPORTS_OPEN_BY_FILE_ID      :   return "FILE_SUPPORTS_OPEN_BY_FILE_ID";
        case FILE_SUPPORTS_REPARSE_POINTS       :   return "FILE_SUPPORTS_REPARSE_POINTS";
        case FILE_SUPPORTS_SPARSE_FILES         :   return "FILE_SUPPORTS_SPARSE_FILES";
        case FILE_SUPPORTS_TRANSACTIONS         :   return "FILE_SUPPORTS_TRANSACTIONS";
        case FILE_SUPPORTS_USN_JOURNAL          :   return "FILE_SUPPORTS_USN_JOURNAL";
        case FILE_UNICODE_ON_DISK               :   return "FILE_UNICODE_ON_DISK";
        case FILE_VOLUME_IS_COMPRESSED          :   return "FILE_VOLUME_IS_COMPRESSED";
        case FILE_VOLUME_QUOTAS                 :   return "FILE_VOLUME_QUOTAS";
        case FILE_SUPPORTS_BLOCK_REFCOUNTING    :   return "FILE_SUPPORTS_BLOCK_REFCOUNTING";
        default                                 :   return "UNINTENDED_VALUE";
    }
}

void print_system_flags(DWORD in) {
    for (auto flag : sys_flags) {
        if(in & flag) std::cout << '\t' <<  get_string_flag(flag) << std::endl;
    }
}

void get_volume_info() {
    TCHAR rootpathname[BUFF] = {LAST_CHOSEN[0], ':', '\\'};
    TCHAR lpVolumeNameBuffer[BUFF],
          lpFileSystemNameBuffer[BUFF];
    DWORD VolumeSerialNumber = 0,
            MaximumComponentLength = 0,
            FileSystemFlags = 0;
    std::cout << "Drive " << LAST_CHOSEN << " volume info:" << std::endl;
    if(GetVolumeInformation(rootpathname, lpVolumeNameBuffer, BUFF, &VolumeSerialNumber,
                            &MaximumComponentLength, &FileSystemFlags, lpFileSystemNameBuffer, BUFF)) {
        std::cout << "Volume Name: " << lpVolumeNameBuffer << std::endl
                << "Serial Number: " << VolumeSerialNumber << std::endl
                << "Maximum Component Length: " << MaximumComponentLength << std::endl
                << "File System Flags:"  << std::endl;
        print_system_flags(FileSystemFlags);
        std::cout << "File System Name: " << lpFileSystemNameBuffer << std::endl;
    } else {
        std::cout << "ERROR: " << GetLastError() << std::endl;
    }
}

void get_disk_free() {
    TCHAR rootpathname[BUFF] = {LAST_CHOSEN[0], ':', '\\'};
    DWORD SectorsPerCluster = 0;
    DWORD BytesPerSector = 0;
    DWORD NumberOfFreeClusters = 0;
    DWORD TotalNumberOfClusters = 0;
    GetDiskFreeSpace(rootpathname, &SectorsPerCluster, &BytesPerSector,
                     &NumberOfFreeClusters, &TotalNumberOfClusters);
    std::cout << "Sectors Per Cluster: " << SectorsPerCluster << std::endl
              << "Bytes Per Sector: " << BytesPerSector << std::endl
              << "Number Of Free Clusters: " << NumberOfFreeClusters << std::endl
              << "Total Number Of Clusters: " << TotalNumberOfClusters << std::endl;
}

void use_GetLogicalDrives() {
    std::cout << "Available disk drives: ";
    auto drives = LogicalDrives();
    for (auto drive : drives) {
        std::cout << drive << "; ";
    }
    std::cout << std::endl;
}

std::vector<char> LogicalDrives() {
    std::vector<char> drives;
    DWORD dd = GetLogicalDrives();

    for (int i = 0; i < 26; ++i ) {
        if((dd>>i)&1) drives.push_back(char(65+i));
    }
    return drives;
}