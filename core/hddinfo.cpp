#include "hddinfo.hpp"

#ifdef __linux__
#include "parsers/linux/hdd_parser.hpp"
#elif defined(_MSC_VER)
#include "parsers/windows/hdd_parser.h"
#endif

HddInfo::pointer HddInfo::makeInLinuxWay()
{
    HddInfo::pointer info(new HddInfo());
#ifdef __linux__
    info->parser = LinuxHddParser::pointer(new LinuxHddParser());
#elif defined(_MSC_VER)
    info->parser = WindowsHddParser::pointer(new WindowsHddParser());
#endif
    info->parse();
    return info;
}

void HddInfo::update()
{
    parser->update();
}

void HddInfo::parse()
{
    parser->parse();
}
