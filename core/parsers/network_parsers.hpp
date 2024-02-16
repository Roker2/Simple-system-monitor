#pragma once

#include "interfaces/network_parser.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

class NetstatNetworkParser : public NetworkParser
{
public:
    typedef std::unordered_map<std::string, uint64_t> IPInfo;
    typedef std::vector<std::string> Keys;
    typedef std::vector<uint64_t> Values;
    typedef std::unique_ptr<NetstatNetworkParser> pointer;
    NetstatNetworkParser(const std::string& _netstatFile);
    void parse() final;
    void update() final;
    inline uint64_t getIncome() const final { return ipinfo.at("InOctets"); }
    inline uint64_t getOutcome() const final { return ipinfo.at("OutOctets"); }
    Keys keys();
    Values values();
private:
    std::string netstatFile;
    IPInfo ipinfo;
};
