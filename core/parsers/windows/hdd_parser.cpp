#include "hdd_parser.h"

#include "core/parsers/parseerror.hpp"

#include <Windows.h>
#include <fileapi.h>

WindowsHddParser::WindowsHddParser()
{

}

void WindowsHddParser::parse()
{
    const auto drives = parseLetters();
    parseDrives(drives);
    parseDrivesActivity(drives);
}

void WindowsHddParser::update()
{
    parse();
}

WindowsHddParser::letters WindowsHddParser::parseLetters()
{
    DWORD size = GetLogicalDriveStringsA(0, nullptr);
    std::vector<char> driveStrings(size);
    if (GetLogicalDriveStringsA(size, driveStrings.data()) != size - 1)
    {
        throw HddParseError("Windows Hdd Parser: failed to get volumes letters");
    }

    letters drives;
    for (auto p = driveStrings.data(); *p; p++)
    {
        if (GetDriveTypeA(p) == DRIVE_FIXED)
            drives.push_back(p);
        while (*p)
            p++;
    }
    return drives;
}

void WindowsHddParser::parseDrives(const letters& drives)
{
    for (const auto& drive : drives)
    {
        ULARGE_INTEGER totalSpace;
        ULARGE_INTEGER freeSpace;
        GetDiskFreeSpaceExA(drive.c_str(), nullptr, &totalSpace, &freeSpace);
        deviceInfoMap.insert({drive, DeviceInfo{drive, 0, totalSpace.QuadPart, freeSpace.QuadPart}});
    }
}

void WindowsHddParser::parseDrivesActivity(const letters& drives)
{
    constexpr DWORD cbOutBufferSize = sizeof(DISK_PERFORMANCE);
    deviceActivity.bytesRead = 0;
    deviceActivity.bytesWrite = 0;
    for (const auto& drive : drives)
    {
        auto path = "\\\\.\\" + drive;
        path.pop_back();

        HANDLE hTarget;
        hTarget = CreateFileA(path.c_str(),
                             0,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             nullptr,
                             OPEN_EXISTING,
                             0,
                             nullptr);

        if (hTarget == INVALID_HANDLE_VALUE)
        {
            throw HddParseError("Windows Hdd Parser: failed to get volume " + drive + " activity: Can not open handle");
        }

        DISK_PERFORMANCE dp;
        DWORD cbBytesReturned;
        if (DeviceIoControl(hTarget, IOCTL_DISK_PERFORMANCE, nullptr, 0, &dp, cbOutBufferSize, &cbBytesReturned, nullptr))
        {
            deviceActivity.bytesRead += static_cast<uint64_t>(dp.BytesRead.QuadPart);
            deviceActivity.bytesWrite += static_cast<uint64_t>(dp.BytesWritten.QuadPart);
            CloseHandle(hTarget);
        }
        else
        {
            CloseHandle(hTarget);
            throw HddParseError("Windows Hdd Parser: failed to get volume " + drive + " activity: Can not get info");
        }
    }
}
