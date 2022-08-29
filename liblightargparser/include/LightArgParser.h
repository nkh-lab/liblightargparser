#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nlab {

class LightArgParserImpl;

using ArgKey_t = std::string;
using ArgVal_t = std::string;
using Args_t = std::map<ArgKey_t, ArgVal_t>;

class LightArgParser
{
public:
    LightArgParser(int argc, const char** argv);
    ~LightArgParser();

    bool Parse(Args_t& config_args, Args_t& data_args, std::string& bad_arg);

private:
    std::unique_ptr<LightArgParserImpl> impl;
};

class LightArgParserHelper
{
public:
    LightArgParserHelper() = default;
    ~LightArgParserHelper() = default;

    static inline bool KeyExists(const Args_t& args, const ArgKey_t& key)
    {
        return args.find(key) == args.end() ? false : true;
    }

    static inline bool AnyKeyExists(const Args_t& args, const std::vector<ArgKey_t>& keys)
    {
        for (auto key : keys)
            if (args.find(key) == args.end()) return true;

        return false;
    }
};

} // namespace nlab
