//
// Created by d3Gaff on 04.10.2021.
//

#include "overlapped_copy.h"
#include "safe_input.h"

size_t call_count = 0;

VOID CALLBACK completion_call(DWORD err, DWORD bytes, LPOVERLAPPED over) { ++call_count; }

bool path(TCHAR* path) {
    std::cout << "Enter path" << std::endl;
    std::cin.getline(path, BUFF);
    if(path[0] == 0) {
        std::cout << "Empty path. Aborting" << std::endl;
        return false;
    }
    return true;
}



void overlapped_copy() {
    TCHAR from, to;

    std::cout << "Enter name of file to copy from" << std::endl;

    if(!path(&from)) {
        return;
    }
    HANDLE h_from = CreateFile(&from, GENERIC_READ, 0, nullptr, OPEN_EXISTING,
                               FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, nullptr);
    if(h_from != INVALID_HANDLE_VALUE) {
        std::cout << "Enter name of file to copy to" << std::endl;
        if(path(&to)) {
            HANDLE h_to = CreateFile(&to, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                                     FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, nullptr);
            if(h_to != INVALID_HANDLE_VALUE) {// GetLastError!=0?
                unsigned block;
                std::cout << "Enter block size: " << std::endl;
                if(safestream >> block) {
                    block *= 4096;
                    unsigned oper;
                    std::cout << "Enter amount of operations: " << std::endl;
                    if(safestream >> oper) {
                        LARGE_INTEGER start, end, freq;
                        long long lsize = 0;
                        DWORD hsize = 0;
                        long long  cur_size = lsize = GetFileSize(h_from, &hsize);
                        BYTE** buff = new BYTE* [oper];
                        for(unsigned i = 0; i < oper; ++i) {
                            buff[i] = new BYTE[block];
                        }
                        OVERLAPPED* read = new OVERLAPPED[oper];
                        OVERLAPPED* write = new OVERLAPPED[oper];
                        for(unsigned i = 0; i < oper; ++i) {
                            read[i].Offset = write[i].Offset = i * block;
                            read[i].OffsetHigh =write[i].OffsetHigh = i * hsize;
                        }
                        QueryPerformanceFrequency(&freq);
                        QueryPerformanceCounter(&start);
                        do {
                            io_overlapped(ReadFileEx, h_from, block, oper, lsize, buff, read);
                            io_overlapped(WriteFileEx, h_to, block, oper, lsize, buff, write);
                            cur_size -= block*oper;
                        } while(cur_size > 0);
                        QueryPerformanceCounter(&end);

                        LARGE_INTEGER  time;
                        time.QuadPart = end.QuadPart - start.QuadPart;
                        time.QuadPart *= 1000000;
                        time.QuadPart /= freq.QuadPart;

                        std::cout << "Time measurement: " << time.QuadPart << "ms" << std::endl;

                        SetFilePointer(h_to, lsize, nullptr, FILE_BEGIN);
                        SetEndOfFile(h_to);
                        CloseHandle(h_from);
                        CloseHandle(h_to);

                        for(unsigned i = 0; i < oper; ++i) delete[] buff[i];
                        delete[] buff;
                        delete[] read;
                        delete[] write;
                    }
                }
                else {
                    std::cout << "Invalid input: " << safestream.get_state() << std::endl;
                    CloseHandle(h_from);
                }
            }
            return;
        }
    }
    std::cout << "Error: " << GetLastError();
}

void io_overlapped(const std::function<BOOL(HANDLE, LPVOID, DWORD, LPOVERLAPPED, LPOVERLAPPED_COMPLETION_ROUTINE)>& f,
                   const HANDLE& h,
                   const unsigned& block,
                   const unsigned& oper,
                   long long lsize,
                   BYTE**& buff,
                   OVERLAPPED*& over) {
    unsigned s_oper = 0;
    for(unsigned i = 0; i < oper; ++i) {
        if(lsize > 0) {
            ++s_oper;
            f(h, buff[i], block, &over[i], completion_call);
            lsize -= block;
        }
    }
    while (call_count < s_oper) SleepEx(SIZE_MAX, true);
    for (unsigned i =0; i < oper; ++i) over[i].Offset += block * oper;
    call_count = 0;
}