#pragma once

#include "core/parsers/interfaces/cpu_parser.h"
#include <vector>
#include <string>

/*
    Has values of CPU state in this moment(times for different activities).
*/
struct CPUTimes
{
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;

    uint64_t summ() const
    {
        return user + nice + system + idle + iowait + irq + softirq;
    }
    CPUTimes operator-(const CPUTimes& other);
    float usage();
};

class StatFileCPUParser : public CPUParser
{
public:
    typedef std::unique_ptr<StatFileCPUParser> pointer;
    typedef std::vector<CPUTimes> Measurements;
    StatFileCPUParser(const std::string& fname = "/proc/stat");
    void parse() final;
    void update() final;
    float getLoad(size_t core) const final;
    inline virtual size_t getCpuCount() const { return _CPUCount; }
    uint64_t getTotalWorkTime() const;
    inline const std::string& getStatFileName() const { return statFile; }
private:
    inline void addCPU(float perc) {_CPUCount++; loadPercentages.push_back(perc);}
    inline void removeCPU() {_CPUCount--; loadPercentages.pop_back();}
    int _CPUCount;
    std::string statFile;
    std::vector<float> loadPercentages;
    Measurements curMeasurement;
    Measurements lastMeasurement;
    CPUTimes lastCPUTimes;
};
