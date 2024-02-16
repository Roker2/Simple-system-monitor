#pragma once

#include <memory>

class Parser
{
public:
    typedef std::unique_ptr<Parser> pointer;
    virtual void parse() = 0;
    virtual void update() = 0;
};
