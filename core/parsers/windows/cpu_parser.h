#pragma once

#include "core/parsers/interfaces/cpu_parser.h"
#include <memory>
#include <vector>
#include <Windows.h>
#include <winternl.h>

class WinCpuParser : public CPUParser
{
    typedef NTSTATUS (NTAPI *sNtQuerySystemInformation)
        (UINT SystemInformationClass,
         PVOID SystemInformation,
         ULONG SystemInformationLength,
         PULONG ReturnLength);

    struct CoreUsage
    {
        uint64_t idle{ 0 };
        uint64_t kernel{ 0 };
        uint64_t user{ 0 };

        uint64_t summ() const
        {
            return idle + kernel + user;
        }
    };

    using CoresUsage = std::vector<CoreUsage>;

public:
    using pointer = std::unique_ptr<WinCpuParser>;

    WinCpuParser();
    void parse() final;
    void update() final;
    float getLoad(size_t core) const final;
    inline virtual size_t getCpuCount() const { return _CPUCount; }
    uint64_t getTotalWorkTime() const;

private:
    float calculateCoreUsage(const CoreUsage &prev, const CoreUsage &cur) const;

private:
    int _CPUCount;
    HMODULE _ntdll_module;
    sNtQuerySystemInformation _pNtQuerySystemInformation{ nullptr };
    CoresUsage _coresUsage;
    CoresUsage _prevCoresUsage;
};
