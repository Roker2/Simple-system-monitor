#pragma once
#include "interfaces/memory_parser.h"

#ifdef __linux__
#include <unistd.h>
#endif

class MeminfoMemoryParser : public MemoryParser
{
public:
    typedef std::unique_ptr<MeminfoMemoryParser> pointer;
    MeminfoMemoryParser(const std::string& _meminfoFile);
    void parse() final;
    void update() final;
    inline MemoryInfo getMemoryInfo() const final { return memoryInfo; }
    inline uint64_t getPageSize() const { return pageSize; }
    inline const std::string& getMeminfoFileName() const { return meminfoFile; }
private:
    std::string meminfoFile;
    MemoryInfo memoryInfo;
    uint64_t pageSize;  // in bytes
};
