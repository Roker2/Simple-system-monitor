#pragma once

#include "interfaces/hdd_parser.h"
#include <memory>
#include <vector>
#include <string>

#ifdef __linux__
#include <sys/statvfs.h>
#endif

#ifdef __linux__
class LinuxHddParser : public HddParser
{
public:
    typedef std::unique_ptr<LinuxHddParser> pointer;
    typedef std::vector<std::string> MountedList;
    LinuxHddParser();
    void parse() final;
    void update() final;
    inline const DeviceInfoMap& getDeviceInfoMap() const final { return deviceInfoMap; }
    inline const DeviceActivity& getDeviceActivity() const final { return deviceActivity; }
private:
    void initFiles();
    void setMountedsList();
    void getDevicesSpaceInfo();
    void getDevicesActivity();
    void getLogicalBlockSize();

    bool areMountEqualWithLast(const std::string& mountFile);

    DeviceInfoMap deviceInfoMap;
    DeviceActivity deviceActivity;
    int logicalBlockSize;
    std::string lastReadMountsFile;

    std::string mountsFile;
    std::string logicBlockFile;
    std::string diskstatsFile;

    static const std::vector<std::string> mountsFiles;
    static const std::vector<std::string> logicBlockSizeFiles;
    static const std::vector<std::string> diskstatsFiles;
};
#endif
