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

#include "LightArgParser.h"

namespace nkhlab {
namespace lightargparser {

namespace impl {
class LightArgParserHelperImpl;
}

class LightArgParserHelper
{
public:
    LightArgParserHelper(const Args_t& args);
    ~LightArgParserHelper();

    bool KeyExists(const ArgKey_t& key);
    bool AnyKeyExists(const std::vector<ArgKey_t>& keys);
    std::vector<ArgKey_t> GetKeys();

private:
    std::unique_ptr<impl::LightArgParserHelperImpl> impl_;
};

} // namespace lightargparser
} // namespace nkhlab
