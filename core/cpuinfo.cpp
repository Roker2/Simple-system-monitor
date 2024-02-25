#include "cpuinfo.hpp"
#ifdef __linux__
#include "parsers/linux/cpu_parser.hpp"
#elif defined(_MSC_VER)
#include "parsers/windows/cpu_parser.h"
#endif


CPUInfo::pointer CPUInfo::fromStatFile(const std::string& statFile)
{
    CPUInfo::pointer info(new CPUInfo());
#ifdef __linux__
    info->parser = StatFileCPUParser::pointer(new StatFileCPUParser(statFile));
#elif defined(_MSC_VER)
    info->parser = WinCpuParser::pointer(new WinCpuParser());
#endif
    info->parse();
    return info;
}

void CPUInfo::update()
{
    parser->update();
}


void CPUInfo::parse()
{
    parser->parse();
}



