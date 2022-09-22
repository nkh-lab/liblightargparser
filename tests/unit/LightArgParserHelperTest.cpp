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

#include "LightArgParser.h"

#include <gtest/gtest.h>

using namespace nkhlab::lightargparser;

TEST(LightArgParserHelperTest, EmptyArgs)
{
    Args_t args{};
    LightArgParserHelper helper(args);

    EXPECT_FALSE(helper.KeyExists("key"));
    EXPECT_FALSE(helper.AnyKeyExists({"k", "key"}));
    EXPECT_EQ(helper.GetKeys().size(), 0);
}

TEST(LightArgParserHelperTest, ThreeArgs)
{
    Args_t args{{"key1", "data1"}, {"key2", "data2"}, {"key3", "data3"}};
    LightArgParserHelper helper(args);

    EXPECT_TRUE(helper.KeyExists("key1"));
    EXPECT_TRUE(helper.AnyKeyExists({"key", "key1"}));
    EXPECT_FALSE(helper.AnyKeyExists({"key", "k"}));
    EXPECT_EQ(helper.GetKeys().size(), 3);
}
