#pragma once

#include <map>
#include <memory>
#include <string>

namespace nlab {

class LightArgParserImpl;

using ArgKey_t = std::string;
using ArgVal_t = std::string;

class LightArgParser
{
public:
    LightArgParser(int argc, const char** argv);
    ~LightArgParser();

    bool Parse(std::map<ArgKey_t, ArgVal_t>& config_args, std::map<ArgKey_t, ArgVal_t>& data_args);

private:
    std::unique_ptr<LightArgParserImpl> impl;
};

} // namespace nlab
