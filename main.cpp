#include "drive_manager.h"
#include "directory_manager.h"
#include "file_manager.h"
#include "attribute_manager.h"

int main() {

    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    menu drive_menu = make_drives_menu();

    view_menu main_menu("Main", {
            std::make_shared<view_menu>("Drives", menu{
                std::make_shared<action_menu>("Get logical drives", use_GetLogicalDrives),
                std::make_shared<view_menu>("Get drive info", drive_menu)
            }),
            std::make_shared<view_menu>("Directories", menu{
                std::make_shared<action_menu>("Create directory", create_dir),
                std::make_shared<action_menu>("Remove directory", delete_dir)
            }),
            std::make_shared<view_menu>("Files", menu {
                std::make_shared<action_menu>("Create file", create_file),
                std::make_shared<action_menu>("Copy file", copy_file),
                std::make_shared<action_menu>("Move file", move_file)
            }),
            std::make_shared<view_menu>("File attributes", menu {
                std::make_shared<action_menu>("Get file attributes", get_file_attr),
                std::make_shared<action_menu>("Set file attributes", set_file_attr),
                std::make_shared<action_menu>("Get file info by handle", get_file_info),
                std::make_shared<action_menu>("Get file time", get_file_time),
                std::make_shared<action_menu>("Set file time", set_file_time)
            })
    });

    main_menu.execute();

    return 0;
}
/*
 * E: * Do this
 *    * Do that
 *    * Do other
 *
 * D: * Do this
 *    * Do that
 *    * Do other
 *
 */