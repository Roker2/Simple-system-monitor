#pragma once

#include "core/parsers/interfaces/memory_parser.h"

class WinMemoryParser : public MemoryParser
{
public:
    typedef std::unique_ptr<WinMemoryParser> pointer;
    WinMemoryParser();
    void parse() final;
    void update() final;
    inline MemoryInfo getMemoryInfo() const final { return memoryInfo; }
    inline uint64_t getPageSize() const { return pageSize; }
private:
    MemoryInfo memoryInfo;
    uint64_t pageSize;  // in bytes
};
