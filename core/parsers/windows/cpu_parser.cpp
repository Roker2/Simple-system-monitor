#include "cpu_parser.h"

#include <sysinfoapi.h>

WinCpuParser::WinCpuParser()
{
    _ntdll_module = GetModuleHandleA("ntdll.dll");
    _pNtQuerySystemInformation = (sNtQuerySystemInformation) GetProcAddress(
        _ntdll_module,
        "NtQuerySystemInformation");
}

void WinCpuParser::parse()
{
    SYSTEM_INFO lpSystemInfo;
    GetSystemInfo(&lpSystemInfo);
    _CPUCount = lpSystemInfo.dwNumberOfProcessors;


    SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *a = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[_CPUCount];
    NTSTATUS status;
    status = _pNtQuerySystemInformation(SystemProcessorPerformanceInformation, a,
                                        sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * _CPUCount, nullptr);
    if (_coresUsage.size() != _CPUCount)
    {
        _coresUsage.resize(_CPUCount);
        _prevCoresUsage.resize(_CPUCount);
    }

    _prevCoresUsage = _coresUsage;
    for (size_t i = 0; i < _CPUCount; i++)
    {
        _coresUsage.at(i).idle = a[i].IdleTime.QuadPart;
        _coresUsage.at(i).kernel = a[i].KernelTime.QuadPart;
        _coresUsage.at(i).user = a[i].UserTime.QuadPart;
    }

    delete[] a;
}

void WinCpuParser::update()
{
    parse();
}

float WinCpuParser::getLoad(size_t core) const
{
    return calculateCoreUsage(_prevCoresUsage.at(core), _coresUsage.at(core));
}

uint64_t WinCpuParser::getTotalWorkTime() const
{
    return _coresUsage.begin()->summ();
}

float WinCpuParser::calculateCoreUsage(const CoreUsage &prev, const CoreUsage &cur) const
{
    const auto deltaIdle = cur.idle - prev.idle;
    const auto deltaKernel = cur.kernel - prev.kernel;
    const auto deltaUser = cur.user - prev.user;

    const auto totalTime = deltaKernel + deltaUser;
    const auto procTime = totalTime - deltaIdle;

    return static_cast<float>(procTime) / totalTime * 100;
}
