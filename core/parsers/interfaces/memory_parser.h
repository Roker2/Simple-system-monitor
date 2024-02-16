#pragma once

#include "core/parsers/parser.hpp"

struct MemoryInfo
{
    uint64_t memoryTotal;
    uint64_t memoryFree;
    uint64_t swapTotal;
    uint64_t swapFree;
};

class MemoryParser : public Parser
{
public:
    typedef std::unique_ptr<MemoryParser> pointer;
    virtual void parse() = 0;
    virtual void update() = 0;
    virtual MemoryInfo getMemoryInfo() const = 0;
    virtual uint64_t getPageSize() const = 0;
};
