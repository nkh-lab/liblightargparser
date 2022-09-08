#pragma once

#include "LightArgParser.h"

namespace nlab {

class LightArgParserHelperImpl;

class LightArgParserHelper
{
public:
    LightArgParserHelper(const Args_t& args);
    ~LightArgParserHelper();

    bool KeyExists(const ArgKey_t& key);
    bool AnyKeyExists(const std::vector<ArgKey_t>& keys);
    std::vector<ArgKey_t> GetKeys();

private:
    std::unique_ptr<LightArgParserHelperImpl> impl_;
};

} // namespace nlab
