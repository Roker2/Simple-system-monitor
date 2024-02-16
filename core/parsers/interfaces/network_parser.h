#pragma once

#include "parser.hpp"

class NetworkParser : public Parser
{
public:
    typedef std::unique_ptr<NetworkParser> pointer;
    virtual void parse() = 0;
    virtual void update() = 0;
    virtual uint64_t getIncome() const = 0;
    virtual uint64_t getOutcome() const = 0;
};
