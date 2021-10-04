//
// Created by d3Gaff on 04.10.2021.
//

#ifndef UNTITLED_OVERLAPPED_COPY_H
#define UNTITLED_OVERLAPPED_COPY_H
#include <windows.h>
#include <functional>
#include <iostream>
#include "time.h"
#define BUFF 256

void overlapped_copy();

bool path(TCHAR* path);

void io_overlapped(const std::function<BOOL(HANDLE, LPVOID, DWORD, LPOVERLAPPED, LPOVERLAPPED_COMPLETION_ROUTINE)>& f,
                   const HANDLE& h,
                   const unsigned& block,
                   const unsigned& oper,
                   long long lsize,
                   BYTE**& buff,
                   OVERLAPPED*& over);
#endif //UNTITLED_OVERLAPPED_COPY_H
