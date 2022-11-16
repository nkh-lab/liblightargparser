/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nkhlab {
namespace lightargparser {

using ArgKey_t = std::string;
using ArgVal_t = std::string;
using Arg_t = std::pair<ArgKey_t, ArgVal_t>;
using Args_t = std::map<ArgKey_t, ArgVal_t>;

namespace impl {
class LightArgParserImpl;
}

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
