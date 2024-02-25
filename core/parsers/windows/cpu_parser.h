#pragma once

#include "core/parsers/interfaces/cpu_parser.h"
#include <memory>

class WinCpuParser : public CPUParser
{
public:
    using pointer = std::unique_ptr<WinCpuParser>;

    WinCpuParser();
    void parse() final;
    void update() final;
    float getLoad(size_t core) const final;
    inline virtual size_t getCpuCount() const { return _CPUCount; }
    uint64_t getTotalWorkTime() const;
private:
    int _CPUCount;
};
