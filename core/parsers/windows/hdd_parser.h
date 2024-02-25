#pragma once

#include "core/parsers/interfaces/hdd_parser.h"

class WindowsHddParser : public HddParser
{
public:
    using pointer = std::unique_ptr<WindowsHddParser>;
    WindowsHddParser();
    void parse() final;
    void update() final;
    inline const DeviceInfoMap& getDeviceInfoMap() const final { return deviceInfoMap; }
    inline const DeviceActivity& getDeviceActivity() const final { return deviceActivity; }

private:
    DeviceInfoMap deviceInfoMap;
    DeviceActivity deviceActivity;
};
