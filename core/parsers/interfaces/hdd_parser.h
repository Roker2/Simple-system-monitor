#pragma once

#include "parser.hpp"
#include <string>
#include <memory>
#include <map>

struct DeviceInfo
{
    std::string devicePath;
    uint64_t physicalBlockSize;
    uint64_t totalSpace;
    uint64_t freeSpace;
};

struct DeviceActivity
{
    uint64_t bytesRead;
    uint64_t bytesWrite;
};

class HddParser : public Parser
{
public:
    typedef std::unique_ptr<HddParser> pointer;
    typedef std::map<std::string, DeviceInfo> DeviceInfoMap;
    virtual void parse() = 0;
    virtual void update() = 0;
    virtual const DeviceInfoMap& getDeviceInfoMap() const = 0;
    virtual const DeviceActivity& getDeviceActivity() const = 0;
};
