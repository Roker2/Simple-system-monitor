#include "cpu_parser.h"

#include <Windows.h>
#include <sysinfoapi.h>

WinCpuParser::WinCpuParser() {}

void WinCpuParser::parse()
{
    SYSTEM_INFO lpSystemInfo;
    GetSystemInfo(&lpSystemInfo);
    _CPUCount = lpSystemInfo.dwNumberOfProcessors;
}

void WinCpuParser::update()
{
    parse();
}

float WinCpuParser::getLoad(size_t core) const
{
    return 0.f;
}

uint64_t WinCpuParser::getTotalWorkTime() const
{
    return 0;
}
