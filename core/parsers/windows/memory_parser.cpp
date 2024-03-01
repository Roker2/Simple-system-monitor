#include "memory_parser.h"

#include <Windows.h>
#include <sysinfoapi.h>

#define DIV 1024

WinMemoryParser::WinMemoryParser()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    pageSize = sysInfo.dwPageSize;
}

void WinMemoryParser::parse()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);

    memoryInfo.memoryTotal = statex.ullTotalPhys / DIV;
    memoryInfo.memoryFree = statex.ullAvailPhys / DIV;
    memoryInfo.swapTotal = statex.ullTotalPageFile / DIV;
    memoryInfo.swapFree = statex.ullAvailPageFile / DIV;
}

void WinMemoryParser::update()
{
    parse();
}
