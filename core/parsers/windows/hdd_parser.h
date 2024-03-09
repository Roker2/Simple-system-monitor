#pragma once

#include "core/parsers/interfaces/hdd_parser.h"

#include <vector>

class WindowsHddParser : public HddParser
{
    using letters = std::vector<std::string>;

public:
    using pointer = std::unique_ptr<WindowsHddParser>;
    WindowsHddParser();
    void parse() final;
    void update() final;
    inline const DeviceInfoMap& getDeviceInfoMap() const final { return deviceInfoMap; }
    inline const DeviceActivity& getDeviceActivity() const final { return deviceActivity; }

private:
    letters parseLetters();
    void parseDrives(const letters& drives);
    void parseDrivesActivity(const letters& drives);

private:
    DeviceInfoMap deviceInfoMap;
    DeviceActivity deviceActivity;
};
