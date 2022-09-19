#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nkhlab {
namespace lightargparser {

namespace impl {
class LightArgParserImpl;
}

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
    std::unique_ptr<impl::LightArgParserImpl> impl_;
};

} // namespace lightargparser
} // namespace nkhlab

#include "LightArgParserHelper.h"
