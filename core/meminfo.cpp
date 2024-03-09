#include "meminfo.hpp"

MemInfo::pointer MemInfo::fromMemInfoFile(const std::string& infoFile)
{
    MemInfo::pointer newMemInfo(new MemInfo());
#ifdef __linux__
    newMemInfo->parser = MeminfoMemoryParser::pointer(new MeminfoMemoryParser(infoFile));
#elif defined(_MSC_VER)
    newMemInfo->parser = WinMemoryParser::pointer(new WinMemoryParser());
#endif
    newMemInfo->parse();
    return newMemInfo;
}

void MemInfo::update()
{
    parser->update();
    MemoryInfo meminfo = parser->getMemoryInfo();
    memTotal = meminfo.memoryTotal;
    memAvailable = meminfo.memoryFree;
    swapTotal = meminfo.swapTotal;
    swapFree = meminfo.swapFree;
}

void MemInfo::parse()
{
    update();
}
