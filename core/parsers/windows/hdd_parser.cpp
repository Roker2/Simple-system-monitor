#include "hdd_parser.h"

#include "core/parsers/parseerror.hpp"

#include <Windows.h>
#include <fileapi.h>
#include <iostream>
#include <vector>

WindowsHddParser::WindowsHddParser() {}

void WindowsHddParser::parse()
{
    parseDrives();
}

void WindowsHddParser::update()
{
    parse();
}

void WindowsHddParser::parseDrives()
{
    DWORD size = GetLogicalDriveStringsA(0, nullptr);
    std::vector<char> drive_strings(size);
    if (GetLogicalDriveStringsA(size, drive_strings.data()) != size - 1)
    {
        throw HddParseError("Windows Hdd Parser: failed to get volumes letters");
    }

    std::vector<std::string> drives;
    for (auto p = drive_strings.data(); *p; p++)
    {
        if (GetDriveTypeA(p) == DRIVE_FIXED)
            drives.push_back(p);
        while (*p)
            p++;
    }

    for (const std::string& drive : drives)
    {
        ULARGE_INTEGER totalSpace;
        ULARGE_INTEGER freeSpace;
        GetDiskFreeSpaceExA(drive.c_str(), nullptr, &totalSpace, &freeSpace);
        deviceInfoMap.insert({drive, DeviceInfo{drive, 0, totalSpace.QuadPart, freeSpace.QuadPart}});
    }
}
