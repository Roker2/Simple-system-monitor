#pragma once

#include "parser.hpp"
#include <memory>

class CPUParser : public Parser
{
public:
    typedef std::unique_ptr<CPUParser> pointer;
    virtual void parse() = 0;
    virtual void update() = 0;
    virtual float getLoad(size_t core) const = 0;
    virtual size_t getCpuCount() const = 0;
    virtual uint64_t getTotalWorkTime() const = 0;
};
