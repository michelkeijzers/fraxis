#include "Lcd1602DisplayModel.hpp"
#include <cstring>

//#include <windows.h>
//#include <tlhelp32.h>
//#include <iostream>
//#include "../../../Common/Services/Debug/Debug.hpp"


//
//
//void PrintAllThreads()
//{
//    DWORD pid = GetCurrentProcessId();
//
//    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
//    if (snapshot == INVALID_HANDLE_VALUE)
//    {
//        Debug::PrintText("Failed to chreate thread snapshot\n");
//        return;
//    }
//
//    THREADENTRY32 te;
//    te.dwSize = sizeof(THREADENTRY32);
//
//    if (!Thread32First(snapshot, &te))
//    {
//        Debug::PrintText("Thread32first failed\n");
//        CloseHandle(snapshot);
//        return;
//    }
//
//    Debug::PrintText("Threads in curren tprocess\n");
//
//    do
//    {
//        if (te.th32OwnerProcessID == pid)
//        {
//            Debug::PrintInt("ThreadId", te.th32ThreadID);
//        }
//    } while (Thread32Next(snapshot, &te));
//
//    CloseHandle(snapshot);
//}


Lcd1602DisplayModel::Lcd1602DisplayModel()
{
    memset(_line1, ' ', sizeof(_line1));
    memset(_line2, ' ', sizeof(_line2));
}

void Lcd1602DisplayModel::WriteLines(const char* line1, const char* line2)
{
    char normalized1[16];
    char normalized2[16];

    // Normalize line1
    size_t len1 = strnlen(line1, 16);
    memcpy(normalized1, line1, len1);
    memset(normalized1 + len1, ' ', 16 - len1);

    // Normalize line2
    size_t len2 = strnlen(line2, 16);
    memcpy(normalized2, line2, len2);
    memset(normalized2 + len2, ' ', 16 - len2);

    bool changed = false;

    if (memcmp(_line1, normalized1, len1) != 0)
    {
        memcpy(_line1, normalized1, len1);
        changed = true;
    }

    if (memcmp(_line2, normalized2, len2) != 0)
    {
        memcpy(_line2, normalized2, len2);
        changed = true;
    }

    if (changed)
    {
        MarkDirty();
    }

    //PrintAllThreads();
}
